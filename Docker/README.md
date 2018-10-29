# Run in docker

Simple and fast setup of dcc.IO on Docker is also available.

## Install Dependencies

- [Docker](https://docs.docker.com) Docker 17.05 or higher is required
- [docker-compose](https://docs.docker.com/compose/) version >= 1.10.0

## Docker Requirement

- At least 7GB RAM (Docker -> Preferences -> Advanced -> Memory -> 7GB or above)
- If the build below fails, make sure you've adjusted Docker Memory settings and try again.

## Build dcc image

```bash
git clone https://github.com/dccIO/dcc.git --recursive  --depth 1
cd dcc/Docker
docker build . -t dccio/dcc
```

The above will build off the most recent commit to the master branch by default. If you would like to target a specific branch/tag, you may use a build argument. For example, if you wished to generate a docker image based off of the v1.4.1 tag, you could do the following:

```bash
docker build -t dccio/dcc:v1.4.1 --build-arg branch=v1.4.1 .
```

By default, the symbol in dccio.system is set to SYS. You can override this using the symbol argument while building the docker image.

```bash
docker build -t dccio/dcc --build-arg symbol=<symbol> .
```

## Start noddcc docker container only

```bash
docker run --name noddcc -p 8888:8888 -p 9876:9876 -t dccio/dcc noddccd.sh -e --http-alias=noddcc:8888 --http-alias=127.0.0.1:8888 --http-alias=localhost:8888 arg1 arg2
```

By default, all data is persisted in a docker volume. It can be deleted if the data is outdated or corrupted:

```bash
$ docker inspect --format '{{ range .Mounts }}{{ .Name }} {{ end }}' noddcc
fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
$ docker volume rm fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
```

Alternately, you can directly mount host directory into the container

```bash
docker run --name noddcc -v /path-to-data-dir:/opt/dccio/bin/data-dir -p 8888:8888 -p 9876:9876 -t dccio/dcc noddccd.sh -e --http-alias=noddcc:8888 --http-alias=127.0.0.1:8888 --http-alias=localhost:8888 arg1 arg2
```

## Get chain info

```bash
curl http://127.0.0.1:8888/v1/chain/get_info
```

## Start both noddcc and kdccd containers

```bash
docker volume create --name=noddcc-data-volume
docker volume create --name=kdccd-data-volume
docker-compose up -d
```

After `docker-compose up -d`, two services named `noddccd` and `kdccd` will be started. noddcc service would expose ports 8888 and 9876 to the host. kdccd service does not expose any port to the host, it is only accessible to cldcc when running cldcc is running inside the kdccd container as described in "Execute cldcc commands" section.

### Execute cldcc commands

You can run the `cldcc` commands via a bash alias.

```bash
alias cldcc='docker-compose exec kdccd /opt/dccio/bin/cldcc -u http://noddccd:8888 --wallet-url http://localhost:8900'
cldcc get info
cldcc get account inita
```

Upload sample exchange contract

```bash
cldcc set contract exchange contracts/exchange/
```

If you don't need kdccd afterwards, you can stop the kdccd service using

```bash
docker-compose stop kdccd
```

### Develop/Build custom contracts

Due to the fact that the dccio/dcc image does not contain the required dependencies for contract development (this is by design, to keep the image size small), you will need to utilize the dccio/dcc-dev image. This image contains both the required binaries and dependencies to build contracts using dcciocpp.

You can either use the image available on [Docker Hub](https://hub.docker.com/r/dccio/dcc-dev/) or navigate into the dev folder and build the image manually.

```bash
cd dev
docker build -t dccio/dcc-dev .
```

### Change default configuration

You can use docker compose override file to change the default configurations. For example, create an alternate config file `config2.ini` and a `docker-compose.override.yml` with the following content.

```yaml
version: "2"

services:
  noddcc:
    volumes:
      - noddcc-data-volume:/opt/dccio/bin/data-dir
      - ./config2.ini:/opt/dccio/bin/data-dir/config.ini
```

Then restart your docker containers as follows:

```bash
docker-compose down
docker-compose up
```

### Clear data-dir

The data volume created by docker-compose can be deleted as follows:

```bash
docker volume rm noddcc-data-volume
docker volume rm kdccd-data-volume
```

### Docker Hub

Docker Hub image available from [docker hub](https://hub.docker.com/r/dccio/dcc/).
Create a new `docker-compose.yaml` file with the content below

```bash
version: "3"

services:
  noddccd:
    image: dccio/dcc:latest
    command: /opt/dccio/bin/noddccd.sh --data-dir /opt/dccio/bin/data-dir -e --http-alias=noddccd:8888 --http-alias=127.0.0.1:8888 --http-alias=localhost:8888
    hostname: noddccd
    ports:
      - 8888:8888
      - 9876:9876
    expose:
      - "8888"
    volumes:
      - noddcc-data-volume:/opt/dccio/bin/data-dir

  kdccd:
    image: dccio/dcc:latest
    command: /opt/dccio/bin/kdccd --wallet-dir /opt/dccio/bin/data-dir --http-server-address=127.0.0.1:8900 --http-alias=localhost:8900 --http-alias=kdccd:8900
    hostname: kdccd
    links:
      - noddccd
    volumes:
      - kdccd-data-volume:/opt/dccio/bin/data-dir

volumes:
  noddcc-data-volume:
  kdccd-data-volume:

```

*NOTE:* the default version is the latest, you can change it to what you want

run `docker pull dccio/dcc:latest`

run `docker-compose up`

### dccIO Testnet

We can easily set up a dccIO local testnet using docker images. Just run the following commands:

Note: if you want to use the mongo db plugin, you have to enable it in your `data-dir/config.ini` first.

```
# create volume
docker volume create --name=noddcc-data-volume
docker volume create --name=kdccd-data-volume
# pull images and start containers
docker-compose -f docker-compose-dccio-latest.yaml up -d
# get chain info
curl http://127.0.0.1:8888/v1/chain/get_info
# get logs
docker-compose logs -f noddccd
# stop containers
docker-compose -f docker-compose-dccio-latest.yaml down
```

The `blocks` data are stored under `--data-dir` by default, and the wallet files are stored under `--wallet-dir` by default, of course you can change these as you want.

### About MongoDB Plugin

Currently, the mongodb plugin is disabled in `config.ini` by default, you have to change it manually in `config.ini` or you can mount a `config.ini` file to `/opt/dccio/bin/data-dir/config.ini` in the docker-compose file.
