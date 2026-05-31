import sys
import numpy as np
import matplotlib.pyplot as plt

dt = [[[int(n) for n in ele.split(",")] for ele in line.rstrip().split('\t')] for line in open(sys.argv[1])]
dt = np.asarray(dt, dtype=np.uint8)
fig, ax = plt.subplots()
ax.imshow(dt)
fig.savefig("test_out.tif")
