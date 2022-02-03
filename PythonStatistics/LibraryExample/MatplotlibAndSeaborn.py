import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

x = np.array([0,1,2,3,4,5,6,7,8,9])
y = np.array([2,3,4,3,5,4,6,7,4,8])
z = np.array([2,3,3,4,4,4,4,5,5,6])
fish = pd.DataFrame({
    'species' : ['A' for i in range(10)] +  ['B' for i in range(10)],
    'length' : [2,3,3,4,4,4,4,5,5,6,5,6,6,7,7,7,7,8,8,9]
    })
#matplotlib
plt.plot(x , y, color = 'black')
plt.title("lineplot matplotlib")
plt.xlabel("x")
plt.ylabel("y")
plt.show()

#hist with seaborn
sns.distplot(z, color = 'red')
plt.show()

#multi hist 
sns.distplot(fish.query("species == 'A'")["length"])
sns.distplot(fish.query("species == 'B'")["length"])
plt.show()

#boxplot
sns.boxplot(x = "species" , y = "length", data = fish)
plt.show()

#violinplot
sns.violinplot(x = "species" , y = "length" , data = fish)
plt.show()

#barplot
sns.barplot(x = "species" , y = "length" , data = fish)
plt.show()

#pairplot
sns.pairplot(data = sns.load_dataset("iris") , hue = "species" , palette = "gray")
plt.show()