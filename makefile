<<<<<<< Updated upstream
# ====================== Project Settings ======================

NAME = NUMERIC
ICON = icon.png
DESCRIPTION = "All the numeric methods you'll ever need!"

SRC = src
BUILD = build
BIN = $(BUILD)/bin
OBJ = $(BUILD)/obj

SOURCES = $(wildcard $(SRC)/*.txt)

COMBINED = $(OBJ)/combined.txt
OUTPUT = $(BIN)/$(NAME).8xp

# ====================== Build Tasks ======================

all: $(OUTPUT)

# Create directories
$(OBJ):
	@mkdir -p $(OBJ)

$(BIN):
	@mkdir -p $(BIN)

# Combine all source files into one
$(COMBINED): $(SOURCES) | $(OBJ)
	@if [ -z "$(SOURCES)" ]; then \
		echo "No source files found."; \
		exit 1; \
	fi
	@echo "Combining source files..."
	@cat $(SOURCES) > $(COMBINED)
	@echo "Done."

# Build with tibasic
$(OUTPUT): $(COMBINED) | $(BIN)
	@echo "Building..."
	@tibasic -o $(OUTPUT) $(COMBINED)
	@echo "Done."

# Delete built files
clean:
	@echo "Cleaning built files..."
	@rm -rf $(BUILD)
	@echo "Done."

.PHONY: all clean
=======
# ====== CONFIGURATION ======

PROJECT_NAME := NUMERIC
VERSION := 0.0.1

# Directories
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

# Files
SRC := $(wildcard $(SRC_DIR)/*.txt)  # Input files are .txt (TI-BASIC code)
BIN_SRC := $(SRC:.txt=.bin)  # Tokenized .bin files (converted from .txt)
OBJ := $(OBJ_DIR)/combined.bin
BIN_PROG := $(BIN_DIR)/$(shell echo $(PROJECT_NAME) | tr a-z A-Z).8xp
BIN_MAP := $(BIN_DIR)/$(shell echo $(PROJECT_NAME) | tr a-z A-Z).map

# Optional image
IMAGE_PATH := image.png
IMAGE_PROG := $(BIN_DIR)/$(notdir $(IMAGE_PATH))

# Compression: none, xz0, xz7, auto
COMPRESS ?= auto

# Autotest flag (CEmu emulator)
TEST := false

# Timestamp (ISO 8601 UTC)
BUILD_TIME := $(shell date -u +"%Y-%m-%dT%H:%M:%SZ")

# ====== BUILD RULES ======

all: prep validate_sources $(BIN_SRC) $(BIN_PROG) $(BIN_MAP) $(IMAGE_PROG) test

# Create build folders
prep:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Validate .txt files
validate_sources:
	@echo "Validating source files..."
	@if [ -z "$(SRC)" ]; then \
		echo "Error: No source files found in $(SRC_DIR). Aborting."; exit 1; \
		fi
	@for file in $(SRC); do \
		if ! [ -s "$$file" ]; then \
			echo "Error: File $$file is empty."; exit 1; \
		fi; \
	done
	@echo "All source files passed validation."

# Tokenize .txt files into .bin files
$(BIN_SRC): $(SRC)
	@echo "Tokenizing .txt files into .bin files..."
	@for file in $(SRC); do \
		tokenize8x "$$file" -o "$(OBJ_DIR)/$$(basename $$file .txt).bin"; \
	done

# Combine tokenized .bin files
$(OBJ): $(BIN_SRC)
	@echo "Combining tokenized binaries into $(OBJ)..."
	@cat $(BIN_SRC) > $(OBJ)

# Tokenize into .8xp with convbin (new flags)
$(BIN_PROG): $(OBJ)
	@echo "Tokenizing with compression mode: $(COMPRESS)..."
	$(eval COMPRESSION_FLAG := $(if $(filter $(COMPRESS),none),,$(shell echo -e "-e $(COMPRESS)")))
	@convbin -j bin -k 8xp -n $(PROJECT_NAME) $(COMPRESSION_FLAG) -i "$<" -o "$@"

# Generate .map file with metadata
$(BIN_MAP): $(OBJ)
	@echo "Generating map file..."
	@echo "Program: $(PROJECT_NAME)" > "$@"
	@echo "Version: $(VERSION)" >> "$@"
	@echo "Compression: $(COMPRESS)" >> "$@"
	@echo "Build Timestamp: $(BUILD_TIME)" >> "$@"
	@echo "Sources:" >> "$@"
	@for file in $(SRC); do echo "  - $$file" >> "$@"; done

# Copy optional image file
$(IMAGE_PROG): $(IMAGE_PATH)
	@if [ -f "$(IMAGE_PATH)" ]; then \
		echo "Copying image $(IMAGE_PATH)..."; \
		cp "$(IMAGE_PATH)" "$(IMAGE_PROG)"; \
	else \
		echo "No image file found at $(IMAGE_PATH), skipping."; \
	fi

# Optional emulator test
test:
ifeq ($(TEST),true)
	@echo "Running autotest with CEmu..."
	cemu --test $(BIN_PROG)
else
	@echo "Autotest skipped. Set TEST=true to enable testing."
endif

# Clean up build output
clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR)

.PHONY: all clean prep validate_sources test
>>>>>>> Stashed changes
