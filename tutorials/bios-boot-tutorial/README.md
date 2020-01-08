# Bios Boot Tutorial

The `bios-boot-tutorial.py` script simulates the ACTC bios boot sequence.

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

1. Install actc binaries by following the steps outlined in below tutorial
[Install actc binaries](https://github.com/ACTC/actc#mac-os-x-brew-install)

2. Install actc.cdt binaries by following the steps outlined in below tutorial
[Install actc.cdt binaries](https://github.com/ACTC/actc.cdt#binary-releases)

3. Compile actc.contracts

```bash
$ cd ~
$ git clone https://github.com/ACTC/actc.contracts.git
$ cd ./actc.contracts/
$ ./build.sh
$ cd ./build/contracts/
$ pwd

```

4. Make note of the directory where the contracts were compiled
The last command in the previous step printed on the bash console the contracts' directory, make note of it, we'll reference it from now on as `ACTC_CONTRACTS_DIRECTORY`

5. Launch the `bios-boot-tutorial.py` script
Minimal command line to launch the script below, make sure you replace `ACTC_CONTRACTS_DIRECTORY` with actual directory

```bash
$ cd ~
$ git clone https://github.com/ACTC/actc.git
$ cd ./actc/tutorials/bios-boot-tutorial/
$ python3 bios-boot-tutorial.py --clactc="clactc --wallet-url http://127.0.0.1:6666 " --nodactc=nodactc --kactcd=kactcd --contracts-dir="ACTC_CONTRACTS_DIRECTORY" -w -a
```

See [ACTC Documentation Wiki: Tutorial - Bios Boot](https://github.com/ACTC/actc/wiki/Tutorial-Bios-Boot-Sequence) for additional information.