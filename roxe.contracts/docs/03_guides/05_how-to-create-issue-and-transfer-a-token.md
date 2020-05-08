## How to create, issue and transfer a token

## Step 1: Obtain Contract Source

Navigate to your contracts directory.

```text
cd CONTRACTS_DIR
```

Pull the source
```text
git clone https://github.com/ROXE/roxe.contracts --branch master --single-branch
```

```text
cd roxe.contracts/contracts/roxe.token
```

## Step 2: Create Account for Contract
[[info]]
| You may have to unlock your wallet first!

```shell
clroxe create account roxe roxe.token ROXE6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```

## Step 3: Compile the Contract

```shell
roxe-cpp -I include -o roxe.token.wasm src/roxe.token.cpp --abigen
```

## Step 4: Deploy the Token Contract

```shell
clroxe set contract roxe.token CONTRACTS_DIR/roxe.contracts/contracts/roxe.token --abi roxe.token.abi -p roxe.token@active
```

Result should look similar to the one below:
```shell
Reading WASM from ...
Publishing contract...
executed transaction: 69c68b1bd5d61a0cc146b11e89e11f02527f24e4b240731c4003ad1dc0c87c2c  9696 bytes  6290 us
#         roxe <= roxe::setcode               {"account":"roxe.token","vmtype":0,"vmversion":0,"code":"0061736d0100000001aa011c60037f7e7f0060047f...
#         roxe <= roxe::setabi                {"account":"roxe.token","abi":"0e656f73696f3a3a6162692f312e30000605636c6f73650002056f776e6572046e61...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Step 5: Create the Token

```shell
clroxe push action roxe.token create '[ "roxe", "1000000000.0000 ROC"]' -p roxe.token@active
```

Result should look similar to the one below:
```shell
executed transaction: 0e49a421f6e75f4c5e09dd738a02d3f51bd18a0cf31894f68d335cd70d9c0e12  120 bytes  1000 cycles
#   roxe.token <= roxe.token::create          {"issuer":"roxe","maximum_supply":"1000000000.0000 ROC"}
```

An alternate approach uses named arguments:

```shell
clroxe push action roxe.token create '{"issuer":"roxe", "maximum_supply":"1000000000.0000 ROC"}' -p roxe.token@active
```

Result should look similar to the one below:
```shell
executed transaction: 0e49a421f6e75f4c5e09dd738a02d3f51bd18a0cf31894f68d335cd70d9c0e12  120 bytes  1000 cycles
#   roxe.token <= roxe.token::create          {"issuer":"roxe","maximum_supply":"1000000000.0000 ROC"}
```
This command created a new token `ACI` with a precision of 4 decimals and a maximum supply of 1000000000.0000 ROC.  To create this token requires the permission of the `roxe.token` contract. For this reason, `-p roxe.token@active` was passed to authorize the request.

## Step 6: Issue Tokens

The issuer can issue new tokens to the issuer account in our case `roxe`.

```text
clroxe push action roxe.token issue '[ "roxe", "100.0000 ROC", "memo" ]' -p roxe@active
```

Result should look similar to the one below:
```shell
executed transaction: a26b29d66044ad95edf0fc04bad3073e99718bc26d27f3c006589adedb717936  128 bytes  337 us
#   roxe.token <= roxe.token::issue           {"to":"roxe","quantity":"100.0000 ROC","memo":"memo"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Step 7: Transfer Tokens

Now that account `roxe` has been issued tokens, transfer some of them to account `bob`.

```shell
clroxe push action roxe.token transfer '[ "roxe", "bob", "25.0000 ROC", "m" ]' -p roxe@active
```

Result should look similar to the one below:
```text
executed transaction: 60d334850151cb95c35fe31ce2e8b536b51441c5fd4c3f2fea98edcc6d69f39d  128 bytes  497 us
#   roxe.token <= roxe.token::transfer        {"from":"roxe","to":"bob","quantity":"25.0000 ROC","memo":"m"}
#         roxe <= roxe.token::transfer        {"from":"roxe","to":"bob","quantity":"25.0000 ROC","memo":"m"}
#           bob <= roxe.token::transfer        {"from":"roxe","to":"bob","quantity":"25.0000 ROC","memo":"m"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
Now check if "bob" got the tokens using [clroxe get currency balance](https://developers.roxe.io/roxe-clroxe/reference#currency-balance)

```shell
clroxe get currency balance roxe.token bob ROC
```

Result:
```text
25.00 ROC
```

Check "roxe's" balance, notice that tokens were deducted from the account

```shell
clroxe get currency balance roxe.token roxe ROC
```

Result:
```text
75.00 ROC
```
