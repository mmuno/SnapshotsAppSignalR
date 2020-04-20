#!/bin/bash
sudo apt update
sudo apt upgrade
sudo apt install pkg-config autoconf autogen python3-pip
git clone https://github.com/zeromq/libzmq
cd libzmq
./autogen.sh && ./configure && make -j 4
make check && sudo make install && sudo ldconfig
cd .. && rm -rf libzmq

git clone git@github.com:zeromq/cppzmq.git
cd cppzmq
mkdir build
cd build
cmake ..
sudo make -j4 install
cd ../../
rm -rf cppzmq

git clone git@github.com:jbeder/yaml-cpp.git
cd yaml-cpp
mkdir build
cd build
cmake ..
sudo make -j4 install
cd ../../
sudo rm -rf yaml-cpp

git clone git@github.com:facebook/zstd.git
cd zstd
sudo make -j4 install
cd ..
sudo rm -rf zstd

pip3 install -r requirements.txt
