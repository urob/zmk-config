#!/usr/bin/env bash

### Step 1: Update OS
sudo apt update
sudo apt upgrade

### Step 2: Install dependencies
sudo apt-get install --yes --no-install-recommends git cmake ninja-build gperf \
  ccache dfu-util device-tree-compiler wget \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
  make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1

### Step 3: Install Zephyr SDK

# Find latest release version
# ZSDK_URL="https://github.com/zephyrproject-rtos/sdk-ng/releases/latest"
# ZSDK_VERSION="$(curl -fsSLI -o /dev/null -w %{url_effective} ${ZSDK_URL} | sed 's/^.*v//')"
ZSDK_VERSION="0.15.2"

# Download and verify latest Zephyr SDK bundle
cd ~/.local
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZSDK_VERSION}/zephyr-sdk-${ZSDK_VERSION}_linux-x86_64.tar.gz
wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZSDK_VERSION}/sha256.sum | shasum --check --ignore-missing
## TODO: abort if exit code is error

# Extract the Zephyr SDK bundle archive
tar xvf zephyr-sdk-${ZSDK_VERSION}_linux-x86_64.tar.gz
rm zephyr-sdk-${ZSDK_VERSION}_linux-x86_64.tar.gz

# Run the Zephyr SDK bundle setup script
cd zephyr-sdk-${ZSDK_VERSION}
./setup.sh

# Install udev rules, which allow you to flash most Zephyr boards as a regular user
sudo cp ~/zephyr-sdk-${ZSDK_VERSION}/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d
sudo udevadm control --reload

### Step 4: Get Zephyr and install Python dependencies

# Install West
pip3 install --user -U west  # may need to replace with "python3 -m pip" or "python -m pip"

# Get the Zephyr cource code:
cd ~/zmk
west init -l app/
west update

# Export a Zephyr CMake package to allow CMake to load the code needed to build ZMK
west zephyr-export

# Install Zephyr Python Dependencies
pip3 install --user -r zephyr/scripts/requirements.txt  # see above

### Step 5: Install Docusaurus
sudo apt-get install --yes --no-install-recommends npm
cd ~/zmk/docs
npm ci

