# Use Ubuntu 20.04 as the base image
FROM ubuntu:20.04

# Set environment variable to prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install necessary packages, including rsync
RUN apt-get update && \
    apt-get install -y \
    dpkg-dev \
    cmake \
    g++ \
    gcc \
    binutils \
    libx11-dev \
    libxpm-dev \
    libxft-dev \
    libxext-dev \
    libpng-dev \
    libjpeg-dev \
    python3 \
    libssl-dev \
    wget \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install FastJet
RUN wget http://fastjet.fr/repo/fastjet-3.4.2.tar.gz && \
    tar xzf fastjet-3.4.2.tar.gz && \
    cd fastjet-3.4.2 && \
    ./configure --prefix=/usr/local && \
    make -j$(nproc) && \
    make install && \
    cd ..

# Install Pythia8
RUN wget https://pythia.org/download/pythia83/pythia8310.tgz && \
    tar xzf pythia8310.tgz && \
    cd pythia8310 && \
    ./configure --with-fastjet3=/usr/local && \
    make -j$(nproc) && \
    make install && \
    cd ..

# Download ROOT
RUN wget http://root.cern/download/root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    tar xzf root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    rm root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    mv root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4 root && \
    mv root /usr/local/

# Set environment variables for ROOT
ENV ROOTSYS=/usr/local/root
ENV PATH=$ROOTSYS/bin:$PATH
ENV LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH

# Set working directory
WORKDIR /jetclustering

# Copy your project files
COPY . .

# Entry point (optional)
CMD ["bash"]
