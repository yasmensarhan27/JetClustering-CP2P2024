FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-ubuntu-20.04

# Install system dependencies
RUN apt-get update && apt-get install -y \
    git \
    root-system-bin \
    root-rootfile \
    libfastjet-dev \
    pythia8 \
    # Add any additional system dependencies here

# Install additional project dependencies
WORKDIR /your/project/path
COPY requirements.txt ./
RUN pip install -r requirements.txt

# Copy your project code
COPY . .

# Expose port for visualization (optional)
EXPOSE 8000

# Set working directory and command
WORKDIR /your/project/path
CMD ["bash"]
