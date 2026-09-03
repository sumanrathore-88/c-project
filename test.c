#include<stdio.h>
int main(){
    char str[20];
    int i,letter=0,digits=0;
    
    printf("enter any name");
    scanf(" %[^\n]",&str);
    for(i=0;str[i]!'\0';i++){
        if(str[i]>='0' && str[i]<='9'){
            digits++;
        }
        else if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z')){
            letter++;
        }
    }
    printf("number of letters: %d\n",letters);
    printf("number of letters: %d\n",digits);
    return 0;
}
