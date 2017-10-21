#!/usr/bin/env python

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Unix Hash password cracking tool

import crypt
import optparse
from datetime import datetime
from threading import Thread
def main():
    parser = optparse.OptionParser("usage : -p <passwordfile> -w <wordlist>")
    parser.add_option('-p', dest='pname', type='string', help='specify password file')
    parser.add_option('-w', dest='wname', type='string', help='specify wordlist file')
    (options, args) = parser.parse_args()
    if (options.pname == None) | (options.wname == None):
        print parser.usage
        exit(0)
    else:
        pname = options.pname
        wname = options.wname
    startTime = datetime.now()
    print '\nScript Start Time: ' +str(startTime) + '\n'
    passFile = open(pname)
    for line in passFile.readlines():                   #reading all lines in the file
        if ":" in line:
            user = line.split(':')[0]                   #Split the text in passwd.txt & save it to var user
            haSh = line.split('$')[1]                   #saving the hash $6$
            salt = line.split('$')[2]                   #saving the hash between 2nd and 3rd $ sign
            cryptPass = line.split(':')[1].strip('\n')
            print 'Cracking password for user: '+user
            t = Thread(target=dictPass, args=(cryptPass,haSh,user,salt,startTime,wname))
            t.start()

def dictPass(cryptPass,haSh,user,salt,startTime,wname):
    dictFile = open(wname,'r')
    for word in dictFile.readlines():
        word = word.strip('\n')                         #Strip new lines
        cryptWord = crypt.crypt(word,'$'+haSh+'$' + salt)   #Creating a new hash out of dictionary file
        if (cryptWord == cryptPass):
            print "[+]PASSWORD FOUND: "+ word + '\n'
            stopTime = datetime.now()
            print 'Script Stop Time: ' +str(stopTime)
            print 'Total Time Used to Crack the Password ' +str(stopTime - startTime)
            return
    print "[+]Password Not Found"
    return

if __name__ == "__main__":
    main()
