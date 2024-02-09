#!/bin/bash
# Add a user with sudo privileges
useradd -m -s /bin/bash -G sudo codespace
echo 'codespace ALL=(ALL) NOPASSWD:ALL' > /etc/sudoers.d/codespace

# Switch to the codespace user
su - codespace
# Source the environment setup scripts for ROOT CERN, FastJet, and Pythia
source /root/root/bin/thisroot.sh

# Add any additional setup commands for your project

# Print a welcome message
echo "Devcontainer initialized successfully!"
