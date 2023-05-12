#############################################################
# 
# Filename: dir_search.py
# Description: Implemented as a command-line function, that returns a list of
#                   relative file paths within a directory, that match a
#                   a specific suffix pattern, or extension.
#                   
# Parameters [Implemented with flags]:
#   [1] -f DIR_PATH
#   [2] -e EXTENSION
# Return:
#   [stdout] 
#       White-space separated list of matching paths
#   [else] 
#       None
# Author: Eng. Hazem Anwer
# Github: https://github.com/hazemanwer2000
# 
#############################################################

import sys
import os

# Get all arguments in a dictionary called 'args'
args = {}
for i in range(1, len(sys.argv), 2):
    args[sys.argv[i][1:]] = sys.argv[i+1]

# Function: Match extension ('ext' must be lowercase)
def match_ext(f, ext):
    return (f[-len(ext):]) == ext

# Function: Check if file is hidden (e.g: begins with '.')
def is_not_hidden(f):
    return True if f[f.rfind('/')+1] != '.' else False

# Function: Get list of matching files
def dir_search(dir_path, ext):
    # ! list all files and folders, with relative path
    listed = [dir_path + '/' + f for f in os.listdir(dir_path)]

    # ! filter for files, with matching extension
    listed_files = [f for f in listed if os.path.isfile(f) and match_ext(f, ext)]
    
    # ! filter for directories
    listed_dirs = [f for f in listed if os.path.isdir(f) and is_not_hidden(f)]
    
    # ! Create and append to return-list
    ret_list = [dir_path] if len(listed_files) > 0 else []
    for dir in listed_dirs:
        ret_list += dir_search(dir, ext)
        
    return ret_list

# Call 'dir_search' and curate result to 'STDOUT'
ret_list = dir_search(args['f'], args['e'])
print(' '.join(ret_list))
