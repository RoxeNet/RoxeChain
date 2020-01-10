### Building your first smart contract
```c++
#include <actc/actc.hpp>
#include <actc/name.hpp>

class [[actc::contract]] hello : public actc::contract {
   public:
      using actc::contract::contract;

      [[actc::action]]
      void hi(actc::name nm) {
         actc::print_f("Hello, %\n", nm);
      }
};
```

- Navigate to the hello folder in examples (./examples/hello).
- You should then see the hello.cpp file
- Now run the compiler
```sh
$ actc-cpp -abigen hello.cpp -o hello.wasm
```
- Or with CMake
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```
This will generate two files:
* The compiled binary wasm (hello.wasm)
* The generated ABI file (hello.abi)
