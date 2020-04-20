#!/bin/bash
apt update
apt --assume-yes install pkg-config autoconf autogen python3-pip git libtool
git clone https://github.com/zeromq/libzmq
cd libzmq
./autogen.sh && ./configure && make -j 4
make check && make install && ldconfig
cd .. && rm -rf libzmq

git clone https://github.com/zeromq/cppzmq.git
cd cppzmq
mkdir build
cd build
cmake ..
make -j4 install
cd ../../
rm -rf cppzmq

git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
mkdir build
cd build
cmake ..
make -j4 install
cd ../../
rm -rf yaml-cpp

git clone https://github.com/facebook/zstd.git
cd zstd
make -j4 install
cd ..
rm -rf zstd

pip3 install -r requirements.txt
