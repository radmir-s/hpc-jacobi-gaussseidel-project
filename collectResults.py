import os
import numpy as np

Size = [32, 128, 512, 2048, 8192]
Inner1 = [1, 2, 4, 8, 16, 48, 96]
Inner2 = [1, 2, 4, 8, 12]
Outer2 = [1, 2, 4, 8, 12]
Loop = [1, 2, 4, 8]

dim = tuple(map(len,(Size, Inner1, Inner2, Outer2, Loop)))

gstime = np.zeros(dim) 
gsl1 = np.zeros(dim)
gsl2 = np.zeros(dim) 
gsl3 = np.zeros(dim) 

for s, size in enumerate(Size):
    for i1, inner1 in enumerate(Inner1):
        for i2, inner2 in enumerate(Inner2):
            for o2, outer2 in enumerate(Outer2):
                for l, loop in enumerate(Loop):
                    if inner2!=12 or outer2!=12:
                        filepath = f"results/gs-{size}-{inner1}-{inner2}-{outer2}-{loop}.txt"
                        with open(filepath,"r") as reader:
                            for line in reader.readlines():
                                if line.startswith("Time"):
                                    gstime[s, i1, i2, o2, l] = float(line.split()[-2])

for L, array in (("l1", gsl1), ("l2", gsl2), ("l3", gsl3)):                                  
    for s, size in enumerate(Size):
        for i1, inner1 in enumerate(Inner1):
            for i2, inner2 in enumerate(Inner2):
                for o2, outer2 in enumerate(Outer2):
                    for l, loop in enumerate(Loop):
                        if inner2!=12 or outer2!=12:
                            filepath = f"results/gs-{L}-{size}-{inner1}-{inner2}-{outer2}-{loop}.txt"
                            with open(filepath,"r") as reader:
                                for line in reader.readlines():
                                    if "main" in line:
                                        array[s, i1, i2, o2, l] = float(line.split()[1]) 

np.save("gstime.npy", gstime)
np.save("gsl1.npy", gsl1)
np.save("gsl2.npy", gsl2)
np.save("gsl3.npy", gsl3)


Size = [32, 128, 512, 2048, 8192]
Inner = [1, 2, 4, 8, 12]
Outer = [1, 2, 4, 8, 12]
Loop = [1, 2, 4, 8]

dim = tuple(map(len,(Size, Inner, Outer, Loop)))

jactime = np.zeros(dim) 
jacl1 = np.zeros(dim)
jacl2 = np.zeros(dim) 
jacl3 = np.zeros(dim) 

for s, size in enumerate(Size):
    for i, inner in enumerate(Inner):
        for o, outer in enumerate(Outer):
            for l, loop in enumerate(Loop):
                if inner!=12 or outer!=12:
                    filepath = f"results/jacobi-{size}-{inner}-{outer}-{loop}.txt"
                    with open(filepath,"r") as reader:
                        for line in reader.readlines():
                            if line.startswith("Time"):
                                jactime[s, i, o, l] = float(line.split()[-1])

for L, array in (("l1", jacl1), ("l2", jacl2), ("l3", jacl3)):                     
    for s, size in enumerate(Size):
        for i, inner in enumerate(Inner):
            for o, outer in enumerate(Outer):
                for l, loop in enumerate(Loop):
                    if inner!=12 or outer!=12:
                        filepath = f"results/jacobi-{L}-{size}-{inner}-{outer}-{loop}.txt"
                        with open(filepath,"r") as reader:
                            for line in reader.readlines():
                                if "main" in line:
                                    array[s, i, o, l] = float(line.split()[1])

np.save("jactime.npy", jactime)
np.save("jacl1.npy", jacl1)
np.save("jacl2.npy", jacl2)
np.save("jacl3.npy", jacl3)