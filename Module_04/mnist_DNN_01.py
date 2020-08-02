import keras
from keras.datasets import mnist
from keras.models import Sequential, Model
from keras.layers import Dense, Dropout, Input, Activation
import matplotlib.pyplot as plt
import numpy as np

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
    plt.plot(history.history['accuracy'])
    plt.plot(history.history['val_accuracy'])
    plt.title('Model accuracy')
    plt.ylabel('Accuracy')
    plt.xlabel('Epochs')
    plt.legend(['Train', 'val'], loc=0)

np.random.seed(1337)  # for reproducibility

# 하이퍼파라미터 설정
batch_size = 128
num_classes = 10
epochs = 12
# ==============================================================================
# 데이터 로드
(X_train, y_train), (X_test, y_test) = mnist.load_data()
print("Training data:")
print("Number of examples: ", X_train.shape[0])
print("Image size:", X_train.shape[1], X_train.shape[2])
print('\n')
print("Test data:")
print("Number of examples:", X_test.shape[0])
print("Image size:", X_test.shape[1], X_test.shape[2])
print('\n')

# # mnist 데이터 이미지 추출 부분
# plt.imshow(X_train[33].reshape(28, 28), cmap='Greys')
# tmp = "Label:" + str(y_train[33])
# plt.title(tmp)
# plt.tight_layout()
# plt.show()

L, W, H = X_train.shape
X_train = X_train.reshape(60000, W * H)
X_test = X_test.reshape(10000, W * H)

# 데이터 정규화 부분
X_train = X_train.astype('float32')
X_test = X_test.astype('float32')
X_train /= 255
X_test /= 255

print(X_train.shape[0], 'train samples')
print(X_test.shape[0], 'test samples')

# 정답 label one-hot encoding
y_train = keras.utils.to_categorical(y_train, num_classes)
y_test = keras.utils.to_categorical(y_test, num_classes)


# ==============================================================================
# build model

# Function()
input_tensor = Input(shape=(784,), name='input_tensor')
hidden_1 = Dense(units=256, activation='relu', name='hidden_1')(input_tensor)
hidden_2 = Dense(units=256, activation='relu', name='hidden_2')(hidden_1)
hidden_3 = Dense(units=256, activation='relu', name='hidden_3')(hidden_2)
hidden_4 = Dense(units=256, activation='relu', name='hidden_4')(hidden_3)
output_tensor = Dense(num_classes, activation='softmax', name ='output_tensor')(hidden_4)
model = Model(inputs=input_tensor, outputs=output_tensor)
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
model.summary()


#sequential()
#model = Sequential()
#model.add(Dense(256, activation='relu', name ='input_tensor', input_shape=(784,)))
#model.add(Dense(256, activation='relue', name='hidden_1'))
#model.add(Dense(256, activation='relue', name='hidden_2'))
#model.add(Dense(256, activation='relue', name='hidden_3'))
#model.add(Dense(num_classes, activation='softmax', name="output_tensor"))
#model.complie(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
#model.summary()

history = model.fit(X_train, y_train,
                    batch_size=batch_size,
                    epochs=epochs,
                    verbose=1,
                    validation_split=0.2)

# ==============================================================================
# predict
print('Test start')
score = model.evaluate(X_test, y_test, batch_size=batch_size)
print('\nTest loss:', score[0])
print('Test accuracy:', score[1])

# 학습 loss 값 과 accuracy 결과 그래프
plot_loss(history)
plt.show()
plot_acc(history)
plt.show()