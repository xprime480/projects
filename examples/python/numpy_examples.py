#!/usr/bin/env python


import numpy as np

a = np.array(range(7), float)
print (a)
print (type(a))
print (a[2])
print ('==================================')

b = np.array([[1,2,3],[8,7,6]], float)
print (b)
print (b.shape)
print (b.dtype)
print (b[:,2])
print (b[:,2].shape)
print ([x in b for x in range(10)])
print (any([x in b for x in range(10)]))
print ('==================================')

c = b.reshape((3,2))
print (b)
print (c)
print ('==================================')

d = b.copy()
d.fill(3)
print (d)
print (d.transpose())
print ('==================================')

e = np.concatenate((c,d.transpose()))
print (e)
f = np.concatenate((c,d.transpose()), axis=1)
print (f)
print ('==================================')

print (b[:,2])
print (b[:,2][:,np.newaxis])
print ('==================================')

g = np.arange(5, dtype=float)
print (g)
h = np.ones((3,3), dtype=float)
print (h)
i = np.zeros((3,3), dtype=float)
print (i)
j = np.identity(4, dtype=int)
print (j)
k = np.eye(4, k=-1, dtype=int)
print (k)
print (j+k)
print ((j+k).sum())
print ('==================================')

print (np.mean(j+k))
print (np.mean(range(5)))
print (b.argmax())
print (b.sum(axis=1))
print (b.diagonal())
print ('==================================')

print (k>j)
print (1/(1+j))
l = np.where(k == 0, 3, k)
l[0,-1] = 0
print (l)
print (l[l>0])
print ('==================================')

del a,b,c,d,e,f,g,h,i,j,k,l

a = np.array([1, 3, 5], float)
b = np.array([0, -1, 4], float)
print (np.dot(a, b))
c = np.outer(a,b)
print (c)
print (np.dot(c,c.transpose()))
print ('==================================')


print (np.linalg.det(2 * np.identity(4, dtype=float)))
print (np.linalg.inv(2 * np.identity(4, dtype=float)))
print ('==================================')

print (np.random.rand(2,3,2))
print (np.dot(np.random.rand(8), np.random.rand(8)))
d = np.random.poisson(5.1, size=16).reshape((4,4)) - 5
print (d)
print (np.linalg.det(d))
