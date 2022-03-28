from email.charset import QP
import numpy as np
from sympy import QQ_python
ax = np.matrix("4; 15; 65; 5; 18; 70", dtype=np.float32)
ay = np.matrix("1; 2; 0; 1; 2; 0", dtype=np.float32)
qx = np.matrix("16; 3; 75", dtype=np.float32)
qy = np.matrix("2; 1; 0", dtype=np.float32)
qp = np.matrix("0; 0; 0", dtype=np.float32)
menorAy = 0

for iq in range(len(qx)):
    menorDist = float("inf")
    for ia in range(len(ax)):
        dist = abs(ax[ia]-qx[iq])
        if dist < menorDist:
            menorDist = dist
            menorAy = ay[ia]
    qp[iq] = menorAy

print("qp:\n")
print(qp)
print("\n qy: \n")
print(qy)