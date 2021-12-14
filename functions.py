import os
import numpy as np
import matplotlib.pyplot as plt

def jacplot(array,size="-",inner="-",outer="-",loop="-"):
    Size = [32, 128, 512, 2048, 8192]
    Inner = [1, 2, 4, 8, 12]
    Outer = [1, 2, 4, 8, 12]
    Loop = [1, 2, 4, 8]
    if size in Size:
        s = Size.index(size)
        array = array[s:s+1]
    if inner in Inner:
        i = Inner.index(inner)
        array = array[:,i:i+1]
    if outer in Outer:
        o = Outer.index(outer)
        array = array[:,:,o:o+1]
    if loop in Loop:
        l = Loop.index(loop)
        array = array[:,:,:,l:l+1]
    plt.plot(array.flatten(),".-")
    plt.title(f"Jacobi Time:\nsize {size}, inner {inner}, outer {outer}, loop {loop}",fontsize=16)
    
def gsplot(array,size="-",inner1="-",inner2="-",outer2="-",loop="-"):
    Size = [32, 128, 512, 2048, 8192]
    Inner1 = [1, 2, 4, 8, 16, 48, 96]
    Inner2 = [1, 2, 4, 8, 12]
    Outer2 = [1, 2, 4, 8, 12]
    Loop = [1, 2, 4, 8]
    if size in Size:
        s = Size.index(size)
        array = array[s:s+1]
    if inner1 in Inner1:
        i1 = Inner1.index(inner1)
        array = array[:,i1:i1+1]
    if inner2 in Inner2:
        i2 = Inner2.index(inner2)
        array = array[:,i2:i2+1]
    if outer2 in Outer2:
        o2 = Outer2.index(outer2)
        array = array[:,:,o2:o2+1]
    if loop in Loop:
        l = Loop.index(loop)
        array = array[:,:,:,l:l+1]
    plt.plot(array.flatten(),".-")
    plt.title(f"Gauss-Seidel Time:\nsize {size}, inner1 {inner1}, inner2 {inner2}, outer2 {outer2}, loop {loop}",fontsize=16)

    