
FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
# Update package lists
RUN apt-get update -y

# Install essential libraries
RUN apt-get install -y \
    build-essential \
    git \
    cmake \
    g++ \
    clang \
    wget \
    curl \

# Install ROOT CERN
RUN wget https://root.cern/download/root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    tar xzf root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    rm root_v6.30.04.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz && \
    cd root && \
    ./configure --enable-roofit --enable-pythia8 --enable-fastjet && \
    make -j$(nproc) && \
    make install && \
    cd ..

# Install Fastjet
RUN wget http://fastjet.fr/repo/fastjet-3.4.2.tar.gz && \
    tar xzf fastjet-3.4.2.tar.gz && \
    cd fastjet-3.4.2 && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    cd ..

# Install Pythia8 (if needed, uncomment and adjust as necessary)

# Set working directory
WORKDIR /jetclustering

# Copy your project files
COPY . .

# Entry point (optional)
CMD ["bash"]
