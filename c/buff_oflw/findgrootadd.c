/*Get GROOT variable's address. Use this address to insert into shellcode */

#include <unistd.h>

int main(void)
{
    printf("GROOT address: 0x%lx\n", getenv("GROOT"));
    return 0;
}
