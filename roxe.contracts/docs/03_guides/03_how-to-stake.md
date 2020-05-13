## Goal

Stake resource for your account

## Before you begin

* Install the currently supported version of clroxe

* Ensure the reference system contracts from `roxe.contracts` repository is deployed and used to manage system resources

* Understand the following:
  * What is an account
  * What is network bandwidth
  * What is CPU bandwidth

## Steps

Stake 0.01 ROC network bandwidth for `alice`

```shell
clroxe system delegatebw alice alice "0 ROC" "0.01 ROC"
```

Stake 0.01 ROC CPU bandwidth for `alice`:

```shell
clroxe system delegatebw alice alice "0.01 ROC" "0 ROC"
```