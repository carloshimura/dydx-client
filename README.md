# dydx-client

# Software Dependencies
- GCC 13 (C++23)
- Python 3.10
- Conan 2

# Library dependencies
You can check the conanfile.txt for all dependencies, but here are a few notes:

- bip3x and toolbox are forked from (https://github.com/edwardstock/bip3x) and (https://github.com/edwardstock/toolbox)
- there was a build error with those, hence the need to fork
- they are installed with conan, so if you run "conan install" for them, they will be made locally available for your through conan
- Proto files also have a build problem in C++. Some services are called "Service", and because of that the name needs to be changed and .h and .cc files need to be fixed to make it buildable
- bech32 files were forked from (https://github.com/asnefedovv/dydx-v4-client-cpp/)

# How to build
```bash
python3 -m venv /path/to/venv
source /path/to/venv/bin/active
conan profile detect
cd dependencies/toolbox
conan create . --build=missing -pr=../../conan_release_pr
cd ../bip3x
conan create . --build=missing -pr=../../conan_release_pr
cd ../..
mkdir build
cd build
conan install ../conanfile.txt --build=missing -of ./conan_release_pr
cmake -S .. -B .
cmake --build --parallel $(nproc --all)
``` 

# Docker build
```bash
docker build . -t dydx-client
```