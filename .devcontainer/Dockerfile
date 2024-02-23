FROM ubuntu:22.04

# Update package lists
RUN apt-get update -y

# Install essential libraries
RUN apt-get install -y \
    build-essential \
    git \
    cmake\
    g++\
    clang\
    wget \
    curl \
    libx11-dev \
    libxpm-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev

# Install ROOT CERN
RUN wget https://root.cern/download/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4.tar.gz
RUN tar xzf root_v6.30.04.source.tar.gz
RUN mkdir -p root && cd root && \
    ./configure --enable-roofit --enable-pythia8 --enable-fastjet && \
    make -j $(nproc) && \
    make install

# Install Fastjet
RUN wget http://fastjet.fr/repo/fastjet-3.4.2.tar.gz
RUN tar xzf fastjet-3.4.2.tar.gz
RUN mkdir -p fastjet && cd fastjet && \
    ./configure && \
    make -j $(nproc) && \
    make install

# Install Pythia8
RUN wget https://pythia.org/download/pythia83/pythia8310.tgz
RUN tar xzf pythia8310.tgz
RUN mkdir -p pythia8 && cd pythia8 && \
    ./configure && \
    make -j $(nproc) && \
    make install

# Set working directory
WORKDIR /jet_clustering_project

# Copy your project files
COPY . .


# Entry point (optional)
CMD ["bash"]
