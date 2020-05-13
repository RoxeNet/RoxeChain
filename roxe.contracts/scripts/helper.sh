# Ensures passed in version values are supported.
function check-version-numbers() {
  CHECK_VERSION_MAJOR=$1
  CHECK_VERSION_MINOR=$2

  if [[ $CHECK_VERSION_MAJOR -lt $ROXE_MIN_VERSION_MAJOR ]]; then
    exit 1
  fi
  if [[ $CHECK_VERSION_MAJOR -gt $ROXE_MAX_VERSION_MAJOR ]]; then
    exit 1
  fi
  if [[ $CHECK_VERSION_MAJOR -eq $ROXE_MIN_VERSION_MAJOR ]]; then
    if [[ $CHECK_VERSION_MINOR -lt $ROXE_MIN_VERSION_MINOR ]]; then
      exit 1
    fi
  fi
  if [[ $CHECK_VERSION_MAJOR -eq $ROXE_MAX_VERSION_MAJOR ]]; then
    if [[ $CHECK_VERSION_MINOR -gt $ROXE_MAX_VERSION_MINOR ]]; then
      exit 1
    fi
  fi
  exit 0
}


# Handles choosing which ROXE directory to select when the default location is used.
function default-roxe-directories() {
  REGEX='^[0-9]+([.][0-9]+)?$'
  ALL_ROXE_SUBDIRS=()
  if [[ -d ${HOME}/roxe ]]; then
    ALL_ROXE_SUBDIRS=($(ls ${HOME}/roxe | sort -V))
  fi
  for ITEM in "${ALL_ROXE_SUBDIRS[@]}"; do
    if [[ "$ITEM" =~ $REGEX ]]; then
      DIR_MAJOR=$(echo $ITEM | cut -f1 -d '.')
      DIR_MINOR=$(echo $ITEM | cut -f2 -d '.')
      if $(check-version-numbers $DIR_MAJOR $DIR_MINOR); then
        PROMPT_ROXE_DIRS+=($ITEM)
      fi
    fi
  done
  for ITEM in "${PROMPT_ROXE_DIRS[@]}"; do
    if [[ "$ITEM" =~ $REGEX ]]; then
      ROXE_VERSION=$ITEM
    fi
  done
}


# Prompts or sets default behavior for choosing ROXE directory.
function roxe-directory-prompt() {
  if [[ -z $ROXE_DIR_PROMPT ]]; then
    default-roxe-directories;
    echo 'No ROXE location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        if [[ -z $ROXE_VERSION ]]; then
          echo "No default ROXE installations detected..."
          PROCEED=n
        else
          printf "Is ROXE installed in the default location: $HOME/roxe/$ROXE_VERSION (y/n)" && read -p " " PROCEED
        fi
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is ROXE installed in the default location?";;
        0 | true | [Yy]* )
          break;;
        1 | false | [Nn]* )
          if [[ $PROMPT_ROXE_DIRS ]]; then
            echo "Found these compatible ROXE versions in the default location."
            printf "$HOME/roxe/%s\n" "${PROMPT_ROXE_DIRS[@]}"
          fi
          printf "Enter the installation location of ROXE:" && read -e -p " " ROXE_DIR_PROMPT;
          ROXE_DIR_PROMPT="${ROXE_DIR_PROMPT/#\~/$HOME}"
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  export ROXE_INSTALL_DIR="${ROXE_DIR_PROMPT:-${HOME}/roxe/${ROXE_VERSION}}"
}


# Prompts or default behavior for choosing ROXE.CDT directory.
function cdt-directory-prompt() {
  if [[ -z $CDT_DIR_PROMPT ]]; then
    echo 'No ROXE.CDT location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is ROXE.CDT installed in the default location? /usr/local/roxe.cdt (y/n)" && read -p " " PROCEED
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is ROXE.CDT installed in the default location?";;
        0 | true | [Yy]* )
          break;;
        1 | false | [Nn]* )
          printf "Enter the installation location of ROXE.CDT:" && read -e -p " " CDT_DIR_PROMPT;
          CDT_DIR_PROMPT="${CDT_DIR_PROMPT/#\~/$HOME}"
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  export CDT_INSTALL_DIR="${CDT_DIR_PROMPT:-/usr/local/roxe.cdt}"
}


# Ensures ROXE is installed and compatible via version listed in tests/CMakeLists.txt.
function nodroxe-version-check() {
  INSTALLED_VERSION=$(echo $($ROXE_INSTALL_DIR/bin/nodroxe --version))
  INSTALLED_VERSION_MAJOR=$(echo $INSTALLED_VERSION | cut -f1 -d '.' | sed 's/v//g')
  INSTALLED_VERSION_MINOR=$(echo $INSTALLED_VERSION | cut -f2 -d '.' | sed 's/v//g')

  if [[ -z $INSTALLED_VERSION_MAJOR || -z $INSTALLED_VERSION_MINOR ]]; then
    echo "Could not determine ROXE version. Exiting..."
    exit 1;
  fi

  if $(check-version-numbers $INSTALLED_VERSION_MAJOR $INSTALLED_VERSION_MINOR); then
    if [[ $INSTALLED_VERSION_MAJOR -gt $ROXE_SOFT_MAX_MAJOR ]]; then
      echo "Detected ROXE version is greater than recommended soft max: $ROXE_SOFT_MAX_MAJOR.$ROXE_SOFT_MAX_MINOR. Proceed with caution."
    fi
    if [[ $INSTALLED_VERSION_MAJOR -eq $ROXE_SOFT_MAX_MAJOR && $INSTALLED_VERSION_MINOR -gt $ROXE_SOFT_MAX_MINOR ]]; then
      echo "Detected ROXE version is greater than recommended soft max: $ROXE_SOFT_MAX_MAJOR.$ROXE_SOFT_MAX_MINOR. Proceed with caution."
    fi
  else
    echo "Supported versions are: $ROXE_MIN_VERSION_MAJOR.$ROXE_MIN_VERSION_MINOR - $ROXE_MAX_VERSION_MAJOR.$ROXE_MAX_VERSION_MINOR"
    echo "Invalid ROXE installation. Exiting..."
    exit 1;
  fi
}
