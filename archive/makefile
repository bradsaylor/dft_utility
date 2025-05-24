# === Directory Structure ===
IDIR = ./include
SDIR = ./src
ODIR = ./build
TOOLSDIR = ./tools

# === Compiler and Flags ===
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -MMD -MP -I$(IDIR)
LIBS = -lm

# === Generator source files ===
GEN_INDEX_SRC = $(TOOLSDIR)/make_fft_reverse_index_LUT.c
GEN_INDEX_HDR = $(TOOLSDIR)/make_fft_reverse_index_LUT.h
GEN_TWID_SRC  = $(TOOLSDIR)/make_fft_twiddle_factor_LUT.c
GEN_TWID_HDR  = $(TOOLSDIR)/make_fft_twiddle_factor_LUT.h

# === Generator executables ===
GEN_INDEX_BIN = $(ODIR)/gen_index
GEN_TWID_BIN  = $(ODIR)/gen_twiddle

# === Generated source/header files
GEN_SRC = $(SDIR)/fft_reverse_index_LUT.c $(SDIR)/fft_twiddle_factor_LUT.c
GEN_HDR = $(IDIR)/fft_reverse_index_LUT.h $(IDIR)/fft_twiddle_factor_LUT.h
TABLE_STAMP = $(ODIR)/tables.stamp

# === All source files (regular + generated)
SRC_ALL = $(wildcard $(SDIR)/*.c)
SRC = $(filter-out $(GEN_INDEX_SRC) $(GEN_TWID_SRC), $(SRC_ALL)) $(GEN_SRC)

# === Object and dependency files (robust even if files don't yet exist)
OBJ = $(foreach src,$(SRC),$(ODIR)/$(notdir $(src:.c=.o)))
DEPS = $(OBJ:.o=.d)

# === Final binary
TARGET = dft_util

# === Default target
.PHONY: all
all: $(TARGET)

# === Link the final executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

# === Ensure tables are generated before compiling object files
$(OBJ): $(TABLE_STAMP)

# === Compile rule for regular .c files in src/
$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# === Explicit compile rules for generated source files
$(ODIR)/fft_reverse_index_LUT.o: $(SDIR)/fft_reverse_index_LUT.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/fft_twiddle_factor_LUT.o: $(SDIR)/fft_twiddle_factor_LUT.c
	$(CC) $(CFLAGS) -c -o $@ $<

# === Table generation stamp
.PHONY: tables
tables: $(TABLE_STAMP)

$(TABLE_STAMP): $(GEN_INDEX_BIN) $(GEN_TWID_BIN)
	@mkdir -p $(SDIR) $(IDIR)
	$(GEN_INDEX_BIN)
	$(GEN_TWID_BIN)
	touch $@

# === Generator binary build rules
$(GEN_INDEX_BIN): $(GEN_INDEX_SRC) $(GEN_INDEX_HDR)
	@mkdir -p $(ODIR)
	$(CC) -o $@ $< $(LIBS)

$(GEN_TWID_BIN): $(GEN_TWID_SRC) $(GEN_TWID_HDR)
	@mkdir -p $(ODIR)
	$(CC) -o $@ $< $(LIBS)

# === Auto-dependency include
-include $(DEPS)

# === Clean all build artifacts
.PHONY: clean
clean:
	rm -f $(OBJ) $(DEPS) $(TARGET) \
		$(GEN_INDEX_BIN) $(GEN_TWID_BIN) \
		$(GEN_SRC) $(GEN_HDR) $(TABLE_STAMP)
