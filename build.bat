@echo off
cls
cd build
cmake -G "MinGW Makefiles" -D BuildTest=OFF -Wdev -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_BUILD_TYPE=Debug ../
cmake --build .
cd ../
