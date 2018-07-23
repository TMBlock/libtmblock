## Build

1. Download and extract [Halide 2017/10/30](https://github.com/halide/Halide/releases/tag/release_2017_10_30) or [Halide 2018/02/15](https://github.com/halide/Halide/releases/tag/release_2018_02_15).
2. Run following instructions.

```bash
mkdir build/
cd bulid/
cmake -DHALIDE_DISTRIB_DIR=path/to/halide ..
make
```

## TODO

* [ ] parallelize

## FAQ

### Failed to build on MacOS

This is [known issue](https://github.com/halide/Halide/issues/2821) of halide.

To work around, add following option when running `cmake`:

```
-DHALIDE_DISTRIB_USE_STATIC_LIBRARY=TRUE
```
