#include <stdio.h>
#include <string.h>
#define N strlen(gen)
 
char test[28],cs[28],gen[]="11000000000000101";
int a,e,c;
 
void xor(){
    for(c = 1;c < N; c++)
    cs[c] = (( cs[c] == gen[c])?'0':'1');
}
 
void crc(){
    for(e=0;e<N;e++)
        cs[e]=test[e];
    do{
        if(cs[0]=='1')
            xor();
        for(c=0;c<N-1;c++)
            cs[c]=cs[c+1];
        cs[c]=test[e++];
    }while(e<=a+N-1);
}
 
int main()
{
    printf("\nEnter Bit string: ");
    scanf("%s",test);
   
    printf("\nGenerator polynomial CRC-16 : %s",gen);

    a=strlen(test);
    for(e=a;e<a+N-1;e++)
        test[e]='0';
   
    printf("\nModified data is : %s",test);
   
    crc();
   // printf("\nChecksum is : %s",cs);
    for(e=a;e<a+N-1;e++)
        test[e]=cs[e-a];
   
    printf("\nFinal codeword is : %s",test);
    
  
}
