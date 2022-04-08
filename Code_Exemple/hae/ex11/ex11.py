# ex11
import os; os.environ['TF_CPP_MIN_LOG_LEVEL']='3'
import tensorflow.keras as keras
from keras.datasets import fashion_mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten
from tensorflow.keras import optimizers
from matplotlib import pyplot as plt
import numpy as np; import sys

(AX, AY), (QX, QY) = fashion_mnist.load_data()
AX=255-AX; QX=255-QX

nclasses = 10
AY2 = keras.utils.to_categorical(AY, nclasses)
QY2 = keras.utils.to_categorical(QY, nclasses)

nl, nc = AX.shape[1], AX.shape[2] #28, 28
AX = (AX.astype('float32')/255.0)-0.5 # -0.5 a +0.5
QX = (QX.astype('float32')/255.0)-0.5 # -0.5 a +0.5

model = Sequential()
model.add(Flatten(input_shape=(nl,nc)))
model.add(Dense(400, activation='relu'))
model.add(Dense(100, activation='relu'))
model.add(Dense(nclasses, activation='softmax'))

opt=optimizers.Adam()
model.compile(optimizer=opt, loss='categorical_crossentropy',
              metrics=['accuracy'])
model.fit(AX, AY2, batch_size=100, epochs=160, verbose=2);

score = model.evaluate(QX, QY2, verbose=False)
print('Test loss: %.4f'%(score[0]))
print('Test accuracy: %.2f %%'%(100*score[1]))
print('Test error: %.2f %%'%(100*(1-score[1])))
model.save('mlp2.h5')

QYw = ['camiseta' if j == 0 else 'calça' if j == 1 else 'Pulôver' if j == 2 else 'Vestido' if j == 3 else 'Casaco' if j == 4 else 'Sandália' if j == 5 else 'Camiseta' if j == 6 else 'Tênis' if j == 7 else 'Bolsa' if j == 8 else 'Botins' if j == 9  else j for j in QY]
QPw = ['camiseta' if j == 0 else 'calça' if j == 1 else 'Pulôver' if j == 2 else 'Vestido' if j == 3 else 'Casaco' if j == 4 else 'Sandália' if j == 5 else 'Camiseta' if j == 6 else 'Tênis' if j == 7 else 'Bolsa' if j == 8 else 'Botins' if j == 9  else j for j in QP]

f = plt.figure()
for i in range(20):
  f.add_subplot(4,5,i+1)
  plt.imshow( QX[237+i], cmap="gray")
  plt.axis("off");
  plt.text(0,-3,QYw[237+i],color="b")
  plt.text(0, 2,QPw[237+i],color="r")
plt.savefig("comparacao_resultados.png")
plt.show()

#600/600 - 1s - loss: 0.0186 - accuracy: 0.9943
#Logo o erro de treino foi 0.57%
#Test loss: 1.1650
#Test accuracy: 89.45 %
#Test error: 10.55 %