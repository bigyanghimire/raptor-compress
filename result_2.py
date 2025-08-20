#fname = raw_input("Enter file name: ")
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')

it=[]
cr=[]
op=[]

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

with open("slurm-4441704.output") as fh:
    for line in fh:
        if line.startswith("Compression"):
            print(line)
            cr=get_compression_ratio(line)
            iter=get_iteration(line)
            level=get_level(line)
            size=get_datasize(line)
            op=get_op(line)





