#! /bin/bash

binaries=(cldcc
          dccio-abigen
          dccio-launcher
          dccio-s2wasm
          dccio-wast2wasm
          dcciocpp
          kdccd
          noddcc
          dccio-applesdemo)

if [ -d "/usr/local/dccio" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            if [ "$(id -u)" -ne 0 ]; then
               printf "\n\tThis requires sudo, please run ./dccio_uninstall.sh with sudo\n\n"
               exit -1
            fi

            pushd /usr/local &> /dev/null
            rm -rf dccio
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            # Handle cleanup of directories created from installation
            if [ "$1" == "--full" ]; then
               if [ -d ~/Library/Application\ Support/dccio ]; then rm -rf ~/Library/Application\ Support/dccio; fi # Mac OS
               if [ -d ~/.local/share/dccio ]; then rm -rf ~/.local/share/dccio; fi # Linux
            fi
            popd &> /dev/null
            break;;
         [Nn]* )
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi
