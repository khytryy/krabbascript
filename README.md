# Krabbascript 2.5.3-prototype
![GitHub License](https://img.shields.io/github/license/khytryy/krabbascript)
![GitHub top language](https://img.shields.io/github/languages/top/khytryy/krabbascript?logo=c&label=)

Krabbascript is a statically typed, AOT compiled, high level programming language designed to be easy to write and read.

> [!CAUTION]
> This project is still in its early stages, so expect a lot of unfinished stuff. Check-out our [Discord](https://discord.gg/MQT4YgEYvn) for news and progress on Krabbascript!

Krabbascript mixes C, Lua, and Python together to form simple, and easy to learn syntax.

## Getting started

### Prerequisites

#### Git (optional)

Git is for cloning Krabbascript's source code.
You can check if Git is installed with:

```bash
git --version
```

You can then clone the repo with

```bash
git clone https://github.com/khytryy/krabbascript
```

#### Make/CMake

To build Krabbascript, you have to use GNU Make or compatible, or CMake.

#### C compiler

Krabbascript is written in C, and requires a C compiler do build. I genuinely recommend that you use gcc to build the compiler, because its set as default in the Makefile. If you cant use gcc for some reason, you can edit CC variable to the compiler you want in the Makefile.

### Building Krabbascript

```bash
make && sudo make install
```

This creates the final binary in the project's directory and copies the compiler to `/usr/local/bin/kscript`.

#### Building with CMake

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build
```

This builds the binary in `build/` and copies the compiler to CMake's default install location under `bin/`.

### Libraries used

- [tomlc17](https://github.com/cktan/tomlc17), MIT License

