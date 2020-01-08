FROM actc/builder
ARG branch=master
ARG symbol=SYS

RUN git clone -b $branch https://github.com/actc/actc.git --recursive \
    && cd actc && echo "$branch:$(git rev-parse HEAD)" > /etc/actc-version \
    && cmake -H. -B"/opt/actc" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/opt/actc -DBUILD_MONGO_DB_PLUGIN=true -DCORE_SYMBOL_NAME=$symbol \
    && cmake --build /opt/actc --target install \
    && cp /actc/Docker/config.ini / && ln -s /opt/actc/contracts /contracts && cp /actc/Docker/nodactcd.sh /opt/actc/bin/nodactcd.sh && ln -s /actc/tutorials /tutorials

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates vim psmisc python3-pip && rm -rf /var/lib/apt/lists/*
RUN pip3 install numpy
ENV actc_ROOT=/opt/actc
RUN chmod +x /opt/actc/bin/nodactcd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/actc/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
