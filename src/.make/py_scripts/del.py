#############################################################
# 
# Filename: del.py
# Description: Implemented as a command-line function, that deletes
#                   each passed file
#                   
# Parameters:
#   [1] SPACE-SEPARATED LIST OF FILES
# Return:
#   [stdout]
#       None
#   [else] 
#       Deletes each passed file
# Author: Eng. Hazem Anwer
# Github: https://github.com/hazemanwer2000
# 
#############################################################

import sys
import os

# Append to file
for i in range(1, len(sys.argv)):
    if os.path.exists(sys.argv[i]):
        os.remove(sys.argv[i])