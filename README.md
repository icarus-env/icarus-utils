# icarus-utils
[![Linux CI Status](https://github.com/icarus-env/icarus-utils/actions/workflows/linux.yml/badge.svg)](https://github.com/icarus-env/icarus-utils/actions/workflows/linux.yml?query=workflow%3Alinux)
[![Windows CI Status](https://github.com/icarus-env/icarus-utils/actions/workflows/windows.yml/badge.svg)](https://github.com/icarus-env/icarus-utils/actions/workflows/windows.yml?query=workflow%3Awindows)
[![codecov](https://codecov.io/gh/icarus-env/icarus-utils/graph/badge.svg?token=nCjYPy5rSt)](https://codecov.io/gh/icarus-env/icarus-utils)
[![Docs Status](https://github.com/icarus-env/icarus-utils/actions/workflows/docs.yml/badge.svg)](https://github.com/icarus-env/icarus-utils/actions/workflows/docs.yml?query=workflow%3Adocs)

`icarus-utils` is a C++ library encompassing general-purpose modules for abstraction and utility in the ICARUS environment.

>**Note:** `icarus-utils` has been initially developed to be used by the `icarus` library and is, subsequetly, strongly driven by its requirements.

**Documentation Website:** https://icarus-env.github.io/icarus-utils/

**Table of Contents**
- [Build from Source](#build-from-source)
  - [Build Prerequisites](#build-prerequisites)
  - [Build Instructions](#build-instructions)
- [Run the Tests](#run-the-tests)
- [Generate HTML Documentation](#generate-html-documentation)
- [License](#license)

## Build from Source
OS: Windows (tested on Windows 11), or Linux (tested on Ubuntu 22.04).

### Build Prerequisites
* C/C++ compiler supporting C++17 (e.g., MSVC for Windows, GCC, Clang)
* Cross-platform build system: CMake (minimum version 3.22)
* Cross-platform package manager: [vcpkg](https://github.com/microsoft/vcpkg) 
    - Installtion: follow the [installation instructions](https://learn.microsoft.com/de-de/vcpkg/get_started/get-started?pivots=shell-cmd#1---set-up-vcpkg). 
    - Set the environment variable `VCPKG_ROOT` (on Linux, e.g., in `.bashrc` file).

### Build Instructions
#### Build as Standalone Project
1. Clone this repository and navigate to the project directory:
```bash
git clone https://github.com/icarus-env/icarus-utils.git && cd icarus-utils
```

2. Generate the build files (CMake configuration):
> **Note:** A `CMakePresets.json` file is used to manage different CMake configurations.

```bash
cmake --preset <preset_name>
```
* `<preset_name>`
    * `no_tests_<debug/release>`: Build configuration without tests (Debug/Release mode)
    * `tests_<debug/release>`: Build configuration including tests (Debug/Release mode).

3. Build the project:
```bash
# --config is required if using the multi-config generator MSBuild of Visual Studio.
cmake --build build [--config <Debug/Release>]
```

#### Integrate into Existing Project
1. Add this repository as a Git submodule:
```bash
git submodule add https://github.com/icarus-env/icarus-utils.git <path_to_submodule>
```

2. Include the library in your CMake project:
```cmake
add_subdirectory(<path_to_submodule>)
target_link_libraries(<your_target> PRIVATE icarus-utils)
```

## Run the Tests
1. Build the project with tests (see [above](#build-as-standalone-project)).
2. Run all tests using the CMake tool `ctest`:
```bash
# --build-config is required if using the multi-config generator MSBuild of Visual Studio.
cd build && ctest --output-on-failure [--build-config <Debug/Release>]
```

3. **[Only for build with GCC] [optional]** Generate a coverage report using the Python tool `gcovr`:
```bash
# Run from the build/ directory
mkdir coverage_report
gcovr -r .. --exclude-unreachable-branches -e '/.*/build/' -e '/.*/tests/' --html --html-details -o coverage_report/coverage.html
```

## Generate HTML Documentation
**Prerequisites:** Doxygen, Graphviz

Navigate to the `docs/` directory and run doxygen:
```bash
cd docs && doxygen Doxyfile
```

## License
`icarus-utils` is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
