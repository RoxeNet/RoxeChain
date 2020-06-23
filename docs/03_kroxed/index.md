---
content_title: Kroxed
---

## Introduction

`kroxed` is a key manager service daemon for storing private keys and signing digital messages. It provides a secure key storage medium for keys to be encrypted at rest in the associated wallet file. `kroxed` also defines a secure enclave for signing transaction created by `clroxe` or a third part library.

## Installation

`kroxed` is distributed as part of the [ROXE software suite](https://github.com/Roxe/roxe/blob/master/README.md). To install `kroxed` just visit the [Roxe Software Installation](../00_install/index.md) section.

## Operation

When a wallet is unlocked with the corresponding password, `clroxe` can request `kroxed` to sign a transaction with the appropriate private keys. Also, `kroxed` provides support for hardware-based wallets such as Secure Encalve and YubiHSM.

[[info | Audience]]
| `kroxed` is intended to be used by ROXE developers only.
