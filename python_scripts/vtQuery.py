#!/usr/bin/env python

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Scans a given input file or a single hash, scans it on virustotal and writes the hit count in a output file

import requests
import argparse
import os
import time

def filecheck(filepath):
	try:
		if os.path.isfile(filepath):
			return filepath
		else:
			print "There is no file at:" + filepath
			exit()
	except Exception, e:
			print e

def main():
	parser = argparse.ArgumentParser(description="[+] This tool queries hashes against Virus Total database.")
	parser.add_argument('-i', '--input', type=filecheck, required=False, help='Enter the full path of input file to be scanned ')
	parser.add_argument('-o', '--output', required=True, help='Enter the full path of the output file ')
	parser.add_argument('-H', '--hash', required=False, help='Insert single hash to be scanned')
	parser.add_argument('-k', '--key', required=True, help='Enter the VirusTotal API key')
	args = parser.parse_args()

	#Run for a single hash + key
	if args.hash and args.key:
		file = open(args.output,'w+')
		file.write('Below is the identified malicious file.\n\n')
		file.close()
		VT_Request(args.key, args.hash.rstrip(), args.output)
	#Run for an input file + key
	elif args.input and args.key:
		file = open(args.output,'w+')
		file.write('Below are the identified malicious files.\n\n')
		file.close()
		with open(args.input) as o:
			for line in o.readlines():
				VT_Request(args.key, line.rstrip(), args.output)
				time.sleep(15)

def VT_Request(key, hash, output):
	params = {'apikey': key, 'resource': hash}
	url = requests.get('https://www.virustotal.com/vtapi/v2/file/report', params=params)
	json_response = url.json()
	#print json_response
	response = int(json_response.get('response_code'))
	if response == 0:
		print hash + ' is not in Virus Total'
		file = open(output,'a')
		file.write(hash + ' is not in Virus Total')
		file.write('\n')
		file.close()
	elif response == 1:
		positives = int(json_response.get('positives'))
		if positives == 0:
			print hash + ' is not malicious'
			file = open(output,'a')
			file.write(hash + ' is not malicious')
			file.write('\n')
			file.close()
		else:
			print hash + ' is malicious'
			file = open(output,'a')
			file.write(hash + ' is malicious. Hit Count:' + str(positives))
			file.write('\n')
			file.close()
	else:
		print hash + ' could not be searched. Please try again later.'
# execute the program
if __name__ == '__main__':
	main()
