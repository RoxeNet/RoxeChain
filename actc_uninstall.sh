#! /bin/bash

binaries=(clactc
          actc-abigen
          actc-launcher
          actc-s2wasm
          actc-wast2wasm
          actccpp
          kactcd
          nodactc
          actc-applesdemo)

if [ -d "/usr/local/actc" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            if [ "$(id -u)" -ne 0 ]; then
               printf "\n\tThis requires sudo, please run ./actc_uninstall.sh with sudo\n\n"
               exit -1
            fi

            pushd /usr/local &> /dev/null
            rm -rf actc
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            # Handle cleanup of directories created from installation
            if [ "$1" == "--full" ]; then
               if [ -d ~/Library/Application\ Support/actc ]; then rm -rf ~/Library/Application\ Support/actc; fi # Mac OS
               if [ -d ~/.local/share/actc ]; then rm -rf ~/.local/share/actc; fi # Linux
            fi
            popd &> /dev/null
            break;;
         [Nn]* )
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi
