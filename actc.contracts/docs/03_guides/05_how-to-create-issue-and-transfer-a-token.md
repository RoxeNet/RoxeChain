## How to create, issue and transfer a token

## Step 1: Obtain Contract Source

Navigate to your contracts directory.

```text
cd CONTRACTS_DIR
```

Pull the source
```text
git clone https://github.com/ACTC/actc.contracts --branch master --single-branch
```

```text
cd actc.contracts/contracts/actc.token
```

## Step 2: Create Account for Contract
[[info]]
| You may have to unlock your wallet first!

```shell
clactc create account actc actc.token ACTC6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```

## Step 3: Compile the Contract

```shell
actc-cpp -I include -o actc.token.wasm src/actc.token.cpp --abigen
```

## Step 4: Deploy the Token Contract

```shell
clactc set contract actc.token CONTRACTS_DIR/actc.contracts/contracts/actc.token --abi actc.token.abi -p actc.token@active
```

Result should look similar to the one below:
```shell
Reading WASM from ...
Publishing contract...
executed transaction: 69c68b1bd5d61a0cc146b11e89e11f02527f24e4b240731c4003ad1dc0c87c2c  9696 bytes  6290 us
#         actc <= actc::setcode               {"account":"actc.token","vmtype":0,"vmversion":0,"code":"0061736d0100000001aa011c60037f7e7f0060047f...
#         actc <= actc::setabi                {"account":"actc.token","abi":"0e656f73696f3a3a6162692f312e30000605636c6f73650002056f776e6572046e61...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Step 5: Create the Token

```shell
clactc push action actc.token create '[ "actc", "1000000000.0000 LSC"]' -p actc.token@active
```

Result should look similar to the one below:
```shell
executed transaction: 0e49a421f6e75f4c5e09dd738a02d3f51bd18a0cf31894f68d335cd70d9c0e12  120 bytes  1000 cycles
#   actc.token <= actc.token::create          {"issuer":"actc","maximum_supply":"1000000000.0000 LSC"}
```

An alternate approach uses named arguments:

```shell
clactc push action actc.token create '{"issuer":"actc", "maximum_supply":"1000000000.0000 LSC"}' -p actc.token@active
```

Result should look similar to the one below:
```shell
executed transaction: 0e49a421f6e75f4c5e09dd738a02d3f51bd18a0cf31894f68d335cd70d9c0e12  120 bytes  1000 cycles
#   actc.token <= actc.token::create          {"issuer":"actc","maximum_supply":"1000000000.0000 LSC"}
```
This command created a new token `ACI` with a precision of 4 decimals and a maximum supply of 1000000000.0000 LSC.  To create this token requires the permission of the `actc.token` contract. For this reason, `-p actc.token@active` was passed to authorize the request.

## Step 6: Issue Tokens

The issuer can issue new tokens to the issuer account in our case `actc`.

```text
clactc push action actc.token issue '[ "actc", "100.0000 LSC", "memo" ]' -p actc@active
```

Result should look similar to the one below:
```shell
executed transaction: a26b29d66044ad95edf0fc04bad3073e99718bc26d27f3c006589adedb717936  128 bytes  337 us
#   actc.token <= actc.token::issue           {"to":"actc","quantity":"100.0000 LSC","memo":"memo"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Step 7: Transfer Tokens

Now that account `actc` has been issued tokens, transfer some of them to account `bob`.

```shell
clactc push action actc.token transfer '[ "actc", "bob", "25.0000 LSC", "m" ]' -p actc@active
```

Result should look similar to the one below:
```text
executed transaction: 60d334850151cb95c35fe31ce2e8b536b51441c5fd4c3f2fea98edcc6d69f39d  128 bytes  497 us
#   actc.token <= actc.token::transfer        {"from":"actc","to":"bob","quantity":"25.0000 LSC","memo":"m"}
#         actc <= actc.token::transfer        {"from":"actc","to":"bob","quantity":"25.0000 LSC","memo":"m"}
#           bob <= actc.token::transfer        {"from":"actc","to":"bob","quantity":"25.0000 LSC","memo":"m"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
Now check if "bob" got the tokens using [clactc get currency balance](https://developers.actc.io/actc-clactc/reference#currency-balance)

```shell
clactc get currency balance actc.token bob LSC
```

Result:
```text
25.00 LSC
```

Check "actc's" balance, notice that tokens were deducted from the account

```shell
clactc get currency balance actc.token actc LSC
```

Result:
```text
75.00 LSC
```
