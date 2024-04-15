# Use an appropriate base image with necessary dependencies for building
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND noninteractive
ENV LANG C.UTF-8

# Update package lists and install necessary packages
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

# Copy the current directory contents into the container at /app
COPY . /app

# Specify the command to run on container start
CMD ["bash"]
