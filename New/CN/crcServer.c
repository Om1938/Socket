#include<stdio.h>
#include<string.h>
#define MAX 100
void substring(char s[], char sub[], int p, int l) {
   int c = 0; 
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}
void main(){
    char crc[MAX],enmsg[MAX],l3c[3];
    int i,j;
    printf("Enter The Message : ");
    scanf("%s",enmsg);
    printf("Enter The CRC Generator : ");
    scanf("%s",crc);
    int clen = strlen(crc);
    for(i = 0;i <= (strlen(enmsg) - clen);){
        for(j = 0;j < clen ; j++){
            //printf("\n%d Upar : %c %c",i+j,enmsg[i+j],crc[j]);
            enmsg[i+j] = (enmsg[i+j] == crc[j])?'0':'1';
            //printf(" Nche : %c",enmsg[i+j]);
        }
        for(;i<strlen(enmsg) && enmsg[i] != '1';i++);
    }
    substring(enmsg,l3c,strlen(enmsg)-2,3);
     if(strpbrk(l3c,"1") == NULL){
         printf("No Error");
     }else
        printf("Error Hai");
}