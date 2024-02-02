autoreconf --install
./configure
clear
make check
gcovr -r .
make clean
