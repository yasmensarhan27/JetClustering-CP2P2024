FROM ubuntu:20.04

# Install necessary dependencies
RUN apk update && \
    DEBIAN_FRONTEND=noninteractive apk add -y \
    build-essential \
    cmake \
    git \
    wget \
    g++ \
    clang \
    libx11-dev \
    libxpm-dev \
    libxft-dev \
    libxext-dev \
    && rm -rf /var/lib/apt/lists/*

# Install ROOT CERN
RUN wget https://root.cern.ch/download/root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz && \
    tar -xf root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz && \
    rm root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz

ENV ROOTSYS /root/root
ENV PATH $ROOTSYS/bin:$PATH
ENV LD_LIBRARY_PATH $ROOTSYS/lib:$LD_LIBRARY_PATH

# Install FastJet
RUN git clone --branch 'v3.3.4' --depth 1 https://github.com/fastjet/fastjet.git && \
    cd fastjet && \
    autoreconf -i && \
    ./configure && \
    make && \
    make check && \
    make install && \
    cd .. && \
    rm -rf fastjet

# Install Pythia
RUN git clone --branch 'v8303' --depth 1 https://github.com/alisw/pythia8.git && \
    cd pythia8 && \
    ./configure && \
    make && \
    cd ..

# Set the default shell
SHELL ["/bin/ash", "-c"]

# Set the default working directory
WORKDIR /workspace
