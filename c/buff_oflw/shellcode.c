/*Quick Shellcode test*/

#include <stdio.h>
#include <string.h>

unsigned char code[] = \
"Insert SHELLCODE Here";

main() {
	printf("Shellcode Length: %d\n", strlen(code));
	int (*ret)() = (int(*)())code;
	ret();
}
