# Quick Start

If the `lib` directory does not exist, use `git submodule` to download the dependent library.
```shell
git submodule init
git submodule update
```
Then, prepare the directories for building and storing data.

```shell
mkdir build data
```

Then, build the code.
```shell
cd build
cmake -DBUILD_DEPS=ON .. && cmake --build .
```

Building the code for the first time will take a considerable amount of time.

You can modify the `testcase.in` to generate data. Each figure in each row represents 
* the minimum number of nodes; 
* the maximum number of nodes; 
* the number of edges divided by the number of nodes; 
* the maximum capacity of flow on each edge.

To generate the data,
```shell
cd build
./gen testcase.in
```

To evaluate the traditional algorithm and the linear solver,
```shell
cd build
./run
```
