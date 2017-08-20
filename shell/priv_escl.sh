#!/bin/bash

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : This Script can be used to find System flaws during privelege escalation

#Get Timestamp to create time based Logs
TIMESTAMP=`date +%d-%m-%y_%I-%M`

#Variables to store the data

OS_INFO="OS_INFO_$TIMESTAMP"
KERNEL_INFO="KERNEL_INFO_$TIMESTAMP"
ENVIRONMENT_VARIABLES="ENVIRONMENT_VARIABLES_$TIMESTAMP"
PRINTER_INFO="PRINTER_INFO_$TIMESTAMP"
PROCESS_INFO="PROCESS_INFO_$TIMESTAMP"
APPS_INSTALLED="APPS_INSTALLED_$TIMESTAMP"
CRON_JOBS="CRON_JOBS_$TIMESTAMP"
CONNECTION_INFO="CONNECTION_INFO_$TIMESTAMP"
PASSUDO_INFO="PASSUDO_INFO_$TIMESTAMP"
SSH_INFO="SSH_INFO_$TIMESTAMP"
LOG_INFO="LOG_INFO_$TIMESTAMP"
PARTITION_INFO="PARTITION_INFO_$TIMESTAMP"
WRITEXEC_INFO="WRITEXEC_INFO_$TIMESTAMP"

echo -e "++++++++++ Collecting OS release Info ++++++++++\n"
cat /etc/*-release >> $OS_INFO

echo -e "\n++++++++++ Collecting Kernel Info ++++++++++\n"
cat /proc/version >> $KERNEL_INFO
echo -e "\n--------------------------------\n"
dmesg | grep Linux >> $KERNEL_INFO
echo -e "\n--------------------------------\n"
ls /boot | grep vmlinuz- >> $KERNEL_INFO

echo -e "\n++++++++++ Collecting Environment Variables ++++++++++\n"
echo -e "\n---+++--- PROFILE DETAILS ---+++---\n" | tee -a $ENVIRONMENT_VARIABLES
cat /etc/profile >> $ENVIRONMENT_VARIABLES
echo -e "\n--------------------------------\n"
echo -e "\n---+++--- BASH INFO ---+++---\n" | tee -a $ENVIRONMENT_VARIABLES
cat ~/.bash* >> $ENVIRONMENT_VARIABLES
echo -e "\n---+++--- ENV DETAILS ---+++---\n" | tee -a $ENVIRONMENT_VARIABLES
env >> $ENVIRONMENT_VARIABLES

echo -e "\n++++++++++ Collecting Printer Info ++++++++++\n"
lpstat -t >> $PRINTER_INFO

echo -e "\n++++++++++ Collecting Process Info ++++++++++\n"
ps aux >> $PROCESS_INFO
echo -e "\n--------------------------------\n"
cat /etc/services >> $PROCESS_INFO
echo -e "\n--------------------------------\n"
ps -ef >> $PROCESS_INFO

echo -e "\n++++++++++ Reading Cron Jobs ++++++++++\n"
crontab -l >> $CRON_JOBS
echo -e "\n--------------------------------\n"
ls -alh /var/spool/cron >> $CRON_JOBS
echo -e "\n--------------------------------\n"
ls -al /etc/ | grep cron >> $CRON_JOBS
echo -e "\n--------------------------------\n"
ls -al /etc/cron* >> $CRON_JOBS
echo -e "\n--------------------------------\n"
cat /etc/crontab >> $CRON_JOBS
echo -e "\n--------------------------------\n"
cat /etc/anacrontab >> $CRON_JOBS

echo -e "\n++++++++++ Collecting Netstat Info ++++++++++\n"
netstat -antup >> $CONNECTION_INFO
echo -e "\n--------------------------------\n"
netstat -antpx >> $CONNECTION_INFO
echo -e "\n--------------------------------\n"
netstat -tulpn >> $CONNECTION_INFO

echo -e "\n---+++--- PASSWD INFO ---+++---\n" | tee -a $PASSUDO_INFO
cat /etc/passwd >> $PASSUDO_INFO

echo -e "\n++++++++++ Collecting SSH Info ++++++++++\n"
echo -e "\n---+++--- AUTHORIZED KEYS ---+++---\n" | tee -a $SSH_INFO
cat ~/.ssh/authorized_keys >> $SSH_INFO
echo -e "\n---+++--- IDENTITY PUBLIC FILES ---+++---\n" | tee -a $SSH_INFO
cat ~/.ssh/identity.pub >> $SSH_INFO
echo -e "\n---+++--- IDENTITY PRIVATE FILES ---+++---\n" | tee -a $SSH_INFO
cat ~/.ssh/identity >> $SSH_INFO
echo -e "\n---+++--- PUBLIC RSA KEY ---+++---\n" | tee -a $SSH_INFO
cat ~/.ssh/id_rsa.pub >> $SSH_INFO
echo -e "\n---+++--- PRIVATE RSA KEY ---+++---\n" | tee -a $SSH_INFO
cat ~/.ssh/id_rsa >> $SSH_INFO
echo -e "\n---+++--- PUBLIC DSA KEY ---+++---\n" | tee -a $SSH_INFO
cat ~/.ssh/id_dsa.pub >> $SSH_INFO
echo -e "\n---+++--- PRIVATE DSA KEY ---+++---\n" | tee -a $SSH_INFO
cat ~/.ssh/id_dsa >> $SSH_INFO
echo -e "\n---+++--- SSH CONFIG ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/ssh_config >> $SSH_INFO
echo -e "\n---+++--- SSHD CONFIG ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/sshd_config >> $SSH_INFO
echo -e "\n---+++--- SSH HOST PUBLIC DSA KEY ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/ssh_host_dsa_key.pub >> $SSH_INFO
echo -e "\n---+++--- SSH HOST PRIVATE DSA KEY ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/ssh_host_dsa_key >> $SSH_INFO
echo -e "\n---+++--- SSH HOST PUBLIC RSA KEY ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/ssh_host_rsa_key.pub >> $SSH_INFO
echo -e "\n---+++--- SSH HOST PRIVATE RSA KEY ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/ssh_host_rsa_key >> $SSH_INFO
echo -e "\n---+++--- SSH HOST PUBLIC KEY ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/ssh_host_key.pub >> $SSH_INFO
echo -e "\n---+++--- SSH HOST PRIVATE KEY ---+++---\n" | tee -a $SSH_INFO
cat /etc/ssh/ssh_host_key >> $SSH_INFO

echo -e "\n++++++++++ Reading Partitions ++++++++++\n"
echo -e "\n---+++--- MOUNTED PARTITIONS ---+++---\n" | tee -a $PARTITION_INFO
df -h >> $PARTITION_INFO
echo -e "\n---+++--- ALL PARTITIONS ---+++---\n" | tee -a $PARTITION_INFO
cat /etc/fstab >> $PARTITION_INFO

echo -e "\n++++++++++ Reading All Write and Execute Locations ++++++++++\n"
echo -e "\n---+++--- WRITABLE Directories ---+++---\n" | tee -a $WRITEXEC_INFO
find / -writable -type d 2>/dev/null >> $WRITEXEC_INFO
find / -perm -222 -type d 2>/dev/null >> $WRITEXEC_INFO
find / -perm -o w -type d 2>/dev/null >> $WRITEXEC_INFO
find / -perm -777 -type d 2>/dev/null >> $WRITEXEC_INFO
find / -perm -4000 -type d 2>/dev/null >> $WRITEXEC_INFO
echo -e "\n---+++--- WRITABLE FILES ---+++---\n" | tee -a $WRITEXEC_INFO
find / -perm -2 ! -type f -ls 2>/dev/null >> $WRITEXEC_INFO
find / -perm -777 -type f 2>/dev/null >> $WRITEXEC_INFO
find / -perm -4000 -type f 2>/dev/null >> $WRITEXEC_INFO
find / perm /u=s -user `whoami` 2>/dev/null >> $WRITEXEC_INFO
find / perm /u=s -type d -user `whoami` 2>/dev/null >> $WRITEXEC_INFO
echo -e "\n---+++--- EXECUTABLE LOCATIONS ---+++---\n" | tee -a $WRITEXEC_INFO
find / -perm -o x -type d 2>/dev/null >> $WRITEXEC_INFO
find / \( -perm -o w -perm -o x \) -type d 2>/dev/null >> $WRITEXEC_INFO

echo "!! DONE !!"
