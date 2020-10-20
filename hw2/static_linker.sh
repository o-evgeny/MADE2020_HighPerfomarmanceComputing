CC='g++ -std=c++14'

${CC} -c main.cpp
${CC} -c matrix.cpp
ar rc lib.a matrix.o
${CC} main.cpp lib.a -o multiplier_static

rm -rf *.o lib.a