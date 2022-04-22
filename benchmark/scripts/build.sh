echo Creating dirs...
mkdir data

echo Building program...
g++ ../bmsd.cpp -o task1
g++ ../main.cpp -o task

echo Building generator...
g++ ./generator/generator.cpp -o ./generator/generator

echo Building benchmark...
g++ ./src/benchmark.cpp -o ./benchmark

echo Done!