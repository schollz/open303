# Makefile for Open303 SuperCollider plugin
# Usage: make [SC_PATH=/path/to/supercollider]

# Default SuperCollider path - override with make SC_PATH=/your/path
SC_PATH ?= $(HOME)/Documents/supercollider

BUILD_DIR = build
INSTALL_DIR = open303-sc

.PHONY: all clean install uninstall help

all: $(INSTALL_DIR)

$(BUILD_DIR):
	@echo "Creating build directory..."
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Makefile: $(BUILD_DIR)
	@echo "Configuring CMake..."
	@cd $(BUILD_DIR) && cmake .. \
		-DCMAKE_BUILD_TYPE=Release \
		-DSC_PATH=$(SC_PATH) \
		-DCMAKE_INSTALL_PREFIX=$(CURDIR)/$(INSTALL_DIR)

$(INSTALL_DIR): $(BUILD_DIR)/Makefile
	@echo "Building Open303 plugin..."
	@cd $(BUILD_DIR) && cmake --build . --config Release --target install -j4
	@echo ""
	@echo "Build complete! Plugin installed to: $(INSTALL_DIR)"
	@echo ""
	@echo "To install for your user, copy the contents to:"
	@echo "  Linux:   ~/.local/share/SuperCollider/Extensions/"
	@echo "  macOS:   ~/Library/Application Support/SuperCollider/Extensions/"
	@echo "  Windows: %APPDATA%/SuperCollider/Extensions/"

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR) $(INSTALL_DIR)

install: $(INSTALL_DIR)
	@echo "Installing to SuperCollider user extensions directory..."
	@if [ "$(shell uname)" = "Darwin" ]; then \
		DEST="$(HOME)/Library/Application Support/SuperCollider/Extensions/Open303"; \
		mkdir -p "$$DEST"; \
		cp -r $(INSTALL_DIR)/Open303/* "$$DEST/"; \
		echo "Installed to: $$DEST"; \
	elif [ "$(shell uname)" = "Linux" ]; then \
		DEST="$(HOME)/.local/share/SuperCollider/Extensions/Open303"; \
		mkdir -p "$$DEST"; \
		cp -r $(INSTALL_DIR)/Open303/* "$$DEST/"; \
		echo "Installed to: $$DEST"; \
	else \
		echo "Windows detected. Please manually copy $(INSTALL_DIR)/Open303 to %APPDATA%/SuperCollider/Extensions/"; \
	fi

uninstall:
	@echo "Uninstalling Open303 from SuperCollider extensions directory..."
	@if [ "$(shell uname)" = "Darwin" ]; then \
		DEST="$(HOME)/Library/Application Support/SuperCollider/Extensions/Open303"; \
		if [ -d "$$DEST" ]; then \
			rm -rf "$$DEST"; \
			echo "Removed: $$DEST"; \
		else \
			echo "Open303 not found at: $$DEST"; \
		fi \
	elif [ "$(shell uname)" = "Linux" ]; then \
		DEST="$(HOME)/.local/share/SuperCollider/Extensions/Open303"; \
		if [ -d "$$DEST" ]; then \
			rm -rf "$$DEST"; \
			echo "Removed: $$DEST"; \
		else \
			echo "Open303 not found at: $$DEST"; \
		fi \
	else \
		echo "Windows detected. Please manually remove %APPDATA%/SuperCollider/Extensions/Open303"; \
	fi

help:
	@echo "Open303 SuperCollider Plugin - Build System"
	@echo ""
	@echo "Usage:"
	@echo "  make              - Build the plugin to ./open303-sc/"
	@echo "  make install      - Build and install to user Extensions directory"
	@echo "  make uninstall    - Remove from user Extensions directory"
	@echo "  make clean        - Remove build artifacts"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "Options:"
	@echo "  SC_PATH=/path     - Path to SuperCollider source (default: ~/Documents/supercollider)"
	@echo ""
	@echo "Example:"
	@echo "  make SC_PATH=/usr/local/src/supercollider"
