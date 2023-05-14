#!/bin/python

import math

################ CREATE LIST

def map2index(n):
    for i in range(8):
        if ((1 << i) & n) != 0:
            return i
    return -1

lst = [-1]
for n in range(1, 256):
    #lst.append(f'{n:b}' + '=' + str(map2index(n)))
    lst.append(map2index(n))

    #print(f'{n:b}')
    #print(map2index(n))

################ PRINT LIST

def p(any):
    print(any, end='')

p('\n')
for i in range(256):
    p(str(lst[i]) + ', ')
    if ((i + 1) % 8) == 0:
        p('\n')
p('\n')