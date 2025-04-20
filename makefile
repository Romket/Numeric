NAME = NUMERIC
ICON = icon.png
DESCRIPTION = "All the numeric methods you'll ever need!"

# TODO: switch to zx0 for likely smaller executable size
COMPRESSED = YES
COMPRESSED_MODE = zx7
COMPRESSED_MODE = zx0

ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# Default make gfx
MAKE_GFX = cd $(GFXDIR) && $(CONVIMG)

HAS_PRINTF = NO

CFLAGS += -Iinclude

# ----------------------------

include $(shell cedev-config --makefile)