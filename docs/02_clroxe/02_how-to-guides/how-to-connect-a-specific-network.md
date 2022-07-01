## Goal

Connect to a specific `nodroxe` or `kroxed` host to send COMMAND

`clroxe` and `kroxed` can connect to a specific node by using the `--url` or `--wallet-url` optional arguments, respectively, followed by the http address and port number these services are listening to.

[[info | Default address:port]]
| If no optional arguments are used (i.e. `--url` or `--wallet-url`), `clroxe` attempts to connect to a local `nodroxe` or `kroxed` running at localhost `127.0.0.1` and default port `8888`.

## Before you begin

* Install the currently supported version of `clroxe`

## Steps
### Connecting to Nodroxe

```sh
clroxe -url http://nodroxe-host:8888 COMMAND
```

### Connecting to Kroxed

```sh
clroxe --wallet-url http://kroxed-host:8888 COMMAND
```
