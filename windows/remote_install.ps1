##Author : Paranoid Ninja
##Email  : paranoidninja@protonmail.com
##Descr  : Simple Powershell Script to deploy any tool remotely via winrm. Change the SourceFolder and add all computer names in the CompName Variable text file/path

$SourceFolder = "\\VBOXSVR\shared_box\psexec.exe\"
$CompName = Get-Content "C:\Users\Administrator\Desktop\machine.txt"

foreach ($computer in $CompName)
{
    $DestinationFolder = "\\$CompName\C$\sysmon"

    if(!(Test-Path -path $DestinationFolder))
    {
        New-Item $DestinationFolder -Type Directory
    }

    robocopy $SourceFolder $DestinationFolder
    Invoke-Command -ComputerName $computer -ScriptBlock { & cmd /c "C:\psexec.exe"} #use whatever tool you want
}
