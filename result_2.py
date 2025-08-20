#fname = raw_input("Enter file name: ")
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')


with open("slurm-4441704.output") as fh:
    for line in fh:
        if line.startswith("Compression"):
            print(line)




