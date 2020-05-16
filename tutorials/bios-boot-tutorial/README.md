# Bios Boot Tutorial

The `bios-boot-tutorial.py` script simulates the ROXE bios boot sequence.

``Prerequisites``:

1. Python 3.x
2. CMake
3. git
4. g++
5. build-essentials
6. pip3
7. openssl
8. curl
9. jq
10. psmisc


``Steps``:

1. Install roxe binaries by following the steps outlined in below tutorial
[Install roxe binaries](https://github.com/ROXE/roxe#mac-os-x-brew-install)

2. Install roxe.cdt binaries by following the steps outlined in below tutorial
[Install roxe.cdt binaries](https://github.com/ROXE/roxe.cdt#binary-releases)

3. Compile roxe.contracts

```bash
$ cd ~
$ git clone https://github.com/ROXE/roxe.contracts.git
$ cd ./roxe.contracts/
$ ./build.sh
$ cd ./build/contracts/
$ pwd

```

4. Make note of the directory where the contracts were compiled
The last command in the previous step printed on the bash console the contracts' directory, make note of it, we'll reference it from now on as `ROXE_CONTRACTS_DIRECTORY`

5. Launch the `bios-boot-tutorial.py` script
Minimal command line to launch the script below, make sure you replace `ROXE_CONTRACTS_DIRECTORY` with actual directory

```bash
$ cd ~
$ git clone https://github.com/ROXE/roxe.git
$ cd ./roxe/tutorials/bios-boot-tutorial/
$ python3 bios-boot-tutorial.py --clroxe="clroxe --wallet-url http://127.0.0.1:6666 " --nodroxe=nodroxe --kroxed=kroxed --contracts-dir="ROXE_CONTRACTS_DIRECTORY" -w -a
```

See [ROXE Documentation Wiki: Tutorial - Bios Boot](https://github.com/ROXE/roxe/wiki/Tutorial-Bios-Boot-Sequence) for additional information.