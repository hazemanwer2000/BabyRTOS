
# Execute python script 'gdb.py', related to the PyCortexM GDB plugin
source ~/.pyscripts/pycortexm/gdb.py

# Load SVD file
svd_load ./.gdb/stm32f401.svd

# Read 'main.elf' file symbols
file main.elf

# Connect to OpenOCD Server (Default port is 3333)
target extended-remote :3333

# Start '.elf' and break at 'main'
start

# 'filey' command
define filey
  file main.elf
  directory
  load
  start
end