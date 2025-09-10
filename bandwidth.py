#fname = raw_input("Enter file name: ")
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
import re
matplotlib.use('Agg')

secs_data=[]
bytes_data=[]
bw_data=[]
bw_data_calc=[]
it=[]
# eg="cr:120, iter:1, level:0, op:`Residual`"
# eg="cr:15.2381,iter:0,level:0,rank:0,datasize:200,operation:Pre-Smoothing"

# egs=eg.split(",")
# for i in egs:
#     val=i.split(":")[-1]
#     print("val:",val)
# print(egs)

with open("slurm-5426585.output") as fh:
    for index,line in enumerate(fh):
        if index>=500:
            break
        if line.startswith("Time"):
            vals=line.split(",")
            print(vals)
            secs=float(vals[0].split(":")[-1])
            bytes=float(vals[1].split(":")[-1])
            bw=float((vals[2].split(":")[-1]))
            it.append(index)
            secs_data.append(float(secs))
            bytes_data.append(float(bw))
            bw_data.append(float(bw))
            bw_data_calc.append(float((bytes*8)/(secs*1000000000)))

df={"Iteration":it, "Bw":bw_data_calc}
data=pd.DataFrame.from_dict(df)
sns.scatterplot(x="Iteration", y="Bw",
             data=data)
plt.ylabel("Gigabits/second")
plt.xlabel("Iteration")
# plt.yscale('log')
plt.savefig("result_band.png")
plt.show()

