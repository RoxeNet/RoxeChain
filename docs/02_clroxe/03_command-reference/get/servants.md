## Description
Retrieve accounts which are servants of a given account 

## Info

**Command**

```sh
clroxe get servants
```
**Output**

```console
Usage: clroxe get servants account

Positionals:
  account TEXT                The name of the controlling account
```

## Command

```sh
clroxe get servants inita
```

## Output

```json
{
  "controlled_accounts": [
    "tester"
  ]
}
```
