//int(*ret)() ###declares a function pointer named ret; the function takes unspecified arguments and returns an integer.
//(int(*)())shellcode ###Converts the address of the shellcode array to a function pointer, which then allows you to call it and execute the shellcode.
//ret() ###Executes the function with the shellcode

#include <string.h>
#include <stdio.h>

unsigned char shellcode[] = "";

main() {
        printf("Shellcode length: %d\n", strlen(shellcode));
        int (*ret)() = (int(*)())shellcode;
        ret();
}
