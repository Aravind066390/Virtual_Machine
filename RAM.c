#include<stdio.h>
#include<unistd.h>
#include"memory.h"
#include"downloads.h"
int sys_tech=0,size_of_ram,cur_reg;
int CORE=0,SIZEOFCORE;
int wr_reg,rd_reg;
char var[259];
int decode(char *,int );
void open_fd(char *arg,char *arg1){
strcpy(var,"fd_");
strcat(var,arg);
FILE *fpt=fopen(var,"w");
fprintf(fpt,"%s",arg1);
fclose(fpt);
}
void close_fd(){
remove(var);
}
void structure(char *s){
char temp_reg[33];
int i=0;
while(s[i]!='\0'){
if(strlen(s+i)<3){
break;
}
if(!strncmp(s,"RDR",3)){
strncpy(temp_reg,s,3);
rd_reg=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"WRR",3)){
strncpy(temp_reg,s,3);
wr_reg=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"CUR",3)){
strncpy(temp_reg,s,3);
cur_reg=decode(temp_reg,sys_tech);
}
i++;
}
}
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
for(int i=0;i<k;i++){
temp=(temp<<1)|s[i];
}
return temp;
}
void imp(char **argv,int argno){
char str[1000];
FILE *fpfp=fopen("CORE_NO.data","r");
if(fpfp==NULL){
perror("UNKNOW FILE ACCESS INITIATED.");
}
while(strncmp(str,argv[0],strlen(argv[0]))){
if(fscanf(fpfp,"%s",str)!=EOF){
if(!strncmp(str,argv[0],strlen(argv[0]))){
fscanf(fpfp,"%d",&SIZEOFCORE);
}
}else{
break;
}
}
fclose(fpfp);
}
void work(char **argv,int argno){
int i=1;
char time_temp[1000];
int cer=0;
while(i<argno){
if(1||(cer=decode(argv[i],sys_tech))){
if(cer==rd_reg){
strcpy(time_temp,"temp_cpu_");
strcat(time_temp,argv[0]);
FILE *fpf=fopen(time_temp,"r");
int k=0;
char chare;
char *ptr_ram=(char *)find_space_ptr(decode(argv[0],sys_tech));
if(fpf==NULL){
perror("Entered file doesnt exist failed to create requested file.");
exit(0);
}
k=decode(argv[i+1],sys_tech);
i=i+1;
while(fscanf(fpf,"%c",&chare)!=EOF){
ptr_ram[k++]=chare;
}
fclose(fpf);
}
else if(cer==wr_reg){
if(fork()){
char sized_str[1000*KB],gbs[10];
char *ptr_ram=(char *)find_space_ptr(decode(argv[0],sys_tech));
strcpy(sized_str,"./CPU ");
sprintf(gbs,"%d",(KB+2));///MIGHT HAVE ERRROR IT SENDS CPU INSTRUCTIONS.
strcat(sized_str,gbs);
strcat(sized_str," ");
strcat(sized_str,argv[1]);
strcat(sized_str," ");
strncat(sized_str,ptr_ram,KB);
execl(sized_str,"ls","-l",NULL);
}else{
char strkl[200];
strcpy(strkl,"2temp_core_count");
strcat(strkl,argv[0]);
FILE *FP=fopen(strkl,"r");
fscanf(FP,"%d",&CORE);
fclose(FP);
CORE+=1;
FP=fopen(strkl,"w");
fprintf(FP,"%d",CORE);
fclose(FP);
}
}
else if(cer==cur_reg){
char *ptr=(char *)find_space_ptr(decode(argv[0],sys_tech));
ptr[i]=i;///useless
}
else{
i=i+1;
}
}
}
}
int main(int argno,char **argv){
if(argno<1){
perror("TOO FEW ARGUMENTS FOUND BY RAM\n");
return -1;
}
open_fd(argv[0],argv[1]);
FILE *fps=fopen("SYS_ARCH.data","r");
if(fps==NULL){
perror("SYSTEM OF NULL YTE ARCHITECTURE FOUND.\nNO THING AS NULL BYTE EXISTS.\nPLEASE INITIALIZE THE DATA.");
return -1;
}
fscanf(fps,"%d",&sys_tech);
fclose(fps);
creat_space(decode(argv[1],sys_tech)+10,8*KB,1);
structure((char *)find_space_ptr(decode(argv[1],sys_tech)+10));
char strs[1000];
strcpy(strs,"RAM_");
strcat(strs,argv[0]);
fps=fopen(strs,"r");
if(fps==NULL){
perror("Size of this particular ram is not defined.\n");
return -1;
}
fscanf(fps,"%d",&size_of_ram);
fclose(fps);
int a=decode(argv[0],sys_tech);
creat_space(a+10,size_of_ram*KB,1);
///CREATE THE SPACE NOT OPEN IT.
imp(argv,argno);
work(argv,argno);
clear_space();
close_fd();
}
///argv[0] stores the location of RAM-10
///argv[1] stores the location of ISA-10
