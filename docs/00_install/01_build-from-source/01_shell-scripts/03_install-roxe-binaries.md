---
content_title: Install ROXE Binaries
---

## Roxe install script

For ease of contract development, content can be installed at the `/usr/local` folder using the `eosio_install.sh` script within the `eos/scripts` folder. Adequate permission is required to install on system folders:

```sh
cd ~/roxe/RoxeChain
sudo ./scripts/roxe_install.sh
```

## Roxe manual install

In lieu of the `roxe_install.sh` script, you can install the Roxe binaries directly by invoking `make install` within the `RoxeChain/build` folder. Again, adequate permission is required to install on system folders:

```sh
cd ~/roxe/RoxeChain/build
sudo make install
```

[[info | What's Next?]]
| Configure and use [Nodroxe](../../../01_nodroxe/index.md), or optionally [Test the ROXE binaries](04_test-roxe-binaries.md).
