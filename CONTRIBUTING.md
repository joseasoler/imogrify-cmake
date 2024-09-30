# Contributing to imogrify

Thank you for being interested on contributing to imogrify! This project follows the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md).

## Questions and bug reports

You can use the [issue tracker](https://github.com/joseasoler/imogrify/issues) to ask questions and report bugs. Please use the search (including closed issues) to see if your entry has been discussed before.

## Contributions

Before preparing and submitting a PR for a feature, create an issue on the [tracker](https://github.com/joseasoler/imogrify/issues) to allow discussing and refining the idea before it is implemented.

Source code contributions must follow the [style guide](STYLE_GUIDE.md). The easiest way to comply with it is to set up [clang-format](https://clang.llvm.org/docs/ClangFormat.html) and [clang-tidy](https://clang.llvm.org/extra/clang-tidy/). You should enable the `-CMAKE_COMPILE_WARNING_AS_ERROR`, `IMOGRIFY_UNIT_TESTS`,  and `IMOGRIFY_CLANG_TIDY` CMake options when you build your code to ensure that your contribution will pass static analysis . You should also execute clang-format on all files you have modified before submitting your contribution.