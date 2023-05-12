# SETUP

## install CMake

    sudo apt update
    sudo apt install -y cmake
    cmake --version

## install the GCC Compiler:

- Start by updating the packages list:

        sudo apt update

- Install the build-essential package by typing:

        sudo apt install build-essential

- The command installs a bunch of new packages including gcc, g++ and make.

- You may also want to install the manual pages about using GNU/Linux for development:

        sudo apt-get install manpages-dev

- To validate that the GCC compiler is successfully installed, use the gcc --version command which prints the GCC version:

        gcc --version

## install GTK+ 3.0
    sudo apt-get install libgtk-3-dev

## Use for update new sony camera sdk
- add user functions  to library CameraDevice
+ File CameraDevice.h 

    std::int64_t get_device_handle() const;

+ File CameraDevice.cpp

    std::int64_t CameraDevice::get_device_handle() const
    {
        return m_device_handle;
    }

## BUILD

cd example01_payload_control
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
