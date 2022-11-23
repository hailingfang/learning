import ctypes
mymod = ctypes.CDLL("myso.so")
c = mymod.myadd(1, 2)
print(c)

