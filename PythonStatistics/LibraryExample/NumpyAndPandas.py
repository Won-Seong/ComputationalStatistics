import numpy as np
import pandas as pd

#numpy array
my_array = np.array([1,2,3,4,5])
my_array

#Operation with numpy array
my_array + 2
my_array ** 2
my_array -= 2

#numpy Matrix
my_matrix = np.array([
    [1,2,3,4,5],
    [6,7,8,9,10]
    ])
my_matrix
my_matrix.shape #check row and column

#Various array
np.tile("A" , 5)
np.tile(0, 4)
np.zeros(7)
np.ones(4)

#Slice
my_array[3]
my_array[2:4]
my_matrix[1]
my_matrix[1][1:3]
my_matrix[1,2:4]

#Basic statistic with numpy

my_data = np.array([2,3,3,4,4,4,4,5,5,6])
my_data.sum()
my_data.mean()
my_data.var(ddof = 0) #Biased
my_data.std(ddof = 0)
my_data.var(ddof = 1) #Unbiased
my_data.std(ddof = 1)
my_data.max()
my_data.min()
np.median(my_data)

#Pandas dataframe
my_dataframe = pd.DataFrame({
    'col1' : my_array,
    'col2' : my_array ** 2,
    'col3' : np.array(["A","B","C","D","E"])
    })
my_dataframe

#Merge dataframe
second_dataframe = pd.DataFrame({
    'col1' : my_array - 10,
    'col2' : my_array * my_array,
    'col3' : ['d','e','f','g','h']
    })

pd.concat([my_dataframe, second_dataframe])
pd.concat([my_dataframe, second_dataframe], axis = 1)

#Manipulate dataframe
my_dataframe.col2
my_dataframe[["col2","col3"]]
my_dataframe.drop("col1",axis = 1)
my_dataframe.head()

#Query
my_dataframe.query('index == 0')[["col1","col3"]]
my_dataframe.query('col1 == 3 or col2 == 4')

#Series
type(my_dataframe.col1)

#Group statistic
second_dataframe = pd.DataFrame({
    'species' : ['A' for i in range(3) ] + [ 'B' for j in range(3)],
    'length' : [2,3,4,6,8,10]
    })
second_dataframe
my_group = second_dataframe.groupby("species")
my_group.mean()
my_group.std(ddof = 1)
my_group.describe()