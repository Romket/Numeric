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
