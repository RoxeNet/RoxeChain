## How to build the roxe.contracts

### Preconditions
Ensure an appropriate version of `roxe.cdt` is installed. Installing `roxe.cdt` from binaries is sufficient, follow the [`roxe.cdt` installation instructions steps](https://github.com/ROXE/roxe.cdt/tree/master/#binary-releases) to install it. To verify if you have `roxe.cdt` installed and its version run the following command

```sh
roxe-cpp -v
```

#### Build contracts using the build script

##### To build contracts alone
Run the `build.sh` script in the top directory to build all the contracts.

##### To build the contracts and unit tests
1. Ensure an appropriate version of `roxe` has been built from source and installed. Installing `roxe` from binaries `is not` sufficient. You can find instructions on how to do it [here](https://github.com/ROXE/roxe/blob/master/README.md) in section `Building from Sources`.
2. Run the `build.sh` script in the top directory with the `-t` flag to build all the contracts and the unit tests for these contracts.

#### Build contracts manually

To build the `roxe.contracts` execute the following commands.

On all platforms except macOS:
```sh
cd you_local_path_to/roxe.contracts/
rm -fr build
mkdir build
cd build
cmake ..
make -j$( nproc )
cd ..
```

For macOS:
```sh
cd you_local_path_to/roxe.contracts/
rm -fr build
mkdir build
cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
cd ..
```

#### After build:
* If the build was configured to also build unit tests, the unit tests executable is placed in the _build/tests_ folder and is named __unit_test__.
* The contracts (both `.wasm` and `.abi` files) are built into their corresponding _build/contracts/\<contract name\>_ folder.
* Finally, simply use __clroxe__ to _set contract_ by pointing to the previously mentioned directory for the specific contract.

## How to deploy the roxe.contracts

### To deploy roxe.bios contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testerbios`
```
clroxe set contract testerbios you_local_path_to/roxe.contracts/build/contracts/roxe.bios/ -p testerbios
```

### To deploy roxe.msig contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testermsig`
```
clroxe set contract testermsig you_local_path_to/roxe.contracts/build/contracts/roxe.msig/ -p testermsig
```

### To deploy roxe.system contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testersystem`
```
clroxe set contract testersystem you_local_path_to/roxe.contracts/build/contracts/roxe.system/ -p testersystem
```

### To deploy roxe.token contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testertoken`
```
clroxe set contract testertoken you_local_path_to/roxe.contracts/build/contracts/roxe.token/ -p testertoken
```

### To deploy roxe.wrap contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testerwrap`
```
clroxe set contract testerwrap you_local_path_to/roxe.contracts/build/contracts/roxe.wrap/ -p testerwrap
```