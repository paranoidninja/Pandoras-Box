#!/bin/bash

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Script to find IP using Mac Address

#Change the Interface adapter and the mac id in particular areas for it to work.
#I am too lazy to modify them here

MYNETWORK=`ip route | grep wlan0 | cut -f1 -d" "`
echo -e "[+] Searching System with in $MYNETWORK\n[+] Running Primary Scan Method.."

IP=`python -c "from scapy.all import arping
import netifaces as ni

ni.ifaddresses('wlan0')
ip = ni.ifaddresses('wlan0')[ni.AF_INET][0]['addr']
ipsplit = ip.split('.')
ipsplit[3] = '*'
iprange = '.'.join(ipsplit)
arping(iprange)" | grep "<EnterYourMacIdHere>" | cut -f4 -d" "`


if [[ -z "$IP" ]]; then
        echo -e "[-] Primary Scan Failed..\n[+] Running Secondary Scan Method..."
        SCAN=""
        COUNTER=1
        while [[ "$SCAN" != *"<EnterYourMacIdHere>"* ]];
        do
                echo "[!] Running loop scans till the System is found. Running counter: $COUNTER"
                SCAN=`nmap -sP $MYNETWORK | grep -i "<EnterYourMacIdHere>" -B 2`
                COUNTER=`expr $COUNTER + 1`
        done
        IP=`echo $SCAN | cut -f5 -d' '`
        echo "Found System with IP: $IP"
        echo "Connecting to System now..."
        ssh user@$IP

else
        echo "Found System with IP: $IP"
        echo "Connecting to System now..."
        ssh user@$IP
fi
