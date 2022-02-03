import numpy as np
import scipy as sp
from scipy import stats

my_data = np.array([2,3,3,4,4,4,4,5,5,6])
second_data = np.array([1,9,3,2,6,7,3,6,5,2])
stats.scoreatpercentile(my_data, 25)
np.cov(my_data, second_data)
np.corrcoef(my_data , second_data)