cls
call build

@echo off
cd tests/build
del Data.cyt
cmake -G "MinGW Makefiles" -Wdev -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_BUILD_TYPE=Debug ../
cmake --build .
Cytrus-Test.exe
cd ../../
