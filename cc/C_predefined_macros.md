# Pre-defined C/C++ Compiler Macros

## Standard Predefined Macros

|Macro|Description|
|---|---|
|\_\_FILE__|name of the current input file|
|\_\_LINE__|current input line number|
|\_\_DATE__|the date on which the preprocessor is being run|
|\_\_TIME__|the time at which the preprocessor is being run|

## Language Standards

|Name|Macro|Standard|
|---|---|---|
|C90|\_\_STDC__|ISO/IEC 9899:1990|
|C99|\_\_STDC_VERSION__ = 199901L|ISO/IEC 9899:1999|
|C11|\_\_STDC_VERSION__ = 201112L|ISO/IEC 9899:2011|
|C++98|\_\_cplusplus = 199711L|ISO/IEC 14882:1998|
|C++11|\_\_cplusplus = 201103L|ISO/IEC 14882:2011|


## Compiler

- GCC C/C++

|Type|Macro|Description|
|---|---|---|
|Identification|\_\_GNUC__||
|Version|\_\_GNUC__|Version|
|Version|\_\_GNUC_MINOR__|Revision|
|Version|\_\_GNUC_PATCHLEVEL__|Patch (introduced in version 3.0)|

- Clang

|Type|Macro|Description|
|---|---|---|
|Identification|\_\_clang__||
|Version|\_\_clang_major__|Major version|
|Version|\_\_clang_minor__|Minor version|
|Version|\_\_clang_patchlevel__|Patch leve|
|Version|\_\_clang_version__||
|LLVM|\_\_llvm__||

- Microsoft Visual C++

|Type|Macro|Description|
|---|---|---|
|Identification|_MSC_VER||
|Version|_MSC_VER||
|Version|_MSC_FULL_VER||
|Version|_MSC_BUILD||

- MinGW and MinGW-w64

|Type|Macro|Description|
|---|---|---|
|Identification|\_\_MINGW32__||
|Version|__MINGW32_MAJOR_VERSION||
|Version|__MINGW32_MINOR_VERSION||
|Identification|\_\_MINGW64__||
|Version|__MINGW64_VERSION_MAJOR||
|Version|__MINGW64_VERSION_MINOR||

- Intel C/C++

|Type|Macro|Description|
|---|---|---|
|Identification|__INTEL_COMPILER||
|Identification|__ICC||
|Version|__INTEL_COMPILER||
|Version|__INTEL_COMPILER_BUILD_DATE||

## Libraries

|Library|Identification|Version|
|---|---|---|
|GNU glibc|\_\_GLIBC__|\_\_GLIBC_MINOR__|
|GNU libstdc++|\_\_GLIBCPP__, \_\_GLIBCXX__|\_\_GLIBCPP__, \_\_GLIBCXX__|

## Operating systems

|System|Identification|
|---|---|
|GNU/Linux|\_\_gnu_linux__|
|Linux kernel|\_\_linux__ , linux, __linux|
|MacOS|macintosh, Macintosh, \_\_APPLE__|
|Windows|\_WIN32, \_WIN64, \_\_WIN32__, \_\_WINDOWS__|
|FreeBSD|\_\_FreeBSD__, BSD|

## Architectures

|Architecture|Identification|Description|
|---|---|---|
|AMD64|\_\_amd64_, \_\_amd64, \_\_x86_64__, \_\_x86_64|Defined by GNU C and Sun Studio|
|ARM|\_\_arm__|Defined by GNU C and RealView|
|ARM64|\_\_aarch64__|Defined by GNU C 1|

## Reference

[Standard Predefined Macros](https://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html#Predefined-Macros)

[Pre-defined C/C++ Compiler Macros](https://sourceforge.net/p/predef/wiki/Home/)
