# rdkvhal-miracast-raspberrypi4

Miracast RPI HAL implementation

---

## Overview
A C++ shared library providing a Miracast HAL (Hardware Abstraction Layer) for RDK-based Raspberry Pi 4 platforms.

For a comprehensive list of changes, updates, and release history, refer to the [Changelog](CHANGELOG.md).

### Features
- Supports logging wrapper aligning to RDKLogger
- Secure and warning-enforced build flags
- CMake-based build system
- BitBake/Yocto ready (multilib, dev packaging, pkg-config)

#### For enabling debug logs from hal
Create `/etc/debug.ini` and add the following line
```
LOG.RDK.MIRACAST = LOG DEBUG INFO ERROR
```

## Building

### Prerequisites
- CMake >= 3.10
- GStreamer 1.0 development libraries
- C++17 compatible compiler

### Build Steps
```sh
mkdir build && cd build
cmake ..
make
```

## Installation

To install the library and headers:
```sh
make install
```
- The shared library will be installed to `${CMAKE_INSTALL_LIBDIR}` (e.g., `/usr/lib`)
- The public header (`SoC_MiracastPlayer.h`) will be installed to `${CMAKE_INSTALL_INCLUDEDIR}` (e.g., `/usr/include`)
- A pkg-config file will be installed for easy integration

## Usage

Include the public header in your project:
```cpp
#include <SoC_MiracastPlayer.h>
```

Link with the library using pkg-config or CMake:
```sh
g++ ... $(pkg-config --cflags --libs MiracastPlayerHal)
```

## Security & Best Practices
- All builds use strong security flags and treat warnings as errors.
- Only C++17 is supported.

## License Details

This project is distributed under the terms outlined in the associated [License](LICENSE) and [Notice](NOTICE) files. Please review these files for detailed information.
