#include<stdio.h>
#define KB 1024
#include<unistd.h>
#include<string.h>
#include"memory.h"
#include"time.h"
int rd_reg,wr_reg,ap_reg,rm_reg,sys_reg;
int ds_reg;///This is to destroy the complete SSD .
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
void search(char *s){
int i=0;
while(s[i]!='\0'){
if(!strncmp("FRD",s+i,3)){
s=s+i;
rd_reg=decode(s,sys_reg);
}
if(!strncmp("FWR",s+i,3)){
s=s+i;
wr_reg=decode(s,sys_reg);
}
if(!strncmp("FRM",s+i,3)){
s=s+i;
rm_reg=decode(s,sys_reg);
}
if(!strncmp("DST",s+i,3)){
s=s+i;
ds_reg=decode(s,sys_reg);
}
}
i=i+1;
return ;
}
void process(char **argv,int argno){
int i=2;
while(i<argno){
int val=decode(argv[i],sys_reg);
if(1){
if(ds_reg==val){
char string[1000];
strcpy(string,"rm -rf ");
strcat(string,argv[1]);
system(string);
}
else if(val==rm_reg){///INCOMPLETE PORTION.
FILE *fpg=fopen(argv[i+1],"r");
if(fpg==NULL){
perror("UNKNOW FILE ENTERED\n");
exit(0);
}
fclose(fpg);
remove(argv[i+1]);
i+=1;
}
else if(val==rd_reg){
FILE *fpg=fopen(argv[i+1],"r");
if(fpg==NULL){
perror("UNKNOW FILE ENTERED\n");
exit(0);
}
char strm[2000];
int j=0;
i+=1;
while(strlen(argv[i+1])!=j){///    DOUBTFUL ABOUT THIS SECTION OF CODE DONT KNOW WHAT IT DOES.
strm[j]=argv[i+1][j];
if(strm[j]=='/'){
strm[j]='+';
}
j++;
}
i+=1;
FILE *tmp=fopen(strm,"w");
char chs;
while(fscanf(fpg,"%c",&chs)!=EOF){
fprintf(tmp,"%c",chs);
}
fclose(tmp);
fclose(fpg);
}
else if(val==wr_reg){
FILE *fpg=fopen(argv[i+1],"w");
if(fpg==NULL){
perror("UNKNOW FILE ENTERED\n");
exit(0);
}
FILE *temp=fopen("TEMP.data","r");
if(temp==NULL){
perror("UNKNOW FILE ENTERED\n");
exit(0);
}
char chr;
while(fscanf(temp,"%c",&chr)!=EOF){
fprintf(fpg,"%c",chr);
}
fclose(temp);
fclose(fpg);
i+=1;
}
else{
i=i+1;
}
}
}
return ;
}
int main(int argno,char **argv){
if(argno<=1){
return -1;
}
FILE *fps=fopen("SYS_ARCH.data","r");
if(fps==NULL){
perror("NOT FOUND INITIALIZATION\nPLEASE INITIALIZE NULL ARCHITERCTURE FOUND \n");
return -1;
}
fscanf(fps,"%d",&sys_reg);
fclose(fps);
char string[100];
int ISA_FD=decode(argv[0],sys_reg);
if(ISA_FD<0){
strcpy(string,"mkdir ");
strcat((string),argv[1]);
system(string);
return 0;
}
else{
creat_space(ISA_FD,8*KB,1);
char *ptr=(char *)find_space_ptr(ISA_FD);
search(ptr);
process(argv,argno);
clear_space();
}
return 0;
}
///ARGV 0 IS FOR ISA_FD
///ARGV 1 IS FOR THE SSD ACTUAL ADDRESS IN LINUX SYSTEM OR NAME OF THE SSD PREVIOUSLY PROVIDED.
