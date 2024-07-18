# Directory Compare

A simple C++17 application for recursively comparing MD5 file hashes between two directories. The project is 
structured following [pitchfork](https://github.com/vector-of-bool/pitchfork) guidelines and has been tested 
on Ubuntu 22.04 Linux.

## Building

Building the project is done with CMake. It has been tested using GCC 11.4.0. Typical CMake workflow can be 
followed:

1. mkdir build && cd build
2. cmake ..
3. make

Addition CMake targets have been enabled to allow the following:

1. make all - build all targets in the project
2. make clean - remove all binary files from the build tree
3. make test - execute prebuilt Catch2 test cases with CTest
4. make run - Run the prebuilt dir-compare executable in the `./build/src` directory against the test directory 
structures in the `tests` folder.

### Required Dependencies

- catch2
- openssl

##### Ubuntu

Install using apt:

```
sudo apt install catch2 openssl
```

##### RHEL

Install using yum/dnf:

```
sudo dnf install openssl catch2-devel
```

## Cleaning the Project

Run `make clean` from within the CMake build tree.

## Running the Application

- Run `make all` followed by `make run` from the root of the `build` directory.

OR

- Run `make all` followed by `./src/dir-compare <dir1> <dir2>` from the root of the `build` directory. `dir1` and 
`dir2` may be any relative or absolute paths to directories on the file system.

### Output

Expected output for the application consists of three files:

1. common - Identical files that have been found to exist in both `dir1` and `dir2`
2. a_only - Unique files that only exist in `dir1` and not `dir2`
3. b_only - Unique files that do not exist in `dir1` but do exist in `dir2`

Each line in an output is of the format `hash: file1 <file2 file3 ...>`. This means that identical files are grouped 
together for easy identification regardless of name/path.

## Running Tests

Run `make all` followed by `make test` from the root of the CMake `build` tree.
