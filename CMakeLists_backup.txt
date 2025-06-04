cmake_minimum_required(VERSION 3.15)
project(dft_util C)

# === Paths ===
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(GEN_SRC_DIR ${CMAKE_SOURCE_DIR}/tools/generated/src)
set(GEN_INC_DIR ${CMAKE_SOURCE_DIR}/tools/generated/include)

# Ensure output directories exist
file(MAKE_DIRECTORY ${GEN_SRC_DIR})
file(MAKE_DIRECTORY ${GEN_INC_DIR})

# Output directory for built binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# === Include paths ===
include_directories(${INC_DIR})
include_directories(${GEN_INC_DIR})

# === Generator executables (actual generator source files)
add_executable(gen_index tools/make_fft_reverse_index_LUT.c)
target_link_libraries(gen_index m)

add_executable(gen_twiddle tools/make_fft_twiddle_factor_LUT.c)
target_link_libraries(gen_twiddle m)

# === Generated files to be created by the generators
set(GEN_SRC
  ${GEN_SRC_DIR}/fft_reverse_index_LUT.c
  ${GEN_SRC_DIR}/fft_twiddle_factor_LUT.c
)

set(GEN_HDR
  ${GEN_INC_DIR}/fft_reverse_index_LUT.h
  ${GEN_INC_DIR}/fft_twiddle_factor_LUT.h
)

# === Custom commands to run generators
add_custom_command(
  OUTPUT ${GEN_SRC_DIR}/fft_reverse_index_LUT.c ${GEN_INC_DIR}/fft_reverse_index_LUT.h
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gen_index
          ${GEN_SRC_DIR}/fft_reverse_index_LUT.c
          ${GEN_INC_DIR}/fft_reverse_index_LUT.h
  DEPENDS gen_index
  COMMENT "Generating fft_reverse_index_LUT"
)

add_custom_command(
  OUTPUT ${GEN_SRC_DIR}/fft_twiddle_factor_LUT.c ${GEN_INC_DIR}/fft_twiddle_factor_LUT.h
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gen_twiddle
          ${GEN_SRC_DIR}/fft_twiddle_factor_LUT.c
          ${GEN_INC_DIR}/fft_twiddle_factor_LUT.h
  DEPENDS gen_twiddle
  COMMENT "Generating fft_twiddle_factor_LUT"
)

# === Source files (excluding generator .c files)
file(GLOB SRC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.c)

# === Final executable build
add_executable(dft_util
  ${SRC_FILES}
  ${GEN_SRC}
)

target_link_libraries(dft_util m)

# === Ensure dft_util depends on generated files
add_dependencies(dft_util gen_index gen_twiddle)
