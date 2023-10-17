import pandas as pd
import matplotlib as plt
df = pd.read_csv("data.csv")

x = []
for i in range(100):
    x.append(i/100)

df[x].plot()
plt.show()