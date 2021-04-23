# cvector - a C99 vector implementation

## 1. Purpose
```cvector``` is a simple, straightforward C99 implementation of a C++-style vector container, which will accept any data type, included custom made ```struct``` and other types.<br>

A ```CMakeLists.txt``` file will be provided for every project subdirectory, for easy integration of **cvector** with any existing C code base.

## 2. Installation
 If you want to install and use the library as a production element, generate the build files using ```cmake -G "Your Generator" -DCMAKE_BUILD_TYPE=Release```.<br><br>
 If you want to contribute to the development of this simple library or if you need debug symbols, generate build files using ```cmake -G "Your Generator" -DCMAKE_BUILD_TYPE=Debug``` instead.