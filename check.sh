autoreconf --install
./configure CFLAGS="--coverage -fPIC" LDLIBS='-lgcov'
make
make check
gcovr --root src/
