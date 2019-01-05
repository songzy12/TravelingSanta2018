set -x
#python prepare_input.py 
#time ./linkern -s 42 -S ../output/linkern.tour -R 1000000000 -t 300 ../input/cities1k.tsp > ../output/linkern.log
#sed -Ene 's/([0-9]+) Steps.*Best: ([0-9]+).*/\1,\2/p' ../output/linkern.log > ../output/linkern.csv
python score_and_submit.py
