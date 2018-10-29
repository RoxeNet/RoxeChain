FROM dccio/builder
ARG branch=master
ARG symbol=SYS

RUN git clone -b $branch https://github.com/dccIO/dcc.git --recursive \
    && cd dcc && echo "$branch:$(git rev-parse HEAD)" > /etc/dccio-version \
    && cmake -H. -B"/opt/dccio" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/opt/dccio -DBUILD_MONGO_DB_PLUGIN=true -DCORE_SYMBOL_NAME=$symbol \
    && cmake --build /opt/dccio --target install \
    && cp /dcc/Docker/config.ini / && ln -s /opt/dccio/contracts /contracts && cp /dcc/Docker/noddccd.sh /opt/dccio/bin/noddccd.sh && ln -s /dcc/tutorials /tutorials

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates vim psmisc python3-pip && rm -rf /var/lib/apt/lists/*
RUN pip3 install numpy
ENV dccIO_ROOT=/opt/dccio
RUN chmod +x /opt/dccio/bin/noddccd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/dccio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
