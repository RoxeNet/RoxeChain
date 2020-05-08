### Building your first smart contract
```c++
#include <roxe/roxe.hpp>
#include <roxe/name.hpp>

class [[roxe::contract]] hello : public roxe::contract {
   public:
      using roxe::contract::contract;

      [[roxe::action]]
      void hi(roxe::name nm) {
         roxe::print_f("Hello, %\n", nm);
      }
};
```

- Navigate to the hello folder in examples (./examples/hello).
- You should then see the hello.cpp file
- Now run the compiler
```sh
$ roxe-cpp -abigen hello.cpp -o hello.wasm
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
