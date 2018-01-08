
## Build

```bash
mkdir build/
cd bulid/
wget https://github.com/halide/Halide/releases/download/release_2017_10_30/halide-mac-64-trunk-3af238615667312dcb46607752e3ae5d0ec5d713.tgz
tar zxvf halide-mac-*.tgz
cmake ../ -DHALIDE_DISTRIB_DIR=$PWD/halide
make
```

if anything goes wrong, try adding the following line to the head of `CMakeLists.txt`:

```
set(HALIDE_DISTRIB_USE_STATIC_LIBRARY TRUE)
```

