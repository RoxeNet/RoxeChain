The following steps must be taken for the example script to work.

0. Create wallet
0. Create account for actc.token
0. Create account for scott
0. Create account for exchange
0. Set token contract on actc.token
0. Create actc token
0. Issue initial tokens to scott

**Note**:
Deleting the `transactions.txt` file will prevent replay from working.


### Create wallet
`clactc wallet create`

### Create account steps
`clactc create key`

`clactc create key`

`clactc wallet import  --private-key <private key from step 1>`

`clactc wallet import  --private-key <private key from step 2>`

`clactc create account actc <account_name> <public key from step 1> <public key from step 2>`

### Set contract steps
`clactc set contract actc.token /contracts/actc.token -p actc.token@active`

### Create actc token steps
`clactc push action actc.token create '{"issuer": "actc.token", "maximum_supply": "100000.0000 actc", "can_freeze": 1, "can_recall": 1, "can_whitelist": 1}' -p actc.token@active`

### Issue token steps
`clactc push action actc.token issue '{"to": "scott", "quantity": "900.0000 actc", "memo": "testing"}' -p actc.token@active`
