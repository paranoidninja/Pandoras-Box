##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Run file test.bat as admin. This script is an alternative to sudo, but for Windows

$secpasswd = ConvertTo-SecureString "<EnterPasswordHere>" -AsPlainText -Force
$mycreds = New-Object System.Management.Automation.PSCredential ("<EnterUsernameHere>",$secpasswd)
$computer = "<EnterHostnameHere>"
[System.Diagnostics.Process]::Start("C:\Users\%USERNAME%\AppData\local\temp\test.bat","",$mycreds.Username, $mycreds.Password, $computer)

