import ResNet as resnet

img_rows, img_cols = 112, 112
img_channels = 3
feature_vecs = 4096

siamese_network = resnet.get_resnet((img_channels, img_rows, img_cols), feature_vecs)
siamese_network.summary()