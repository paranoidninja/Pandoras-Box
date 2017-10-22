#!/usr/bin/env python

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Bad Char generator for Buffer Overflow

import sys
for x in range(1, 256):
	sys.stdout.write("\\x" + '{:02x}'.format(x))
print ("\n")

