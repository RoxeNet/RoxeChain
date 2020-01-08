## Goal

Setup an account that require multiple signatures for signing a transaction

## Before you begin

* You have an account

* Ensure the reference system contracts from `actc.contracts` repository is deployed and used to manage system resources

* You have sufficient token allocated to your account

* Install the currently supported version of clactc

* Unlock your wallet

## Steps

Buys RAM in value of 0.1 ACI tokens for account `alice`:

```shell
clactc system buyram alice alice "0.1 ACI" -p alice@active
```