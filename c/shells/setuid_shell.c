int main(void){
       setresuid(0, 0, 0);
       system("/bin/bash");
}

