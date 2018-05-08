#include<stdio.h>
#include<string.h>
void main(){
    char x[] = "1";
    if(strpbrk("101",x) == NULL){
        printf("Hell Yeah");
    }else{
        printf("%s",strpbrk("101",x));
    }
}