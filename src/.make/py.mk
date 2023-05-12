
# Python shell command
PY := python3

# Directory, containing python scripts
PY_DIR := $(MAKE_WS)/py_scripts

# Useful python command(s)
PY_DIR_SEARCH := $(PY) $(PY_DIR)/dir_search.py
PY_APPEND_CMD := $(PY) $(PY_DIR)/append_cmd.py
PY_DEL := $(PY) $(PY_DIR)/del.py

# Function: Find all directories, containing at least one file with a 
# 				matching an extension
# 	Parameters:
# 		[1]: Directory path
# 		[2]: Extension
GET_DIRS = $(shell $(PY_DIR_SEARCH) -f $(1) -e $(2))

# Function: Find all files with a matching extension
# 	Parameters:
# 		[1]: Directory path
# 		[2]: Extension
GET_FILES = $(wildcard $(addsuffix /*$(2),$(call GET_DIRS,$(1),$(2))))