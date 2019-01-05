import sympy
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def _read_tour(filename):
    tour = open(filename).read().split()[1:]
    tour = list(map(int, tour))
    if tour[-1] == 0: tour.pop()
    return tour

def read_tour(filename):
    tour = []
    for line in open(filename).readlines():
        line = line.replace('\n', '')
        try:
            tour.append(int(line) - 1)
        except ValueError as e:
            pass  # skip if not a city id (int)
    return tour[:-1]

cities = pd.read_csv('../input/cities.csv', index_col=['CityId'])

def score_tour(tour):
    df = cities.reindex(tour + [0]).reset_index()
    primes = list(sympy.primerange(0, len(cities)))
    df['prime'] = df.CityId.isin(primes).astype(int)
    df['dist'] = np.hypot(df.X - df.X.shift(-1), df.Y - df.Y.shift(-1))
    df['penalty'] = df['dist'][9::10] * (1 - df['prime'][9::10]) * 0.1
    return df.dist.sum() + df.penalty.sum()

def write_submission(tour, filename):
    assert set(tour) == set(range(len(tour)))
    pd.DataFrame({'Path': list(tour) + [0]}).to_csv(filename, index=False)


tour = read_tour('../output/tsp_solution.csv')
write_submission(tour, '../output/submission.csv')
print(score_tour(tour))


plt.figure(figsize=(20, 20))
plt.plot(cities.X[tour], cities.Y[tour], alpha=0.7)
plt.show()