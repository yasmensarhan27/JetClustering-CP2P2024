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
#RUN wget https://root.cern.ch/root_v6.26.06.source.tar.gz
#RUN tar xzf root_v6.26.06.source.tar.gz
#RUN mkdir -p root && cd root && \
 #   ./configure --enable-roofit --enable-pythia8 --enable-fastjet && \
  #  make -j $(nproc) && \
  #  make install

# Install Fastjet
#RUN wget https://downloads.fastjet.fr/public/releases/fastjet-3.7.4.tar.gz
#RUN tar xzf fastjet-3.7.4.tar.gz
#RUN mkdir -p fastjet && cd fastjet && \
#    ./configure && \
#    make -j $(nproc) && \
#    make install

# Install Pythia8
#RUN wget https://pythia.org/download/pythia8/pythia8300.tgz
#RUN tar xzf pythia8300.tgz
#RUN mkdir -p pythia8 && cd pythia8 && \
#   ./configure && \
#    make -j $(nproc) && \
#    make install
#
# Set working directory
WORKDIR /jet_clustering_project

# Copy your project files
COPY . .

# Expose ROOT port (optional)
EXPOSE 8000

# Entry point (optional)
CMD ["bash"]
