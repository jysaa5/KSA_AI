from __future__ import absolute_import, division, print_function, unicode_literals, unicode_literals

import numpy as np
from keras.models import Sequential, Model
from keras.layers import Dense, Activation, Flatten
from keras.layers import Conv2D, MaxPooling2D, Input
from keras.utils import np_utils
from keras import backend as K
import matplotlib.pyplot as plt

# loss 그래프 그리는 함수
from tensorflow import keras
import tensorflow as tf
print(tf.__version__)

def plot_loss(history):
    plt.plot(history.history['loss'])
    plt.plot(history.history['val_loss'])
    plt.title('Model Loss')
    plt.ylabel('Loss')
    plt.xlabel('Epochs')
    plt.legend(['Train', 'val'], loc=0)

# accuracy 그래프 그리는 함수
def plot_acc(history):
    plt.plot(history.history['accuracy'])
    plt.plot(history.history['val_accuracy'])
    plt.title('Model accuracy')
    plt.ylabel('Accuracy')
    plt.xlabel('Epochs')
    plt.legend(['Train', 'val'], loc=0)

np.random.seed(1337)  # for reproducibility

# 하이퍼파라미터 설정
batch_size = 128
nb_classes = 10
#nb_epoch = 20
nb_epoch = 100

# 입력 이미지 사이즈 정보
img_rows, img_cols = 28, 28
# number of convolutional filters to use
#nb_filters = 32
nb_filters = 32


# the data, shuffled and split between train and test sets
fashion_mnist = keras.datasets.fashion_mnist
(X_train, y_train), (X_test, y_test) = fashion_mnist.load_data()

class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

# 데이터 탐색
X_train.shape
len(y_train)
y_train
X_test.shape
len(y_test)

# 데이터 전처리
plt.figure()
plt.imshow(X_train[0])
plt.colorbar()
plt.grid(False)
plt.show()

print("Training data:")
print("Number of examples: ", X_train.shape[0])
print("Image size:", X_train.shape[1], X_train.shape[2])
print('\n')
print("Test data:")
print("Number of examples:", X_test.shape[0])
print("Image size:", X_test.shape[1], X_test.shape[2])
print('\n')

# # mnist 데이터 이미지 추출 부분
# plt.imshow(X_train[20].reshape(28, 28), cmap='Greys')
# tmp = "Label:" + str(y_train[20])
# plt.title(tmp, fontsize=30)
# plt.tight_layout()
# plt.show()

# tensorflow backend 사용시 (Height, Width, channel) 순 입력 , Theano backend 사용시 (channel, Height, Width) 순 입력
if K.image_data_format() == 'th':
    X_train = X_train.reshape(X_train.shape[0], 1, img_rows, img_cols)
    X_test = X_test.reshape(X_test.shape[0], 1, img_rows, img_cols)
    input_shape = (1, img_rows, img_cols)
else:
    X_train = X_train.reshape(X_train.shape[0], img_rows, img_cols, 1)
    X_test = X_test.reshape(X_test.shape[0], img_rows, img_cols, 1)
    input_shape = (img_rows, img_cols, 1)

# 데이터 정규화 부분
X_train = X_train.astype('float32')
X_test = X_test.astype('float32')
X_train /= 255
X_test /= 255

plt.figure(figsize=(10, 10))

for i in range(25):
    plt.subplot(5, 5, i+1)
    plt.xticks([])
    plt.yticks([])
    plt.grid(False)
    plt.imshow(X_train[i], cmap=plt.cm.binary)
    plt.xlabel(class_names[y_train[i]])
plt.show()


print(X_train.shape[0], 'train samples')
print(X_test.shape[0], 'test samples')

# 정답 label one-hot encoding
Y_train = np_utils.to_categorical(y_train, nb_classes)
Y_test = np_utils.to_categorical(y_test, nb_classes)

# # one-hot encoding print 부분
# print('y_train_ori : {}'.format(y_train[:5]))
# print('\n')
# print('y_train_one-hot-endcoing : {}'.format(Y_train[:5]))


# Sequential()
model = Sequential()
model.add(Conv2D(nb_filters, kernel_size=(3, 3), padding='valid', input_shape=input_shape, name='Conv_1'))
model.add(Activation('relu', name='relu_1'))
model.add(Conv2D(nb_filters, kernel_size=(3, 3), name='Conv_2'))
model.add(Activation('relu', name='relu_2'))
model.add(Conv2D(nb_filters, kernel_size=(3, 3), name='Conv_3'))
model.add(Activation('relu', name='relu_3'))
model.add(Conv2D(nb_filters, kernel_size=(3, 3), name='Conv_4'))
model.add(Activation('relu', name='relu_4'))
model.add(MaxPooling2D(pool_size=(2, 2), name='pool_1'))
model.add(Flatten())
model.add(Dense(256, name='hidden_1'))
model.add(Dense(256, name='hidden_2'))
model.add(Dense(256, name='hidden_3'))
# model.add(Dense(256, name='hidden_4'))
# model.add(Dense(256, name='hidden_5'))
# model.add(Dense(256, name='hidden_6'))
model.add(Activation('relu', name='relu_5'))
model.add(Dense(nb_classes, name='hidden_7'))
model.add(Activation('softmax', name='output_tensor'))
model.summary()

# Function()
# input_tensor = Input(shape=input_shape)
# x = Conv2D(nb_filters, kernal_size = (3,3), padding='valid', name='Conv1')(input_tensor)
# x = Activation('relu', name='relu_1')(x)
# x = Conv2D(nb_filters, kernel_size=(3,3), padding='valid', name='Conv2')(x)
# x = Activation('relu', name='relu_2')(x)
# x = MaxPooling2D(pool_size=(2,2), name='pool_1')(x)
# x = Flatten()(x)
# x = Dense(units=120, name='hidden_1')(x)
# x = Activation('relu', name='hidden_2')(x)
# x = Dense(units=nb_classes, name='hidden_2')(x)
# output_tensor = Activation('softmax', name = 'output_tensor')(x)
# model = Model(inputs=input_tensor, outputs=output_tensor)
# model.surmmary()


model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
# validation_split = 0.2
history = model.fit(X_train, Y_train, batch_size=batch_size, epochs=nb_epoch, verbose=1, validation_split=0.15)

print('\n')
print('Test start')
score = model.evaluate(X_test, Y_test, verbose=1)
print('Test loss:', score[0])
print('Test accuracy:', score[1])

# 학습 loss 값 과 accuracy 결과 그래프
plot_loss(history)
plt.show()
plot_acc(history)
plt.show()