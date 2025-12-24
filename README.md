# C++ Experiments

This is a collection of C++ experiments, done for fun and for learning.

## Compiling

I am using [conan](https://conan.io/) to manage dependencies. Thus, make sure to install it first. After that,
run:

```shell
mkdir build && cd build
cmake -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake ..
make
```

You can also use the [cpp-dev](https://github.com/santiagonar1/dockerfiles/blob/main/cpp-dev.dockerfile) docker image
to compile and run the code. If you do not want to build it yourself, run:

```shell
./run-docker.sh
```