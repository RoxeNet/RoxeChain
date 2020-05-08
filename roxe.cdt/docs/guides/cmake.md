# CMake

## CMake Configuration
To compile an ROXE smart contract with CMake you'll need a CMake file. The new `roxe-init` tool can be used to generate the directory structure stub .hpp/.cpp files and subsequent cmake files. Or the template `CMakeLists.txt` in the examples folder is a good boilerplate for manual usage.

For example:

In `CMakeLists.txt`:
```
cmake_minimum_required(VERSION 3.5)
project(test_example VERSION 1.0.0)

find_package(roxe.cdt)

add_contract( test test test.cpp )
```


In `test.cpp`:

```
#include <roxe/roxe.hpp>
using namespace roxe;

CONTRACT test : public roxe::contract {
public:
   using contract::contract;

   ACTION testact( name test ) {
   }
};

ROXE_DISPATCH( test, (testact) )
```

## CMake Macros
- `add_contract` is used to build your smart contract and generate an ABI, the first parameter is the contract name, the second is the cmake target name, and the rest are the CPP files needed to build the contract.
- `target_ricardian_directory` can be used to add the directory where your ricardian contracts live to a specific cmake target.
- (new for native tester) `add_native_library` and `add_native_executable` CMake macros have been added (these are a drop in replacement for add_library and add_executable).
