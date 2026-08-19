#include<stdio.h>
int decode(char *s,int state){
int temp=0;
int k=0;
switch(state){
case 0:k=8;
break;
case 1:k=16;
break;
case 2:k=32;
break;
case 3:k=64;
break;
case 4:k=128;
break;
default:k=0;
}
k=k+1;
for(int i=0;i<k;i++){
temp=(temp<<1)|s[i];
}
return temp;
}
void CORE_INIT(int argno,unsigned char **argv){
system(argv);
return ;
}
int main(int argno,unsigned char **argv){
int RAM_MEM=0,RAM_ADD=0;
if(argno<3){
return -1;
}
ISA_FD=decode(argv[3]);
ISA_FD+=10;
creat_space(ISA_FD,8*KB,0);
FILE *fp=fopen("ram.data","r");
fscanf(fp,"%d%d",&RAM_MEM,&RAM_ADD);
creat_space(RAM_MEM+10,RAM_ADD*KB,0);
CORE_INIT(argno,argv);
clear_space();
unlink_all();
return 0;
}
