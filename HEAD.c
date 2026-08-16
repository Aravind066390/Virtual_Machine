#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include"memory.h"
char *to_up(char *s){
int i=0;
while(s[i]!='\0'){
if(s[i]>=97&&s[i]<(97+32)){
s[i]-=32;
}
i++;
}
return s;
}
int main(){
char cur_str[103*1024];
strcpy(cur_str,"NULL");
while(strcmp("EXIT",cur_str)){
printf("\nENTER>");
scanf("%s",cur_str);
strcpy(cur_str,to_up(cur_str));
if(!strcmp("EXIT",cur_str)){
printf("\nexiting");
for(int i=0;i<5;i++){
printf(".");
fflush(stdout);
sleep(1);
}
return 0;
}else if(!strcmp(cur_str,"RAM")){
printf("Enter the values of RAM ISA:-");
int i=0;
return 0;
while(cur_str[i]!=27){
scanf("%c",&cur_str[i]);
i++;
}
char name[1024];
printf("\nEnter the value of RAM_NO_FD:-");
scanf("%s",name);
}else if(!strcmp("ISA_INIT",cur_str)){
int i=0;
printf("\nEnter>\n");
while(1){
scanf("%c",&cur_str[i]);
if(i>0&&cur_str[i]=='['&&cur_str[i-1]=='^'){
break;
}
i++;
}
FILE *fp=fopen("SYS_ARCH.data","w");
fprintf(fp,"%s",cur_str);
fclose(fp);
}
else if(!strcmp("VIEW",cur_str)){
scanf("%s",cur_str);
strcpy(cur_str,to_up(cur_str));
if(!strcmp(cur_str,"ISA")){
FILE *fp=fopen("SYS_ARCH.data","r");
int i=0;
while(1){
fscanf(fp,"%c",&cur_str[i]);
printf("%c",cur_str[i]);
if(i>0&&cur_str[i]=='['&&cur_str[i-1]=='^'){
break;
}
i++;
}
fclose(fp);
}
}
else if(!strcmp("RUN",cur_str)){
FILE *fp=fopen("Instructions","r");
}
else{
printf("\nError\n");
}
}
}
