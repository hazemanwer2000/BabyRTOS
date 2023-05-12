#############################################################
# 
# Filename: append_cmd.py
# Description: Implemented as a command-line function, that appends
#               a command to a '.d' file
#                   
# Parameters:
#   [1] File, whitespace not permitted
#   [2] Command, whitespace permitted
# Return:
#   [stdout]
#       None
#   [else] 
#       Appends a command to a file
# Author: Eng. Hazem Anwer
# Github: https://github.com/hazemanwer2000
# 
#############################################################

import sys
import os

# Fix spacing within arguments
args = sys.argv[2:]
for i in range(len(args)):
    if ' ' in args[i]:
        args[i] = '"' + args[i] + '"'

# Append to file
with open(sys.argv[1], 'a') as f:
    f.write('\t' + ' '.join(args))