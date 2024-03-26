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
    libpcre3-dev \
    xlibmesa-glu-dev \
    libglew-dev \
    libftgl-dev \
    libmysqlclient-dev \
    libfftw3-dev \
    libcfitsio-dev \
    graphviz-dev \
    libavahi-compat-libdnssd-dev \
    libldap2-dev \
    libxml2-dev \
    libkrb5-dev \
    libgsl-dev \
    libqt5x11extras5-dev \
    libclass-method-modifiers-perl \
    libxml-libxml-perl \
    libcrypt-openssl-rsa-perl \
    libauthen-sasl-perl \
    libmime-lite-perl \
    libterm-readkey-perl \
    libyaml-cpp-dev \
    zlib1g-dev \
    libtbb-dev \
    liblzma-dev \
    libbz2-dev \
    python3-dev \
    python3-numpy \
    python3-pip \
    python3-pyqt5 \
    libopencv-dev \
    libpython3-dev \
    libboost-all-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install ROOT CERN
RUN wget https://root.cern/download/root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    tar xzf root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    rm root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    cd root && \
    ./configure --enable-roofit --enable-pythia8 --enable-fastjet && \
    make -j$(nproc) && \
    make install && \
    cd ..

# Set working directory
WORKDIR /jetclustering

# Copy your project files
COPY . .

# Entry point (optional)
CMD ["bash"]
