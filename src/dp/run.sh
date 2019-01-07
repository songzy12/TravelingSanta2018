# g++ --std=c++17 -Wall -g -Ofast -mtune=native -march=native -fopenmp -DNDEBUG -o dp dp.cc

# K=12: 1515579.33 real 1m33s
# K=13: 1515578.73 real 3m31s
# K=14: 1515577.89 real 7m51s
# ...
# K=18: 1515572.48 ca. 200 minutes
time ./dp 20 <1515572.48.csv >submission.csv
