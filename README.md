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

We also provide a docker image for compiling the project. You can build it with:

```shell
make docker
```

Then you can launch the container with:

```shell
docker run --rm -it -v .:/code -w /code cpp-dev bash
```
