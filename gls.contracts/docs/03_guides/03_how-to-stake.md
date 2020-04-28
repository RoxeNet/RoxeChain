## Goal

Stake resource for your account

## Before you begin

* Install the currently supported version of clactc

* Ensure the reference system contracts from `gls.contracts` repository is deployed and used to manage system resources

* Understand the following:
  * What is an account
  * What is network bandwidth
  * What is CPU bandwidth

## Steps

Stake 0.01 LSC network bandwidth for `alice`

```shell
clactc system delegatebw alice alice "0 LSC" "0.01 LSC"
```

Stake 0.01 LSC CPU bandwidth for `alice`:

```shell
clactc system delegatebw alice alice "0.01 LSC" "0 LSC"
```