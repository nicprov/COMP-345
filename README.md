[![CircleCI](https://circleci.com/gh/nicprov/COMP-345/tree/master.svg?style=shield&circle-token=86ae7faeb3d98bd7603d69519b4e99529d73704f)](https://circleci.com/gh/nicprov/COMP-345/tree/master)

# COMP-345 Warzone

## Setup

### Setting up CMake
If CMake is already installed (make sure that you have at least v3.11), you can run the command below to setup your project.
```
cmake --configure .
```

Otherwise, you will need to download the latest version, and install it manually
```
wget https://cmake.org/files/v3.21/cmake-3.21.0.tar.gz --no-check-certificate
tar -zxvf cmake-3.21.0.tar.gz
cd cmake-3.21.0
./bootstrap --prefix=/usr
make
make install
```

### Building code with CMake
```
cmake --build . --target all
```

tournament ../maps/solar.map aggressive,benevolent 5 10 -> not working