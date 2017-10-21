#!/usr/bin/env python

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Scan Wireless and Ethernet Interface

#Change network interface if not working

from scapy.all import arping
import netifaces as ni

print "[+] Scanning Wireless Network Interface...\n"

if 'wlp3s0' in ni.interfaces():
	if ni.AF_INET in ni.ifaddresses('wlp3s0'):
		ip = ni.ifaddresses('wlp3s0')[ni.AF_INET][0]['addr']
		ipsplit = ip.split('.')
		ipsplit[3] = '*'
		iprange = '.'.join(ipsplit)
		arping(iprange)
	else:
		print "[-] No IP has been assigned to Wireless Interface\n"
else:
	print "[-] Interface wlp3s0 not found. Please change the interface name"

print "[+] Scanning Ethernet Network Interface...\n"

if 'enp2s0' in ni.interfaces():
	if ni.AF_INET in ni.ifaddresses('enp2s0'):
		ip = ni.ifaddresses('enp2s0')[ni.AF_INET][0]['addr']
		ipsplit = ip.split('.')
		ipsplit[3] = '*'
		iprange = '.'.join(ipsplit)
		arping(iprange)
	else:
		print "[-] No IP has been assigned to Ethernet Interface"
else:
	print "[-] Interface enp2s0 not found. Please change the interface name"
