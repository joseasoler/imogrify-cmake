# imogrify

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0) [![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](CODE_OF_CONDUCT.md)

Image conversion tool optimized for processing large batches of files.

## Contributing

imogrify encourages community involvement and contributions. Check the [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) files for details. You can check all contributors in the [contributors list](https://github.com/joseasoler/imogrify/graphs/contributors).

## License

imogrify is licensed under the Mozilla Public License, v. 2.0. See the [LICENSE](LICENSE) file for details. Check the [MPL 2.0 FAQ](https://www.mozilla.org/en-US/MPL/2.0/FAQ/) to learn more.

## Building

Building imogrify requires [CMake](https://cmake.org/) and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20).

### Dependencies

* **[Boost.Filesystem](https://www.boost.org/doc/libs/master/libs/filesystem/doc/index.htm)**: Filesystem operations with UTF-8 encoding. See [this link](https://www.boost.org/doc/libs/1_86_0/libs/nowide/doc/html/index.html#using_integration) for details.

* **[Boost.NoWide](https://www.boost.org/doc/libs/master/libs/nowide/doc/html/index.html)**: Provides implementations of some standard functions which are UTF-8 aware on Windows without requiring the use of the Wide API.

* **[Catch2](https://github.com/catchorg/Catch2)**: Used for unit testing. Only required if `IMOGRIFY_BUILD_UNIT_TESTS` is set to on.

* **[fmt](https://fmt.dev/latest/index.html)**: Provides formatting and printing utilities.

### CMake options

* `CMAKE_COMPILE_WARNING_AS_ERROR`: When this option is enabled, compilers will treat warnings as errors. If `IMOGRIFY_CLANG_TIDY` is enabled, [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) will also treat its warnings as errors.
* `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Requires the [Catch2](https://github.com/catchorg/Catch2) library. Off by default.
* `IMOGRIFY_CLANG_ALL_WARNINGS`: This option is only available when the [clang](https://clang.llvm.org/) compiler is in use. This option enables almost every warning from this compiler, except for a few that cause issues with imogrify. This may trigger unexpected positives when using newer clang versions. Off by default.
* `IMOGRIFY_CLANG_TIDY`: If [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) is available, it will be used to analyze the project. Off by default.

### CMake presets

imogrify includes a set of CMake presets intended for use in CI. These presets use [vcpkg](https://github.com/microsoft/vcpkg) to retrieve and build the dependencies.

To use these presets locally, you will need to [install vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started) and set the environment variable `VCPKG_ROOT` to its path. It is recommended to install vcpkg in a short path to avoid building issues with some dependencies. Keep in mind that [vcpkg collects telemetry data by default](https://learn.microsoft.com/en-us/vcpkg/about/privacy). It is possible to disable it by setting the `VCPKG_DISABLE_METRICS` environment variable.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
