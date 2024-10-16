# imogrify

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0) [![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](CODE_OF_CONDUCT.md)

Image conversion tool optimized for processing large batches of files.

## Contributing

imogrify encourages community involvement and contributions. Check the [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) files for details. You can check all contributors in the [contributors list](https://github.com/joseasoler/imogrify/graphs/contributors).

## License

imogrify is licensed under the Mozilla Public License, v. 2.0. See the [LICENSE](LICENSE) file for details. Check the [MPL 2.0 FAQ](https://www.mozilla.org/en-US/MPL/2.0/FAQ) to learn more.

The repository includes third party dependencies as source code in the thirdparty subfolder. Each one of them is under their own license, which is included in their respective folder. 

## Building

Building imogrify requires [CMake](https://cmake.org) and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20).

### CMake presets

imogrify includes a set of CMake presets intended for use in CI, which can also be used for development. These presets use [vcpkg](https://github.com/microsoft/vcpkg) to retrieve and build the dependencies.

To use these presets locally, you will need to [install vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started) and set the environment variable `VCPKG_ROOT` to its path. It is recommended to install vcpkg in a short path to avoid building issues with some dependencies. Keep in mind that [vcpkg collects telemetry data by default](https://learn.microsoft.com/en-us/vcpkg/about/privacy). It is possible to disable it by setting the `VCPKG_DISABLE_METRICS` environment variable.

### Dependencies

imogrify expects to have the following dependencies available to be retrieved through `find_package`.

* **[Boost.Filesystem](https://www.boost.org/doc/libs/master/libs/filesystem/doc/index.htm)**: Filesystem operations with UTF-8 encoding. See [this link](https://www.boost.org/doc/libs/master/libs/nowide/doc/html/index.html#using_integration) for details.

* **[Boost.NoWide](https://www.boost.org/doc/libs/master/libs/nowide/doc/html/index.html)**: Provides implementations of some standard functions which are UTF-8 aware on Windows without requiring the use of the Wide API.

* **[Catch2](https://github.com/catchorg/Catch2)**: Used for unit testing. Only required if `IMOGRIFY_BUILD_UNIT_TESTS` is set to on.

* **[fmt](https://fmt.dev/latest/index.html)**: Provides formatting and printing utilities.

* **[libpng](http://www.libpng.org)**: A library implementing an interface for reading and writing PNG (Portable Network Graphics) format files."

* **[Magic Enum](https://github.com/Neargye/magic_enum)**: Provides static reflection for enums.

* **[nanobench](https://nanobench.ankerl.com)**: A platform independent microbenchmarking library for C++. Only required if `IMOGRIFY_BUILD_DEPENDENCY_BENCHMARKS` or `IMOGRIFY_BUILD_IMOGRIFY_BENCHMARKS` are enabled. 

The following dependencies are included as source code in the thirdparty folder of the imogrify repository.

* **[wuffs](https://github.com/google/wuffs)**: A library for Wrangling Untrusted File Formats Safely.

Compiling with the `IMOGRIFY_BUILD_DEPENDENCY_BENCHMARKS` CMake option enabled requires additional dependencies. These libraries are not used by the imogrify binary.

* **[libspng](https://libspng.org)**: libspng (simple png) is a C library for reading and writing Portable Network Graphics (PNG) format files with a focus on security and ease of use.

* **[lodepng](https://lodev.org/lodepng)**: LodePNG is a PNG image decoder and encoder, all in one, no dependency or linkage to zlib or libpng required.

* **[tabulate](https://github.com/p-ranav/tabulate)**: Table Maker for Modern C++.

### CMake options

* `CMAKE_COMPILE_WARNING_AS_ERROR`: When this option is enabled, compilers will treat warnings as errors. If `IMOGRIFY_CLANG_TIDY` is enabled, [clang-tidy](https://clang.llvm.org/extra/clang-tidy) will also treat its warnings as errors.
* `IMOGRIFY_BUILD_DEPENDENCY_BENCHMARKS`: Compile benchmarks comparing potential dependencies for imogrify. Requires the [nanobench](https://nanobench.ankerl.com) library along with additional dependencies. Off by default.
* `IMOGRIFY_BUILD_IMOGRIFY_BENCHMARKS`: Compile microbenchmarks for some parts of the imogrify code. Requires the [nanobench](https://nanobench.ankerl.com) library. Off by default.
* `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Requires the [Catch2](https://github.com/catchorg/Catch2) library. Off by default.
* `IMOGRIFY_CLANG_ALL_WARNINGS`: This option is only available when the [clang](https://clang.llvm.org) compiler is in use. This option enables almost every warning from this compiler, except for a few that cause issues with imogrify. This may trigger unexpected positives when using newer clang versions. Off by default.
* `IMOGRIFY_CLANG_TIDY`: If [clang-tidy](https://clang.llvm.org/extra/clang-tidy) is available, it will be used to analyze the project. Off by default.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
