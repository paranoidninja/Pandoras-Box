#!/bin/bash

##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Linux/Unix Privilege Escalation Recon Script


SYSINFO() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING BASIC SYSTEM INFO...
    [-] Operating System:\n`tput sgr0;cat /etc/issue`
    `tput setaf 3`[-] Kernel:\n`tput sgr0;cat /proc/version`
    `tput setaf 3`[-] Hostname:\n`tput sgr0;hostname`"
}



NETWINFO() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING NETWORKING INFO...
    [-] NETINFO:\n`tput sgr0;/sbin/ifconfig -a`
    `tput setaf 3`[-] ROUTE:\n`tput sgr0;route`
    `tput setaf 3`[-] NETSTAT:\n`tput sgr0;netstat -autlnp`"
}


FILESYSINFO() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING FILESYSTEM INFO...
    [-] MOUNT POINTS:\n`tput sgr0;mount`
    `tput setaf 3`[-] FSTAB ENTRIES:\n`tput sgr0;cat /etc/fstab`"
}


CRONJOBS() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING CRONJOB INFO...
    [-] SCHEDULED CRON JOBS:\n`tput sgr0;ls -la /etc/cron* 2>/dev/null`
    `tput setaf 3`[-] WRITABLE CRON DIRECTORIES:\n`tput sgr0;ls -aRl /etc/cron* 2>/dev/null | awk '$1 ~ /w.$/' 2>/dev/null`"
}


USERENV() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING USER AND ENVIRONMENTAL VARIABLES...
    [-] WHOAMI:\n`tput sgr0;whoami`
    `tput setaf 3`[-] ID:\n`tput sgr0;id`
    `tput setaf 3`[-] ALLUSERS:\n`tput sgr0;cat /etc/passwd`
    `tput setaf 3`[-] SUPERUSERS:\n`tput sgr0;grep -v -E '^#' /etc/passwd | awk -F: '$3 == 0{print $1}'`
    `tput setaf 3`[-] HISTORY:\n`tput sgr0;ls -la ~/.*_history; ls -la /root/.*_history 2>/dev/null`
    `tput setaf 3`[-] ENVIRONMENTAL VARIABLES:\n`tput sgr0;env 2>/dev/null | grep -v 'LS_COLORS'`
    `tput setaf 3`[-] SUDOERS:[privileged]\n`tput sgr0;cat /etc/sudoers 2>/dev/null | grep -v '#' 2>/dev/null`
    `tput setaf 3`[-] LOGGED IN USERS:\n`tput sgr0;w 2>/dev/null`"

}


FILEDIRPERM() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING FILE AND DIRECTORY PERMISSIONS/CONTENTS...
    [-] WORLD WRITABLE DIRECTORIES USER/GROUP 'ROOT':\n`tput sgr0;find / \( -wholename '/home/homedir*' -prune \) -o \( -type d -perm -0002 \) -exec ls -ld '{}' ';' 2>/dev/null | grep root`
    `tput setaf 3`[-] WORLD WRITABLE DIRECTORIES FOR USERS OTHER THAN ROOT:\n`tput sgr0;find / \( -wholename '/home/homedir*' -prune \) -o \( -type d -perm -0002 \) -exec ls -ld '{}' ';' 2>/dev/null | grep -v root`
    `tput setaf 3`[-] WORLD WRITABLE FILES:\n`tput sgr0;find / \( -wholename '/home/homedir/*' -prune -o -wholename '/proc/*' -prune \) -o \( -type f -perm -0002 \) -exec ls -l '{}' ';' 2>/dev/null`
    `tput setaf 3`[-] SUID/SGID FILES AND DIRECTORIES:\n`tput sgr0;find / \( -perm -2000 -o -perm -4000 \) -exec ls -ld {} \; 2>/dev/null`
    `tput setaf 3`[-] CHECKING IF ROOT'S HOME DIRECTORY IS ACCESSIBLE:[privileged]\n`tput sgr0;ls -ahlR /root 2>/dev/null`
    `tput setaf 3`[-] LOG FILES CONTAINING KEYWORD 'PASSWORD':\n`tput sgr0;find /var/log -name '*.log' 2>/dev/null | xargs -l10 egrep 'pwd|password'`
    `tput setaf 3`[-] CONFIG FILES CONTAINING KEYWORD 'PASSWORD:\n`tput sgr0;find /etc -name '*.c*' 2>/dev/null | xargs -l10 egrep 'pwd|password' 2>/dev/null`
    `tput setaf 3`[-] READING SHADOW FILE:[privileged]\n`tput sgr0;cat /etc/shadow 2>/dev/null`"
}


PROCAPPS() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING RUNNING PROCESSES AND APPLICATIONS...
    [-] PROCESSES RUNNING AS OTHER USERS:\n`tput sgr0;ps aux | awk '{print $1,$2,$9,$10,$11}' | grep -v 'root'`
    `tput setaf 3`[-] PROCESSES RUNNING AS ROOT:\n`tput sgr0;ps aux | awk '{print $1,$2,$9,$10,$11}' | grep 'root'`"
}


OTHINFO() {
    echo -e "\n\n`tput setaf 3`[*] OTHER APPLICATION INFO...
    [-] SUDO VERSION:\n`tput sgr0;sudo -V | grep version 2>/dev/null`
    `tput setaf 3`[-] APACHE VERSION AND MODULES:\n`tput sgr0;apache2 -v; apache2ctl -M; httpd -v; apachectl -l 2>/dev/null`
    `tput setaf 3`[-] APACHE CONFIG FILE:\n`tput sgr0;cat /etc/apache2/apache2.conf 2>/dev/null`"
}

TOOLS() {
    echo -e "\n\n`tput setaf 3`[*] ENUMERATING INSTALLED TOOLS/COMPILERS FOR EXPLOIT BUILDING...
    [-] INSTALLED TOOLS:\n`tput sgr0;which awk perl python ruby gcc cc vi vim nmap find netcat nc wget tftp ftp 2>/dev/null`"
}


SYSINFO
NETWINFO
FILESYSINFO
CRONJOBS
USERENV
FILEDIRPERM
PROCAPPS
OTHINFO
TOOLS
