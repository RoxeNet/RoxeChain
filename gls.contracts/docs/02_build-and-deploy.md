## How to build the gls.contracts

### Preconditions
Ensure an appropriate version of `actc.cdt` is installed. Installing `actc.cdt` from binaries is sufficient, follow the [`actc.cdt` installation instructions steps](https://github.com/ACTC/actc.cdt/tree/master/#binary-releases) to install it. To verify if you have `actc.cdt` installed and its version run the following command

```sh
actc-cpp -v
```

#### Build contracts using the build script

##### To build contracts alone
Run the `build.sh` script in the top directory to build all the contracts.

##### To build the contracts and unit tests
1. Ensure an appropriate version of `actc` has been built from source and installed. Installing `actc` from binaries `is not` sufficient. You can find instructions on how to do it [here](https://github.com/ACTC/actc/blob/master/README.md) in section `Building from Sources`.
2. Run the `build.sh` script in the top directory with the `-t` flag to build all the contracts and the unit tests for these contracts.

#### Build contracts manually

To build the `gls.contracts` execute the following commands.

On all platforms except macOS:
```sh
cd you_local_path_to/gls.contracts/
rm -fr build
mkdir build
cd build
cmake ..
make -j$( nproc )
cd ..
```

For macOS:
```sh
cd you_local_path_to/gls.contracts/
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
* Finally, simply use __clactc__ to _set contract_ by pointing to the previously mentioned directory for the specific contract.

## How to deploy the gls.contracts

### To deploy actc.bios contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testerbios`
```
clactc set contract testerbios you_local_path_to/gls.contracts/build/contracts/actc.bios/ -p testerbios
```

### To deploy gls.msig contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testermsig`
```
clactc set contract testermsig you_local_path_to/gls.contracts/build/contracts/gls.msig/ -p testermsig
```

### To deploy gls.system contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testersystem`
```
clactc set contract testersystem you_local_path_to/gls.contracts/build/contracts/gls.system/ -p testersystem
```

### To deploy gls.token contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testertoken`
```
clactc set contract testertoken you_local_path_to/gls.contracts/build/contracts/gls.token/ -p testertoken
```

### To deploy gls.wrap contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testerwrap`
```
clactc set contract testerwrap you_local_path_to/gls.contracts/build/contracts/gls.wrap/ -p testerwrap
```