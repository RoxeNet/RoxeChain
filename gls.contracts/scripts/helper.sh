# Ensures passed in version values are supported.
function check-version-numbers() {
  CHECK_VERSION_MAJOR=$1
  CHECK_VERSION_MINOR=$2

  if [[ $CHECK_VERSION_MAJOR -lt $ACTC_MIN_VERSION_MAJOR ]]; then
    exit 1
  fi
  if [[ $CHECK_VERSION_MAJOR -gt $ACTC_MAX_VERSION_MAJOR ]]; then
    exit 1
  fi
  if [[ $CHECK_VERSION_MAJOR -eq $ACTC_MIN_VERSION_MAJOR ]]; then
    if [[ $CHECK_VERSION_MINOR -lt $ACTC_MIN_VERSION_MINOR ]]; then
      exit 1
    fi
  fi
  if [[ $CHECK_VERSION_MAJOR -eq $ACTC_MAX_VERSION_MAJOR ]]; then
    if [[ $CHECK_VERSION_MINOR -gt $ACTC_MAX_VERSION_MINOR ]]; then
      exit 1
    fi
  fi
  exit 0
}


# Handles choosing which ACTC directory to select when the default location is used.
function default-actc-directories() {
  REGEX='^[0-9]+([.][0-9]+)?$'
  ALL_ACTC_SUBDIRS=()
  if [[ -d ${HOME}/actc ]]; then
    ALL_ACTC_SUBDIRS=($(ls ${HOME}/actc | sort -V))
  fi
  for ITEM in "${ALL_ACTC_SUBDIRS[@]}"; do
    if [[ "$ITEM" =~ $REGEX ]]; then
      DIR_MAJOR=$(echo $ITEM | cut -f1 -d '.')
      DIR_MINOR=$(echo $ITEM | cut -f2 -d '.')
      if $(check-version-numbers $DIR_MAJOR $DIR_MINOR); then
        PROMPT_ACTC_DIRS+=($ITEM)
      fi
    fi
  done
  for ITEM in "${PROMPT_ACTC_DIRS[@]}"; do
    if [[ "$ITEM" =~ $REGEX ]]; then
      ACTC_VERSION=$ITEM
    fi
  done
}


# Prompts or sets default behavior for choosing ACTC directory.
function actc-directory-prompt() {
  if [[ -z $ACTC_DIR_PROMPT ]]; then
    default-actc-directories;
    echo 'No ACTC location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        if [[ -z $ACTC_VERSION ]]; then
          echo "No default ACTC installations detected..."
          PROCEED=n
        else
          printf "Is ACTC installed in the default location: $HOME/actc/$ACTC_VERSION (y/n)" && read -p " " PROCEED
        fi
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is ACTC installed in the default location?";;
        0 | true | [Yy]* )
          break;;
        1 | false | [Nn]* )
          if [[ $PROMPT_ACTC_DIRS ]]; then
            echo "Found these compatible ACTC versions in the default location."
            printf "$HOME/actc/%s\n" "${PROMPT_ACTC_DIRS[@]}"
          fi
          printf "Enter the installation location of ACTC:" && read -e -p " " ACTC_DIR_PROMPT;
          ACTC_DIR_PROMPT="${ACTC_DIR_PROMPT/#\~/$HOME}"
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  export ACTC_INSTALL_DIR="${ACTC_DIR_PROMPT:-${HOME}/actc/${ACTC_VERSION}}"
}


# Prompts or default behavior for choosing ACTC.CDT directory.
function cdt-directory-prompt() {
  if [[ -z $CDT_DIR_PROMPT ]]; then
    echo 'No ACTC.CDT location was specified.'
    while true; do
      if [[ $NONINTERACTIVE != true ]]; then
        printf "Is ACTC.CDT installed in the default location? /usr/local/actc.cdt (y/n)" && read -p " " PROCEED
      fi
      echo ""
      case $PROCEED in
        "" )
          echo "Is ACTC.CDT installed in the default location?";;
        0 | true | [Yy]* )
          break;;
        1 | false | [Nn]* )
          printf "Enter the installation location of ACTC.CDT:" && read -e -p " " CDT_DIR_PROMPT;
          CDT_DIR_PROMPT="${CDT_DIR_PROMPT/#\~/$HOME}"
          break;;
        * )
          echo "Please type 'y' for yes or 'n' for no.";;
      esac
    done
  fi
  export CDT_INSTALL_DIR="${CDT_DIR_PROMPT:-/usr/local/actc.cdt}"
}


# Ensures ACTC is installed and compatible via version listed in tests/CMakeLists.txt.
function nodactc-version-check() {
  INSTALLED_VERSION=$(echo $($ACTC_INSTALL_DIR/bin/nodactc --version))
  INSTALLED_VERSION_MAJOR=$(echo $INSTALLED_VERSION | cut -f1 -d '.' | sed 's/v//g')
  INSTALLED_VERSION_MINOR=$(echo $INSTALLED_VERSION | cut -f2 -d '.' | sed 's/v//g')

  if [[ -z $INSTALLED_VERSION_MAJOR || -z $INSTALLED_VERSION_MINOR ]]; then
    echo "Could not determine ACTC version. Exiting..."
    exit 1;
  fi

  if $(check-version-numbers $INSTALLED_VERSION_MAJOR $INSTALLED_VERSION_MINOR); then
    if [[ $INSTALLED_VERSION_MAJOR -gt $ACTC_SOFT_MAX_MAJOR ]]; then
      echo "Detected ACTC version is greater than recommended soft max: $ACTC_SOFT_MAX_MAJOR.$ACTC_SOFT_MAX_MINOR. Proceed with caution."
    fi
    if [[ $INSTALLED_VERSION_MAJOR -eq $ACTC_SOFT_MAX_MAJOR && $INSTALLED_VERSION_MINOR -gt $ACTC_SOFT_MAX_MINOR ]]; then
      echo "Detected ACTC version is greater than recommended soft max: $ACTC_SOFT_MAX_MAJOR.$ACTC_SOFT_MAX_MINOR. Proceed with caution."
    fi
  else
    echo "Supported versions are: $ACTC_MIN_VERSION_MAJOR.$ACTC_MIN_VERSION_MINOR - $ACTC_MAX_VERSION_MAJOR.$ACTC_MAX_VERSION_MINOR"
    echo "Invalid ACTC installation. Exiting..."
    exit 1;
  fi
}
