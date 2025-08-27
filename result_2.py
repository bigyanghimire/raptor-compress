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
ranks=[]
# eg="cr:120, iter:1, level:0, op:`Residual`"
# eg="cr:15.2381,iter:0,level:0,rank:0,datasize:200,operation:Pre-Smoothing"

# egs=eg.split(",")
# for i in egs:
#     val=i.split(":")[-1]
#     print("val:",val)
# print(egs)

with open("slurm-10000.output") as fh:
    for line in fh:
        if line.startswith("cr"):
            vals=line.split(",")
            print(vals)
            ratio=vals[0].split(":")[-1]
            iter=vals[1].split(":")[-1]
            level=vals[2].split(":")[-1]
            rank=vals[3].split(":")[-1]
            datasize=vals[4].split(":")[-1]
            operation=(vals[5].split(":")[-1]).rstrip()

            # print(ratio)
            # print(iter)
            # print(level)
            # print(rank)
            # print(datasize)
            # print(operation)

            cr.append(float(ratio))
            it.append(float(iter))
            levels.append(float(level))
            ranks.append(float(rank))
            ds.append(float(datasize))
            ops.append(operation)

# print(it)
# print(cr)
print("operations:",cr)
# print(levels)
# print(ds)

df={"Iteration":it, "Ratio":cr, "Method":ops}
data=pd.DataFrame.from_dict(df)
sns.lineplot(x="Iteration", y="Ratio",
             hue="Method",
             data=data)
plt.yscale('log')
plt.savefig("result_10000.png")
plt.show()


