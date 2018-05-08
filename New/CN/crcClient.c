#include<stdio.h>
#include<string.h>
#define MAX 100
#define THREE 3
void substring(char s[], char sub[], int p, int l) {
   int c = 0; 
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}
void main(){
    char msg[MAX],crc[MAX],enmsg[MAX],l3c[THREE];
    int i = 0, j = 0;
    strcpy(enmsg,"");
    printf("Enter The Message : ");
    scanf("%s",msg);
    printf("Enter The CRC Generator : ");
    scanf("%s",crc);
    int mlen = strlen(msg);
    int clen = strlen(crc);
    strcat(enmsg,msg);
    for(i = 1;i < clen ; i++){
        strcat(enmsg,"0");
        //printf("\n%d%s",clen,enmsg);
    }
    //printf("%s : %d",enmsg,(int)strlen(enmsg));
    for(i = 0;i <= (strlen(enmsg) - clen);){
        for(j = 0;j < clen ; j++){
            //printf("\n%d Upar : %c %c",i+j,enmsg[i+j],crc[j]);
            enmsg[i+j] = (enmsg[i+j] == crc[j])?'0':'1';
            //printf(" Nche : %c",enmsg[i+j]);
        }
        for(;i<strlen(enmsg) && enmsg[i] != '1';i++);
    }
    printf("%s",enmsg);
    substring(enmsg,l3c,strlen(enmsg)-2,3);
    printf("\n%s",l3c);
}