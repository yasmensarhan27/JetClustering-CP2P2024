# Use Ubuntu 20.04 as the base image
FROM ubuntu:20.04

# Set environment variable to prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install necessary packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    git \
    cmake \
    g++ \
    clang \
    wget \
    curl \
    libx11-dev \
    libxpm-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libssl-dev \
    libncurses5-dev \
    libxml2-dev \
    libz-dev \
    libbz2-dev \
    libsqlite3-dev \
    libcurl4-openssl-dev \
    python \
    python3 \
    libkrb5-dev \
    libgsl-dev \
    libfftw3-dev \
    libcfitsio-dev \
    graphviz \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install FastJet, Pythia8, and ROOT
RUN wget -qO- http://fastjet.fr/repo/fastjet-3.4.2.tar.gz | tar xz -C /tmp && \
    cd /tmp/fastjet-3.4.2 && \
    ./configure --prefix=/usr/local && \
    make -j$(nproc) && \
    make install && \
    cd /tmp && rm -rf fastjet-3.4.2 && \
    wget -qO- https://pythia.org/download/pythia83/pythia8310.tgz | tar xz -C /tmp && \
    cd /tmp/pythia8310 && \
    ./configure --with-fastjet3=/usr/local && \
    make -j$(nproc) && \
    make install && \
    cd /tmp && rm -rf pythia8310 && \
    wget -qO- https://root.cern/download/root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz | tar xz -C /usr/local && \
    mv /usr/local/root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4 /usr/local/root && \
    rm -f /usr/local/root/README && \
    ln -s /usr/local/root/bin/* /usr/local/bin/ && \
    ln -s /usr/local/root/lib/* /usr/local/lib/ && \
    ln -s /usr/local/root/include/* /usr/local/include/ && \
    echo "source /usr/local/root/bin/thisroot.sh" >> ~/.bashrc

# Set working directory
WORKDIR /jetclustering

# Copy your project files
COPY . .

# Entry point (optional)
CMD ["bash"]
