---
content_title: Build ROXE Binaries
---

[[info | Shell Scripts]]
| The build script is one of various automated shell scripts provided in the ROXE repository for building, installing, and optionally uninstalling the ROXE software and its dependencies. They are available in the `RoxeChain/scripts` folder.

The build script first installs all dependencies and then builds ROXE. The script supports these [Operating Systems](../../index.md#supported-operating-systems). To run it, first change to the `~/roxe/RoxeChain` folder, then launch the script:

```sh
cd ~/roxe/RoxeChain
./scripts/roxe_build.sh
```

The build process writes temporary content to the `RoxeChain/build` folder. After building, the program binaries can be found at `RoxeChain/build/programs`.

[[info | What's Next?]]
| [Installing ROXE](03_install-roxe-binaries.md) is strongly recommended after building from source as it makes local development significantly more friendly.
