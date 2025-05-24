# DFT Utility

A lightweight C library and command-line utility for computing the Discrete Fourier Transform (DFT) and related operations, including an optimized Goertzel algorithm implementation. Built using CMake for portability and easy integration into signal processing workflows.

---

## Features

- Direct DFT computation (complex input/output)
- Goertzel algorithm for efficient single-frequency analysis
- Configurable twiddle factor and bit-reversal lookup tables
- Clean modular C structure with unit tests
- Build system using CMake for cross-platform support

---

## Project Structure

```text
dft_util/
├── CMakeLists.txt          # CMake build configuration
├── src/                    # Main source code
├── include/                # Public headers
├── tools/                  # Code generation and utilities
├── tests/                  # Unit tests
├── build/                  # CMake build directory (ignored)
└── README.md               # This file
