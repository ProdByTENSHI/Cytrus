@echo off
cls
cd build
cmake -G "MinGW Makefiles" -D CYTRUS_DEBUG_OUTPUT=ON -D BuildTest=OFF -Wdev -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_BUILD_TYPE=Debug ../
cmake --build .
cd ../
