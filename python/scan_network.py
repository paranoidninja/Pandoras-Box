#!/usr/bin/env python

from scapy.all import arping
import netifaces as ni

print "[+] Scanning Wireless Network Interface...\n"

if ni.AF_INET in ni.ifaddresses('wlp3s0'):
	ip = ni.ifaddresses('wlp3s0')[ni.AF_INET][0]['addr']
	ipsplit = ip.split('.')
	ipsplit[3] = '*'
	iprange = '.'.join(ipsplit)
	arping(iprange)
else:
	print "[-] No IP has been assigned to Wireless Interface\n"

print "[+] Scanning Ethernet Network Interface...\n"

if ni.AF_INET in ni.ifaddresses('enp2s0'):
	ip = ni.ifaddresses('enp2s0')[ni.AF_INET][0]['addr']
	ipsplit = ip.split('.')
	ipsplit[3] = '*'
	iprange = '.'.join(ipsplit)
	arping(iprange)
else:
	print "[-] No IP has been assigned to Ethernet Interface"
