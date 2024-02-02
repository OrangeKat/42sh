autoreconf --install
./configure
clear
make check
gcovr
make clean
