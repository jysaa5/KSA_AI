import numpy as np
from keras.utils import to_categorical
from keras.datasets import cifar10
from keras.layers import Input, Flatten, Dense, Activation, Conv2D, LeakyReLU, Dropout, \
    BatchNormalization, MaxPooling2D
from keras.models import Model, Sequential
from keras.optimizers import Adam
from keras import backend as K
import matplotlib.pyplot as plt
from keras.models import load_model
from keras.preprocessing.image import ImageDataGenerator
from keras.regularizers import l2
# conv_1_1 = Conv2D(filters=32, kernel_size=(1, 1),
#                   strides=1,
#                   padding="same",
#                   kernel_initializer="he_normal",
#                   kernel_regularizer=l2(1e-4))(input)


# loss 그래프 그리는 함수
def plot_loss(history):
    plt.plot(history.history['loss'])
    plt.plot(history.history['val_loss'])
    plt.title('Model Loss')
    plt.ylabel('Loss')
    plt.xlabel('Epochs')
    plt.legend(['Train', 'val'], loc=0)

# accuracy 그래프 그리는 함수
def plot_acc(history):
    plt.plot(history.history['acc'])
    plt.plot(history.history['val_acc'])
    plt.title('Model accuracy')
    plt.ylabel('Accuracy')
    plt.xlabel('Epochs')
    plt.legend(['Train', 'val'], loc=0)

# input image dimensions
img_rows, img_cols = 32, 32

# 데이터 로드
(x_train, y_train), (x_test, y_test) = cifar10.load_data()
print("Training data:")
print("Number of examples: ", x_train.shape[0])
print("Number of channels:",x_train.shape[3])
print("Image size:", x_train.shape[1], x_train.shape[2])
print('\n')
print("Test data:")
print("Number of examples:", x_test.shape[0])
print("Number of channels:", x_test.shape[3])
print("Image size:", x_test.shape[1], x_test.shape[2])

# tensorflow backend 사용시 (Height, Width, channel)으로 입력 , Theano backend 사용시 (channel, Height, Width)으로 입력
if K.image_data_format() == 'th':
    X_train = x_train.reshape(x_train.shape[0], 3, img_rows, img_cols)
    X_test = x_test.reshape(x_test.shape[0], 3, img_rows, img_cols)
    input_shape = (3, img_rows, img_cols)
else:
    X_train = x_train.reshape(x_train.shape[0], img_rows, img_cols, 3)
    X_test = x_test.reshape(x_test.shape[0], img_rows, img_cols, 3)
    input_shape = (img_rows, img_cols, 3)

NUM_CLASSES = 10
data_augmentation = True

# 데이터 정규화 부분
x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0

# 정답 label one-hot encoding
y_train = to_categorical(y_train, NUM_CLASSES)
y_test = to_categorical(y_test, NUM_CLASSES)

#######################################################
# 모델 만들기
# # Sequential()
# model = Sequential()
# model.add(Conv2D(32, kernel_size=(3,3), padding='same', strides=1, input_shape=input_shape, name='Conv1'))
# model.add(LeakyReLU(name='relu_1'))
# model.add(Conv2D(32, kernel_size=(3,3), padding='same', strides=2, name='Conv2'))
# model.add(LeakyReLU(name='relu_2'))
# model.add(Conv2D(64, kernel_size=(3,3), padding='same', strides=1, name='Conv3'))
# model.add(LeakyReLU(name='relu_3'))
# model.add(Conv2D(64, kernel_size=(3,3), padding='same', strides=2, name='Conv4'))
# model.add(LeakyReLU(name='relu_4'))
# model.add(Flatten())
# model.add(Dense(128, name='hidden_1'))
# model.add(LeakyReLU(name='relu_5'))
# model.add(Dense(NUM_CLASSES, name='hidden_2'))
# model.add(Activation('softmax', name='output_tensor'))
# model.summary()

# Function()
input_layer = Input(shape=(32, 32, 3))
x = Conv2D(filters=32, kernel_size=3, strides=1, padding='same')(input_layer)
x = BatchNormalization()(x)
x = LeakyReLU()(x)
x = Conv2D(filters=32, kernel_size=3, strides=1, padding='same')(x)
x = BatchNormalization()(x)
x = LeakyReLU()(x)
x = MaxPooling2D(pool_size=(2,2))(x)
x = Dropout(rate=0.25)(x)
x = Conv2D(filters=64, kernel_size=3, strides=1, padding='same')(x)
x = BatchNormalization()(x)
x = LeakyReLU()(x)
x = Conv2D(filters=64, kernel_size=3, strides=1, padding='same')(x)
x = BatchNormalization()(x)
x = LeakyReLU()(x)
x = MaxPooling2D(pool_size=(2,2))(x)
x = Dropout(rate=0.25)(x)
x = Flatten()(x)
x = Dense(512)(x)
x = BatchNormalization()(x)
x = LeakyReLU()(x)
x = Dropout(rate=0.5)(x)
x = Dense(NUM_CLASSES)(x)
output_layer = Activation('softmax')(x)
model = Model(input_layer, output_layer)
model.summary()
############################################################
# 모델 컴파일
opt = Adam(lr=0.0005)
model.compile(loss='categorical_crossentropy', optimizer=opt, metrics=['accuracy'])
##############################################################
# 모델 훈련

if not data_augmentation:
    print('Not using data augmentation.')
    history = model.fit(x_train, y_train,
                        batch_size=16,
                        epochs=5,
                        verbose=1,
                        validation_split=0.2)
else:
    print('Using real-time data augmentation.')
    # This will do preprocessing and realtime data augmentation:
    datagen = ImageDataGenerator(
        featurewise_center=False,  # set input mean to 0 over the dataset
        samplewise_center=False,  # set each sample mean to 0
        featurewise_std_normalization=False,  # divide inputs by std of the dataset
        samplewise_std_normalization=False,  # divide each input by its std
        zca_whitening=False,  # apply ZCA whitening
        zca_epsilon=1e-06,  # epsilon for ZCA whitening
        rotation_range=0,  # randomly rotate images in the range (degrees, 0 to 180)
        # randomly shift images horizontally (fraction of total width)
        width_shift_range=0.1,
        # randomly shift images vertically (fraction of total height)
        height_shift_range=0.1,
        shear_range=0.,  # set range for random shear
        zoom_range=0.,  # set range for random zoom
        channel_shift_range=0.,  # set range for random channel shifts
        # set mode for filling points outside the input boundaries
        fill_mode='nearest',
        cval=0.,  # value used for fill_mode = "constant"
        horizontal_flip=True,  # randomly flip images
        vertical_flip=False,  # randomly flip images
        # set rescaling factor (applied before any other transformation)
        rescale=None,
        # set function that will be applied on each input
        preprocessing_function=None,
        # image data format, either "channels_first" or "channels_last"
        data_format=None,
        # fraction of images reserved for validation (strictly between 0 and 1)
        validation_split=0.0)

    # Compute quantities required for feature-wise normalization
    # (std, mean, and principal components if ZCA whitening is applied).
    datagen.fit(x_train)

    # Fit the model on the batches generated by datagen.flow().
    history = model.fit_generator(datagen.flow(x_train, y_train, batch_size=16),
                        epochs=5,
                        steps_per_epoch=50000, verbose=1,
                        validation_data=(x_test, y_test))

model.save('save.h5')
# 모델평가
print('\nAccuracy: {:.4f}'.format(model.evaluate(x_test, y_test, verbose=0)[1]))
print('\nloss: {:.4f}'.format(model.evaluate(x_test, y_test, verbose=0)[0]))

# 학습 loss 값 과 accuracy 결과 그래프
plot_loss(history)
plt.show()
plot_acc(history)
plt.show()


import matplotlib.pyplot as plt
import random
import numpy as np
from keras.datasets import cifar10
from keras.models import load_model
from keras.utils import to_categorical
(x_train, y_train), (x_test, y_test) = cifar10.load_data()

model = load_model('save.h5')
model.summary()

NUM_CLASSES = 10
x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0

# 정답 label one-hot encoding
y_train = to_categorical(y_train, NUM_CLASSES)
y_test = to_categorical(y_test, NUM_CLASSES)

print('\nAccuracy: {:.4f}'.format(model.evaluate(x_test, y_test, verbose=1)[1]))
print('\nloss: {:.4f}'.format(model.evaluate(x_test, y_test, verbose=1)[0]))

# 학습모델 결과 이미지 추출용
CLASSES = np.array(['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck'])

preds = model.predict(x_test)
preds_single = CLASSES[np.argmax(preds, axis=-1)]
actual_single = CLASSES[np.argmax(y_test, axis=-1)]

n_to_show = 10
indices = np.random.choice(range(len(x_test)), n_to_show)

fig = plt.figure(figsize=(15, 3))
fig.subplots_adjust(hspace=0.4, wspace=0.4)

for i, idx in enumerate(indices):
    img = x_test[idx]
    ax = fig.add_subplot(1, n_to_show, i+1)
    ax.axis('off')
    ax.text(0.5, -0.35, 'pred = ' + str(preds_single[idx]), fontsize=10, ha='center', transform=ax.transAxes)
    ax.text(0.5, -0.7, 'act = ' + str(actual_single[idx]), fontsize=10, ha='center', transform=ax.transAxes)
    ax.imshow(img)

plt.show()




