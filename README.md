# dydx-client

# How to build
```bash
python3 -m venv /path/to/venv
source /path/to/venv/bin/active
mkdir build
cd build
conan profile detect
conan install ../conanfile.txt --build=missing -of .
cmake -S .. -B .
cmake --build --parallel 4
``` 
