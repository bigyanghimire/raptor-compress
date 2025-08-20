#fname = raw_input("Enter file name: ")
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
import re
matplotlib.use('Agg')

it=[]
cr=[]
ops=[]
levels=[]
ds=[]
def get_compression_ratio(line):
    return 5

def get_iteration(line):
    return 5

def get_level(line):
    return 5

def get_datasize(line):
    return 5

def get_op(line):
    return "Smooth"

with open("slurm-5000.output") as fh:
    for line in fh:
        if line.startswith("Compression"):
            pattern = (
                r"Compression Ratio rank 0:\s*([\d.]+).*?"
                r"Amg iter:\s*(\d+).*?"
                r"Amg level:\s*(\d+).*?"
                r"Datasize:\s*(\d+).*?"
                r"Operation:\s*(\w+)"
            )

            match = re.search(pattern, line)
            if match:
                compression_ratio = float(match.group(1))
                amg_iter = int(match.group(2))
                amg_level = int(match.group(3))
                datasize = int(match.group(4))
                operation = match.group(5)

                print("Compression Ratio:", compression_ratio)
                print("AMG Iter:", amg_iter)
                print("AMG Level:", amg_level)
                print("Datasize:", datasize)
                print("Operation:", operation)
                it.append(amg_iter)
                cr.append(compression_ratio)
                ops.append(operation)
                levels.append(amg_level)
                ds.append(datasize)
            # print(line)
            # ratio=get_compression_ratio(line)
            # iter=get_iteration(line)
            # level=get_level(line)
            # size=get_datasize(line)
            # op=get_op(line)
            # it.append(iter)
            # cr.append(ratio)
            # ops.append(op)



print(it)
print(cr)
print(ops)
print(levels)
print(ds)

