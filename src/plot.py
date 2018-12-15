import pandas as pd
pd.read_csv('../output/linkern.csv', index_col=0, names=['TSP tour length']).plot();