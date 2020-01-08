FROM actc/builder as builder
ARG branch=master
ARG symbol=SYS

RUN git clone -b $branch https://github.com/actc/actc.git --recursive \
    && cd actc && echo "$branch:$(git rev-parse HEAD)" > /etc/actc-version \
    && cmake -H. -B"/tmp/build" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/tmp/build -DBUILD_MONGO_DB_PLUGIN=true -DCORE_SYMBOL_NAME=$symbol \
    && cmake --build /tmp/build --target install && rm /tmp/build/bin/actccpp


FROM ubuntu:18.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/lib/* /usr/local/lib/
COPY --from=builder /tmp/build/bin /opt/actc/bin
COPY --from=builder /tmp/build/contracts /contracts
COPY --from=builder /actc/Docker/config.ini /
COPY --from=builder /etc/actc-version /etc
COPY --from=builder /actc/Docker/nodactcd.sh /opt/actc/bin/nodactcd.sh
ENV actc_ROOT=/opt/actc
RUN chmod +x /opt/actc/bin/nodactcd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/actc/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
