# dccIO - The Most Powerful Infrastructure for Decentralized Applications

[![Build status](https://badge.buildkite.com/370fe5c79410f7d695e4e34c500b4e86e3ac021c6b1f739e20.svg?branch=master)](https://buildkite.com/dccIO/dccio)

Welcome to the dccIO source code repository! This software enables businesses to rapidly build and deploy high-performance and high-security blockchain-based applications.

Some of the groundbreaking features of dccIO include:

1. Free Rate Limited Transactions 
1. Low Latency Block confirmation (0.5 seconds)
1. Low-overhead Byzantine Fault Tolerant Finality
1. Designed for optional high-overhead, low-latency BFT finality 
1. Smart contract platform powered by Web Assembly
1. Designed for Sparse Header Light Client Validation
1. Scheduled Recurring Transactions 
1. Time Delay Security
1. Hierarchical Role Based Permissions
1. Support for Biometric Hardware Secured Keys (e.g. Apple Secure Enclave)
1. Designed for Parallel Execution of Context Free Validation Logic
1. Designed for Inter Blockchain Communication 

dccIO is released under the open source MIT license and is offered “AS IS” without warranty of any kind, express or implied. Any security provided by the dccIO software depends in part on how it is used, configured, and deployed. dccIO is built upon many third-party libraries such as Binaryen (Apache License) and WAVM  (BSD 3-clause) which are also provided “AS IS” without warranty of any kind. Without limiting the generality of the foregoing, Block.one makes no representation or guarantee that dccIO or any third-party libraries will perform as intended or will be free of errors, bugs or faulty code. Both may fail in large or small ways that could completely or partially limit functionality or compromise computer systems. If you use or implement dccIO, you do so at your own risk. In no event will Block.one be liable to any party for any damages whatsoever, even if it had been advised of the possibility of damage.  

Block.one is neither launching nor operating any initial public blockchains based upon the dccIO software. This release refers only to version 1.0 of our open source software. We caution those who wish to use blockchains built on dccIO to carefully vet the companies and organizations launching blockchains based on dccIO before disclosing any private keys to their derivative software. 

There is no public testnet running currently.

**If you have previously installed dccIO, please run the `dccio_uninstall` script (it is in the directory where you cloned dccIO) before downloading and using the binary releases.**

#### Mac OS X Brew Install
```sh
$ brew tap dccio/dccio
$ brew install dccio
```
#### Mac OS X Brew Uninstall
```sh
$ brew remove dccio
```
#### Ubuntu 18.04 Debian Package Install
```sh
$ wget https://github.com/dccio/dcc/releases/download/v1.4.1/dccio-1.4.1.ubuntu-18.04-x86_64.deb
$ sudo apt install ./dccio-1.4.1.ubuntu-18.04-x86_64.deb
```
#### Ubuntu 16.04 Debian Package Install
```sh
$ wget https://github.com/dccio/dcc/releases/download/v1.4.1/dccio-1.4.1.ubuntu-16.04-x86_64.deb
$ sudo apt install ./dccio-1.4.1.ubuntu-16.04-x86_64.deb
```
#### Debian Package Uninstall
```sh
$ sudo apt remove dccio
```
#### RPM Package Install
```sh
$ wget https://github.com/dccio/dcc/releases/download/v1.4.1/dccio-1.4.1.x86_64-0.x86_64.rpm
$ sudo yum install ./dccio-1.4.1.x86_64-0.x86_64.rpm
```
#### RPM Package Uninstall
```sh
$ sudo yum remove dccio.cdt
```

## Supported Operating Systems
dccIO currently supports the following operating systems:  
1. Amazon 2017.09 and higher
2. Centos 7
3. Fedora 25 and higher (Fedora 27 recommended)
4. Mint 18
5. Ubuntu 16.04 (Ubuntu 16.10 recommended)
6. Ubuntu 18.04
7. MacOS Darwin 10.12 and higher (MacOS 10.13.x recommended)

## Resources
1. [Website](https://dcc.io)
1. [Blog](https://medium.com/dccio)
1. [Developer Portal](https://developers.dcc.io)
1. [StackExchange for Q&A](https://dccio.stackexchange.com/)
1. [Community Telegram Group](https://t.me/dccProject)
1. [Developer Telegram Group](https://t.me/joinchat/EaEnSUPktgfoI-XPfMYtcQ)
1. [White Paper](https://github.com/dccIO/Documentation/blob/master/TechnicalWhitePaper.md)
1. [Roadmap](https://github.com/dccIO/Documentation/blob/master/Roadmap.md)

<a name="gettingstarted"></a>
## Getting Started
Instructions detailing the process of getting the software, building it, running a simple test network that produces blocks, account creation and uploading a sample contract to the blockchain can be found in [Getting Started](https://developers.dcc.io/dccio-noddcc/docs/overview-1) on the [dccIO Developer Portal](https://developers.dcc.io).
