#fname = raw_input("Enter file name: ")
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')

com_data=[]
no_com_data=[]
iter=[]
with open("com.txt") as fh:
    for line in fh:
        if line.startswith("Res"):
            val=(line.split("=")[-1]).rstrip()
            com_data.append(float(val))
with open("no_com.txt") as fh:
    for line in fh:
        if line.startswith("Res"):
            val=(line.split("=")[-1]).rstrip()
            no_com_data.append(float(val))
            # iter.append()
print(com_data)
print(no_com_data)

it = []#[i for i+1 in xrange(len(com_data))]
res = []
mth = []

for i in range(len(no_com_data)):
    it.append(i+1)
    mth.append("No Compression")
    res.append(no_com_data[i])
    
for i in range(len(com_data)):
    it.append(i+1)
    mth.append("Compressed")
    res.append(com_data[i])
    

df={"Iteration":it, "Residual":res, "Method":mth}
data=pd.DataFrame.from_dict(df)

sns.lineplot(x="Iteration", y="Residual",
             hue="Method",
             data=data)
plt.yscale('log')
plt.savefig("res.jpeg")
plt.show()



