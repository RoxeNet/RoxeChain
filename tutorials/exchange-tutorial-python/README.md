The following steps must be taken for the example script to work.

0. Create wallet
0. Create account for dccio.token
0. Create account for scott
0. Create account for exchange
0. Set token contract on dccio.token
0. Create dcc token
0. Issue initial tokens to scott

**Note**:
Deleting the `transactions.txt` file will prevent replay from working.


### Create wallet
`cldcc wallet create`

### Create account steps
`cldcc create key`

`cldcc create key`

`cldcc wallet import  --private-key <private key from step 1>`

`cldcc wallet import  --private-key <private key from step 2>`

`cldcc create account dccio <account_name> <public key from step 1> <public key from step 2>`

### Set contract steps
`cldcc set contract dccio.token /contracts/dccio.token -p dccio.token@active`

### Create dcc token steps
`cldcc push action dccio.token create '{"issuer": "dccio.token", "maximum_supply": "100000.0000 dcc", "can_freeze": 1, "can_recall": 1, "can_whitelist": 1}' -p dccio.token@active`

### Issue token steps
`cldcc push action dccio.token issue '{"to": "scott", "quantity": "900.0000 dcc", "memo": "testing"}' -p dccio.token@active`
