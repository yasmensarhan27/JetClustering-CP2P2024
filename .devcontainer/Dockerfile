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
    ca-certificates \
    cpp \
    cpp-9 \
    dirmngr \
    dpkg-dev \
    fakeroot \
    file \
    gcc \
    gcc-9 \
    gcc-9-base \
    git-man \
    gnupg \
    gnupg-l10n \
    gnupg-utils \
    gpg \
    gpg-agent \
    gpg-wks-client \
    gpg-wks-server \
    gpgconf \
    gpgsm \
    krb5-locales \
    less \
    lib32gcc-s1 \
    lib32stdc++6 \
    libalgorithm-diff-perl \
    libalgorithm-diff-xs-perl \
    libalgorithm-merge-perl \
    libarchive13 \
    libasan5 \
    libasn1-8-heimdal \
    libassuan0

# Install Pythia8
RUN wget https://pythia.org/download/pythia83/pythia8310.tgz && \
    tar xzf pythia8310.tgz && \
    cd pythia8310 && \
    ./configure && \
    make -j $(nproc) && \
    make install && \
    cd ..

# Install Fastjet
RUN wget http://fastjet.fr/repo/fastjet-3.4.2.tar.gz && \
    tar xzf fastjet-3.4.2.tar.gz && \
    cd fastjet-3.4.2 && \
    ./configure && \
    make -j $(nproc) && \
    make install && \
    cd ..

# Download ROOT from the CERN website
RUN wget https://root.cern/download/root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    tar xzf root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    rm root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    cd root && \
    ./configure --enable-roofit --enable-pythia8 --enable-fastjet && \
    make -j $(nproc) && \
    make install && \
    cd ..

# Set working directory
WORKDIR /jetclustering

# Copy your project files
COPY . .

# Entry point (optional)
CMD ["bash"]
