#!/usr/bin/python3

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Script to embed exe files to jpeg

import sys

if (len(sys.argv) != 3):
    print("Usage:\n ./" + sys.argv[0] + " <JpegFile> <ExecutableToEmbed>")
else:
    JpegFile = open(sys.argv[1], "rb").read()
    ExecFile = open(sys.argv[2], "rb").read()
    OutputFile = open("embeded.jpg", "wb")
    OutputFile.write(JpegFile)
    OutputFile.write(ExecFile)
    print ("[+] Written to embeded.jpg")
