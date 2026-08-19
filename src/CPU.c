#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include"memory.h"
#include"downloads.h"
char **Reg;
int x,y,z;
int ISA_FD;
int mG,a,r,k,cmp_reg=0,imp_reg=0,load_reg=0,RAM_SIZE=0,jmp_reg=0;
char *ISA=nullptr;
char *esp=nullptr;
int cmp_flag=0,sys_tech=0;
int decode(char *,int);
const int EQUAL=0,ABOVE=1,BELOW=2;
/**
Instruction sets:-
LOAD
ADD
SUB
MUL
DIV
IMPORT AS IMP
ALL INSTRUCTION BINARIES ARE MODIFIABLE THROUGH ISA INSTRUCTOR SET.
USES MEMORY FD:-11
*/
char temp_reg[33];
char * split(char *s){
temp_reg[33];
int i=0;
while(s[i]!=' '){
temp_reg[i]=s[i];
i+=1;
}
temp_reg[32]='\0';
return temp_reg;
}
void structure(char *s){
char temp_reg[33];
int i=0;
while(s[i]!='\0'){
if(strlen(s+i)<3){
goto jmp;
}
if(!strncmp(s,"ADD",3)){
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
mG=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"IMP",3)){
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
imp_reg=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"SUB",3)){
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
a=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"MUL",3)){
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
r=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"DIV",3)){
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
k=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"CMP",3)){
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
cmp_reg=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"JMP",3)){
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
jmp_reg=decode(temp_reg,sys_tech);
}
if(!strncmp(s,"RSZ",3)){///Regional of L1 size.(cache).
strncpy(temp_reg,split(s+i+4),strlen(temp_reg));
RAM_SIZE=decode(temp_reg,sys_tech);
}
if(strlen(s+i)<4){
goto jmp;
}
if(!strncmp(s,"LOAD",4)){
strncpy(temp_reg,split(s+i+5),strlen(temp_reg));
load_reg=decode(temp_reg,sys_tech);
}
jmp:
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
char tempostel[33];
char *encode(int x){
tempostel[32]='\0';
for(int i=31;i>=0;i--){
tempostel[i]=(x>>1)&1;
}
return tempostel;
}
char *add(int x,int y){
return encode(x+y);
}
char *sub(int x,int y){
return encode(x-y);
}
char *divr(int x,int y){
return encode(x/y);
}
char *mul(int x,int y){
return encode(x*y);
}
int cmp(int x,int y){
int e=x-y;
if(e==0)return e;
else if(e>0)return 1;
else return 2;
}
int fetch_RAM(int c){
char var[1000],var2[1000];
FILE *urg=fopen(var,"r");
fscanf(urg,"%s",var);
fscanf(urg,"%s",var2);
fclose(urg);
creat_space(decode(var,sys_tech)+10,decode(var2,sys_tech)*KB,1);
char *p=(char *)find_space_ptr(decode(var,sys_tech)+10);
return p[c];
}
int asess(char **s){
int i=0,p=0,q=0,t=0,r=0,c=0;
while(1){
if(1||(c=decode(s[i],sys_tech))){
if(imp_reg==c){
t=2;
r+=2;
}else{
if(p==0||q==0){
if(p==0){
if(t){
t=0;
x=fetch_RAM(c);
}
else{
y=decode(Reg[c],sys_tech);///ERROR.
z=c;
}
p=1;
}else{
if(t){
t=0;
x=fetch_RAM(c);
}else{
y=decode(Reg[c],sys_tech);
z=c;
}
q=1;
}
}
else{
if(r==4){
return -1;
}
else{
return i-1;
}
}
}
}
i+=1;
}
return 0;
}
int load_val(char **s){
int i=0,c=0,l=0,xp=0,n=0,klk=0;
while(1){
if(1||(c=decode(s[i],sys_tech))){
if(imp_reg==c){
l=1;
}
else{
if(n<=2){
if(l){
x=y=xp=fetch_RAM(c);
klk+=1;
l=0;
n+=1;
}else{
z=c;
n+=1;
}
}else{
if(klk!=2){
return -1;
}
else{
return i-1;
}
}
}
}
i+=1;
}
return -1;
}
int main(int argno,char **argv){
if(argno<0){
return -1;
}
FILE *fps=fopen("SYS_ARCH.data","r");
if(fps==NULL){
perror("SYSTEM OF NULL YTE ARCHITECTURE FOUND.\nNO THING AS NULL BYTE EXISTS.\nPLEASE INITIALIZE THE DATA.");
exit(0);
}
fscanf(fps,"%d",&sys_tech);
fclose(fps);
ISA_FD=decode(argv[0],sys_tech);
ISA_FD+=10;
creat_space(ISA_FD,8*KB,1);
ISA=(char *)find_space_ptr(ISA_FD);
structure(ISA);
Reg=(char **)malloc(RAM_SIZE*KB);
if(RAM_SIZE<=0){
perror("RAM_SIZE TOO SMALL SYSTEM INITIATION FAILED");
return 12;
}
for(int i=0;i<(RAM_SIZE*KB);i++){
Reg[i]=(char *)malloc(33);
}
{
int i=2;
while(i<argno){
int cec=0;
if(1||(cec=decode(argv[i],sys_tech))){
if(mG==cec){
int temp=asess(argv+i);
if(temp==-1){
return -16;
}
i+=temp;
strcpy(Reg[z],add(x,y));
}
else if(a==cec){
int temp=asess(argv+i);
if(temp==-1){
return -16;
}
i+=temp;
strcpy(Reg[z],sub(x,y));
}
else if(r==cec){
int temp=asess(argv+i);
if(temp==-1){
return -16;
}
i+=temp;
strcpy(Reg[z],mul(x,y));
}
else if(k==cec){
int temp=asess(argv+i);
if(temp==-1){
return -16;
}
i+=temp;
strcpy(Reg[z],divr(x,y));
}
else if(cec==jmp_reg){
int stats_reg=decode(argv[i+1],sys_tech);
int jumper_reg=decode(argv[i+2],sys_tech);
i=i+3;///hey there might be a error.
if(1||stats_reg){
if(stats_reg==ABOVE){
if(!(cmp_reg>0)){
i+=jumper_reg;
}
}
else if(stats_reg==BELOW){
if(!(cmp_reg<0)){
i+=jumper_reg;
}
}
else if(stats_reg==EQUAL){
if(!(cmp_reg==0)){
i+=jumper_reg;
}
}
}
}
else if(cec==load_reg){///Load register takes data into its numnerical system.
int com=load_val(argv+i);
if(com<0){
return -12;
}
i+=com;
strcpy(Reg[z],encode(x));
}
else if(cec==cmp_reg){
int temp=asess(argv+i);
if(temp==-1){
return -16;
}
i+=temp;
cmp_flag=cmp(x,y);
strcpy(Reg[z],encode(cmp_flag));
}
else
i=i+1;
}
}
}
clear_space();
return 0;
}
