#bank_nn.py
import numpy as np
from sklearn import neighbors

def le(nomearq):
    with open(nomearq,"r") as f:
        linhas=f.readlines()
    linha0=linhas[0].split()
    nl=int(linha0[0]); nc=int(linha0[1])
    a=np.empty((nl,nc),dtype=np.float32)
    for l in range(nl):
        linha=linhas[l+1].split()
        for c in range(nc):
            a[l,c]=np.float32(linha[c])
    return a

### main
ax=le("ax.txt"); ay=le("ay.txt")
qx=le("qx.txt"); qy=le("qy.txt")

vizinho = neighbors.KNeighborsClassifier(n_neighbors=1, weights="uniform")
vizinho.fit(ax,ay.ravel())
qp = vizinho.predict(qx)
print("qp: ",qp)

erros = 0

for l in range(len(qp)):
    if qp[l] != qy[l]:
        erros += 1
print("Numero de erros = ", erros)