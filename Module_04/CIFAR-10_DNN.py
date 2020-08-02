import numpy as np
from keras.utils import to_categorical
from keras.datasets import cifar10
from keras.layers import Input, Flatten, Dense, Activation
from keras.models import Model, Sequential
from keras.optimizers import Adam
import matplotlib.pyplot as plt

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

# # Cifar-10 데이터 이미지 추출 부분
# CLASSES = np.array(['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck'])
# actual_single = CLASSES[y_train]
# plt.imshow(x_train[20], interpolation="bicubic")
# tmp = "Label:" + str(actual_single[20])
# plt.title(tmp, fontsize=30)
# plt.tight_layout()
# plt.show()

NUM_CLASSES = 10

# 데이터 정규화 부분
x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0

# 정답 label one-hot encoding
y_train = to_categorical(y_train, NUM_CLASSES)
y_test = to_categorical(y_test, NUM_CLASSES)

#######################################################
# 모델 만들기
input_layer = Input(shape=(32, 32, 3))
x = Flatten()(input_layer)
x = Dense(units=200, activation='relu')(x)
x = Dense(units=150, activation='relu')(x)
x = Dense(units=256, activation='relu')(x)
output_layer = Dense(units=10, activation='softmax')(x)
model = Model(input_layer, output_layer)
############################################################
# 모델 컴파일
opt = Adam(lr=0.0002)
model.compile(loss='categorical_crossentropy', optimizer=opt, metrics=['accuracy'])
##############################################################
# 모델 훈련
history = model.fit(x_train, y_train,
                    batch_size=16,
                    epochs=20,
                    verbose=1,
                    validation_split=0.2)

# 모델평가
print('\nAccuracy: {:.4f}'.format(model.evaluate(x_test, y_test, verbose=0)[1]))
print('\nloss: {:.4f}'.format(model.evaluate(x_test, y_test, verbose=0)[0]))

# 학습 loss 값 과 accuracy 결과 그래프
plot_loss(history)
plt.show()
plot_acc(history)
plt.show()


# # 학습모델 결과 이미지 추출용
# CLASSES = np.array(['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck'])
#
# preds = model.predict(x_test)
# preds_single = CLASSES[np.argmax(preds, axis=-1)]
# actual_single = CLASSES[np.argmax(y_test, axis=-1)]
#
# n_to_show = 10
# indices = np.random.choice(range(len(x_test)), n_to_show)
#
# fig = plt.figure(figsize=(15, 3))
# fig.subplots_adjust(hspace=0.4, wspace=0.4)
#
# for i, idx in enumerate(indices):
#     img = x_test[idx]
#     ax = fig.add_subplot(1, n_to_show, i+1)
#     ax.axis('off')
#     ax.text(0.5, -0.35, 'pred = ' + str(preds_single[idx]), fontsize=10, ha='center', transform=ax.transAxes)
#     ax.text(0.5, -0.7, 'act = ' + str(actual_single[idx]), fontsize=10, ha='center', transform=ax.transAxes)
#     ax.imshow(img)
#
# plt.show()


