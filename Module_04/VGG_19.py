# VGG16

from keras.layers import Input, Flatten, Dense, Activation, Conv2D, LeakyReLU, Dropout, MaxPooling2D
from keras.models import Model

img_input = Input(shape=(224, 224, 3))

# Block1
x = Conv2D(64, kernel_size=(3, 3), activation='relu', padding='same', name='block1_conv1')(img_input)
x = Conv2D(64, kernel_size=(3, 3), activation='relu', padding='same', name='block1_conv2')(x)
x = MaxPooling2D((2, 2), strides=(2, 2), name='block1_pool')(x)

# Block2
x = Conv2D(128, kernel_size=(3, 3), activation='relu', padding='same', name='block2_conv1')(img_input)
x = Conv2D(128, kernel_size=(3, 3), activation='relu', padding='same', name='block2_conv2')(x)
x = MaxPooling2D((2, 2), strides=(2, 2), name='block2_pool')(x)

# Block3
x = Conv2D(256, kernel_size=(3, 3), activation='relu', padding='same', name='block3_conv1')(img_input)
x = Conv2D(256, kernel_size=(3, 3), activation='relu', padding='same', name='block3_conv2')(x)
x = Conv2D(256, kernel_size=(3, 3), activation='relu', padding='same', name='block3_conv3')(x)
x = Conv2D(256, kernel_size=(3, 3), activation='relu', padding='same', name='block3_conv4')(x)
x = MaxPooling2D((2, 2), strides=(2, 2), name='block3_pool')(x)

# Block4
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block4_conv1')(img_input)
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block4_conv2')(x)
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block4_conv3')(x)
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block4_conv4')(x)
x = MaxPooling2D((2, 2), strides=(2, 2), name='block4_pool')(x)

# Block5
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block5_conv1')(img_input)
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block5_conv2')(x)
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block5_conv3')(x)
x = Conv2D(512, kernel_size=(3, 3), activation='relu', padding='same', name='block5_conv4')(x)
x = MaxPooling2D((2, 2), strides=(2, 2), name='block5_pool')(x)

x = Flatten(name='Flatten')(x)
x = Dense(units=4096, activation='relu')(x)
x = Dense(units=4096, activation='relu')(x)
x = Dense(units=1000, activation='relu')(x)
output_layer = Activation('softmax')(x)

model = Model(img_input, output_layer)
model.summary()