---
content_title: Download Roxe Source
---

To download the Roxe source code, clone the `RoxeChain` repo and its submodules. It is adviced to create a home `roxe` folder first and download all the Roxe related software there:

```sh
mkdir -p ~/roxe && cd ~/roxe
git clone --recursive https://github.com/Roxe/RoxeChain
```

## Update Submodules

If a repository is cloned without the `--recursive` flag, the submodules *must* be updated before starting the build process:

```sh
cd ~/roxe/RoxeChain
git submodule update --init --recursive
```

## Pull Changes

When pulling changes, especially after switching branches, the submodules *must* also be updated. This can be achieved with the `git submodule` command as above, or using `git pull` directly:

```sh
[git checkout <branch>]  (optional)
git pull --recurse-submodules
```

[[info | What's Next?]]
| [Build Roxe binaries](02_build-roxe-binaries.md)
