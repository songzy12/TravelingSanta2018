set -x
cd concorde && CFLAGS='-O3 -march=native -mtune=native -fPIC' ./configure
cd LINKERN && make -j && mv linkern ../../