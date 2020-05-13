#! /bin/bash

binaries=(clroxe
          roxe-abigen
          roxe-launcher
          roxe-s2wasm
          roxe-wast2wasm
          roxecpp
          kroxed
          nodroxe
          roxe-applesdemo)

if [ -d "/usr/local/roxe" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            if [ "$(id -u)" -ne 0 ]; then
               printf "\n\tThis requires sudo, please run ./roxe_uninstall.sh with sudo\n\n"
               exit -1
            fi

            pushd /usr/local &> /dev/null
            rm -rf roxe
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            # Handle cleanup of directories created from installation
            if [ "$1" == "--full" ]; then
               if [ -d ~/Library/Application\ Support/roxe ]; then rm -rf ~/Library/Application\ Support/roxe; fi # Mac OS
               if [ -d ~/.local/share/roxe ]; then rm -rf ~/.local/share/roxe; fi # Linux
            fi
            popd &> /dev/null
            break;;
         [Nn]* )
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi
