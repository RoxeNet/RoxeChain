FROM dccio/builder as builder
ARG branch=master
ARG symbol=SYS

RUN git clone -b $branch https://github.com/dccIO/dcc.git --recursive \
    && cd dcc && echo "$branch:$(git rev-parse HEAD)" > /etc/dccio-version \
    && cmake -H. -B"/tmp/build" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/tmp/build -DBUILD_MONGO_DB_PLUGIN=true -DCORE_SYMBOL_NAME=$symbol \
    && cmake --build /tmp/build --target install && rm /tmp/build/bin/dcciocpp


FROM ubuntu:18.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/lib/* /usr/local/lib/
COPY --from=builder /tmp/build/bin /opt/dccio/bin
COPY --from=builder /tmp/build/contracts /contracts
COPY --from=builder /dcc/Docker/config.ini /
COPY --from=builder /etc/dccio-version /etc
COPY --from=builder /dcc/Docker/noddccd.sh /opt/dccio/bin/noddccd.sh
ENV dccIO_ROOT=/opt/dccio
RUN chmod +x /opt/dccio/bin/noddccd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/dccio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
