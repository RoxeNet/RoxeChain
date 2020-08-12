---
content_title: Nodroxe
---

## Introduction

`nodroxe` is the core service daemon that runs on every ROXE node. It can be configured to process smart contracts, validate transactions, produce blocks containing valid transactions, and confirm blocks to record them on the blockchain.

## Installation

`nodroxe` is distributed as part of the [ROXE software suite](https://github.com/ROXE/roxe/blob/master/README.md). To install `nodroxe`, visit the [ROXE Software Installation](../00_install/index.md) section.

## Explore

Navigate the sections below to configure and use `nodroxe`.

* [Usage](02_usage/index.md) - Configuring and using `nodroxe`, node setups/environments.
* [Plugins](03_plugins/index.md) - Using plugins, plugin options, mandatory vs. optional.
* [Replays](04_replays/index.md) - Replaying the chain from a snapshot or a blocks.log file.
* [Logging](06_logging/index.md) - Logging config/usage, loggers, appenders, logging levels.
* [Upgrade Guides](07_upgrade-guides/index.md) - ROXE version/consensus upgrade guides.
* [Troubleshooting](08_troubleshooting/index.md) - Common `nodroxe` troubleshooting questions.

[[info | Access Node]]
| A local or remote ROXE access node running `nodroxe` is required for a client application or smart contract to interact with the blockchain.
