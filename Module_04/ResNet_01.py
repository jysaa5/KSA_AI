from __future__ import division

import six
from keras import backend as K
from keras.layers import (
    Input,
    Activation,
    Dense,
    Flatten,
    MaxPooling2D
)
from keras.layers.convolutional import (
    Conv2D,
    AveragePooling2D
)
from keras.layers.merge import add
from keras.layers.normalization import BatchNormalization
from keras.models import Model
from keras.regularizers import l2


def _bn_relu(input):
    """Helper to build a BN -> relu block
    """
    norm = BatchNormalization(axis=CHANNEL_AXIS)(input)
    return Activation("relu")(norm)

def _conv_bn_relu(**conv_params):
    """Helper to build a conv -> BN -> relu block
    """
    filters = conv_params["filters"]
    kernel_size = conv_params["kernel_size"]
    strides = conv_params.setdefault("strides", (1, 1))
    kernel_initializer = conv_params.setdefault("kernel_initializer", "he_normal")
    padding = conv_params.setdefault("padding", "same")
    kernel_regularizer = conv_params.setdefault("kernel_regularizer", l2(1.e-4))

    def f(input):
        conv = Conv2D(filters=filters, kernel_size=kernel_size,
                      strides=strides, padding=padding,
                      kernel_initializer=kernel_initializer,
                      kernel_regularizer=kernel_regularizer)(input)
        print(conv.shape)
        return _bn_relu(conv)

    return f


def _bn_relu_conv(**conv_params):
    """Helper to build a BN -> relu -> conv block.
    This is an improved scheme proposed in http://arxiv.org/pdf/1603.05027v2.pdf
    """
    filters = conv_params["filters"]
    kernel_size = conv_params["kernel_size"]
    strides = conv_params.setdefault("strides", (1, 1))
    kernel_initializer = conv_params.setdefault("kernel_initializer", "he_normal")
    padding = conv_params.setdefault("padding", "same")
    kernel_regularizer = conv_params.setdefault("kernel_regularizer", l2(1.e-4))

    def f(input):
        activation = _bn_relu(input)
        return Conv2D(filters=filters, kernel_size=kernel_size,
                      strides=strides, padding=padding,
                      kernel_initializer=kernel_initializer,
                      kernel_regularizer=kernel_regularizer)(activation)

    return f

# H(X) = f(x) + x 을 구현, f(x)는 residual x는 input이다. 두 인수의 shape이 다를 경우 Conv2D연산을 통해 맞춰준다.
def _shortcut(input, residual):
    """Adds a shortcut between input and residual block and merges them with "sum"
    """
    # Expand channels of shortcut to match residual.
    # Stride appropriately to match residual (width, height)
    # Should be int if network architecture is correctly configured.
    input_shape = K.int_shape(input)
    residual_shape = K.int_shape(residual)
    stride_width = int(round(input_shape[ROW_AXIS] / residual_shape[ROW_AXIS])) #round 는 반올림
    stride_height = int(round(input_shape[COL_AXIS] / residual_shape[COL_AXIS]))
    equal_channels = input_shape[CHANNEL_AXIS] == residual_shape[CHANNEL_AXIS]

    shortcut = input
    # 1 X 1 conv if shape is different. Else identity.
    # input과 residual의 shape이 다를 경우 동일하게 해준다.
    if stride_width > 1 or stride_height > 1 or not equal_channels:
        shortcut = Conv2D(filters=residual_shape[CHANNEL_AXIS],
                          kernel_size=(1, 1),
                          strides=(stride_width, stride_height),
                          padding="valid",
                          # 1 x 1 필터이므로 패딩이 의미가 없다. valid는 패딩을 안 한다는 의미,
                          # same은 입력과 출력이 같은 사이즈가 되도록 제로패딩, casual은 dilated convolution 연산에 쓰인다고함
                          kernel_initializer="he_normal",
                          kernel_regularizer=l2(0.0001))(input)

    return add([shortcut, residual])


# basic_block 또는 bottleneck_block을 repetitions 만큼 연달아 만든다. 여기서 reduce_output은 conv연산의 stride 를 조절한다.
# conv 연산의 stride가 2일 경우 입력이미지의 w,h의 절반 사이즈의 출력을 갖게 된다.
def _residual_block(block_function, filters, repetitions, is_first_layer=False, reduce_output=False):
    """Builds a residual block with repeating bottleneck blocks.
    """
    def f(input):
        for i in range(repetitions):
            init_strides = (1, 1)
            if i == 0 and reduce_output:
                init_strides = (2, 2)
            input = block_function(filters=filters, init_strides=init_strides,
                                   is_first_block_of_first_layer=(is_first_layer and i == 0))(input)
        return input

    return f


# 일반적인 Resnet 블록의 구조이다.
def basic_block(filters, init_strides=(1, 1), is_first_block_of_first_layer=False):
    """Basic 3 X 3 convolution blocks for use on resnets with layers <= 34.
    Follows improved proposed scheme in http://arxiv.org/pdf/1603.05027v2.pdf
    """
    def f(input):

        if is_first_block_of_first_layer:
            # don't repeat bn->relu since we just did bn->relu->maxpool
            conv1 = Conv2D(filters=filters, kernel_size=(3, 3),
                           strides=init_strides,
                           padding="same",
                           kernel_initializer="he_normal",
                           kernel_regularizer=l2(1e-4))(input)
        else:
            conv1 = _bn_relu_conv(filters=filters, kernel_size=(3, 3),
                                  strides=init_strides)(input)

        residual = _bn_relu_conv(filters=filters, kernel_size=(3, 3))(conv1)
        return _shortcut(input, residual)

    return f


# 연산량을 줄이기 위한 Resnet 블록의 구조이다. 1x1 Conv으로 depth를 줄인후 3x3 Conv을 수행하고 다시 1x1 Conv으로 depth를 늘려준다.
def bottleneck(filters, init_strides=(1, 1), is_first_block_of_first_layer=False):
    """Bottleneck architecture for > 34 layer resnet.
    Follows improved proposed scheme in http://arxiv.org/pdf/1603.05027v2.pdf
    Returns:
        A final conv layer of filters * 4
    """
    def f(input):

        if is_first_block_of_first_layer:
            # don't repeat bn->relu since we just did bn->relu->maxpool
            conv_1_1 = Conv2D(filters=filters, kernel_size=(1, 1),
                              strides=init_strides,
                              padding="same",
                              kernel_initializer="he_normal",
                              kernel_regularizer=l2(1e-4))(input)
        else:
            conv_1_1 = _bn_relu_conv(filters=filters, kernel_size=(1, 1),
                                     strides=init_strides)(input)

        conv_3_3 = _bn_relu_conv(filters=filters, kernel_size=(3, 3))(conv_1_1)
        residual = _bn_relu_conv(filters=filters * 4, kernel_size=(1, 1))(conv_3_3)
        return _shortcut(input, residual)

    return f


def _handle_dim_ordering(): #Tensorflow 는 (row, col, channel) 이고 theano (channel, row, col)
    global ROW_AXIS
    global COL_AXIS
    global CHANNEL_AXIS
    if K.image_dim_ordering() == 'tf':
        ROW_AXIS = 1
        COL_AXIS = 2
        CHANNEL_AXIS = 3
    else:
        CHANNEL_AXIS = 1
        ROW_AXIS = 2
        COL_AXIS = 3


# 위에서 선언한 basic_block, bottleneck 블록의 identifier를 입력받아 존재하는지 확인하고 존재한다면 해당함수를 반환
def _get_block(identifier):
    # Six 는 python 유틸리티 함수, isinstance는 파이썬 내장함수로 isinstance(object, classinfo) object의 인자가
    # classinfo 인자의 인스턴스 또는 서브클래스의 인스턴스이면 참을 반환한다. 나머지는 거짓을 돌려준다.
    if isinstance(identifier, six.string_types):
        res = globals().get(identifier)
        print(res)
        if not res:
            raise ValueError('Invalid {}'.format(identifier))
        return res
    return identifier


def get_resnet(input_shape, num_outputs):
    """Builds a custom ResNet like architecture.
        Args:
            input_shape: The input shape in the form (nb_channels, nb_rows, nb_cols)
            num_outputs: The number of outputs at final softmax layer
            block_fn: The block function to use. This is either `basic_block` or `bottleneck`.
                The original paper used basic_block for layers < 50
            repetitions: Number of repetitions of various block units.
                At each block unit, the number of filters are doubled and the input size is halved
        Returns:
            The keras `Model`.
        """
    # keras의 backend API는 tensorflow와 theano가 있다. 이 둘은 이미지 tensor의 순서가 다르므로 이를 정의하는 함수
    # 'tf' == tensorflow (row, col, channel), 'th' == theano (channel, row, col)
    _handle_dim_ordering()
    if len(input_shape) != 3:
        raise Exception("Input shape should be a tuple (nb_channels, nb_rows, nb_cols)")

        # Permute dimension order if necessary
    if K.image_dim_ordering() == 'tf':
        input_shape = (input_shape[1], input_shape[2], input_shape[0])

    # Load function from str if needed.
    bottleneck_fn = _get_block(bottleneck)
    basic_block_fn = _get_block(basic_block)

    #resnet34
    input = Input(shape=input_shape)
    conv1 = _conv_bn_relu(filters=64, kernel_size=(7, 7), strides=(1, 1))(input)
    pool1 = MaxPooling2D(pool_size=(3, 3), strides=(2, 2), padding="same")(conv1)
    block1 = _residual_block(basic_block_fn, filters=64, repetitions=3, is_first_layer=True, reduce_output=False)(pool1)
    block2 = _residual_block(basic_block_fn, filters=128, repetitions=4, is_first_layer=False, reduce_output=True)(block1)
    block3 = _residual_block(basic_block_fn, filters=256, repetitions=6, is_first_layer=False, reduce_output=True)(block2)
    final_block = _residual_block(basic_block_fn, filters=512, repetitions=3, is_first_layer=False, reduce_output=True)(block3)

    # Last activation
    block = _bn_relu(final_block)

    # Classifier block
    block_shape = K.int_shape(block)
    pool2 = AveragePooling2D(pool_size=(block_shape[ROW_AXIS], block_shape[COL_AXIS]), strides=(1, 1))(block)
    flatten1 = Flatten()(pool2)
    dense = Dense(units=num_outputs, kernel_initializer="he_normal", activation="sigmoid")(flatten1)

    model = Model(inputs=input, outputs=dense)
    return model




