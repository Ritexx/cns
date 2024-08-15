#include<stdio.h>
#include<ctype.h>

int main(){

    char text[100];
    int n;

    printf("enter the text: ");
    fgets(text,100,stdin);

    printf("enter the number: ");
    scanf("%d", &n);

    // encryption
     
    for( int i=0; text[i] != '\0'; i++){
        if(isalpha(text[i])){
            if(islower(text[i])){
                text[i] = (text[i] - 'a' + n )%26 + 'a';
            }
            else{
                text[i] = (text[i] - 'A' + n )%26 + 'A';
            }
        }
       
    }

    printf("your cipher text: %s", text);

    // decryption 

    for(int i=0; text[i] != '\0'; i++){
        if(isalpha(text[i])){
            if(islower(text[i])){
                text[i] = (text[i] - 'a' - n )%26 + 'a';
            }
            else{
                text[i] = (text[i] - 'A' - n )%26 + 'A';
            }
        }
    }
    
    printf("your decrypted text: %s", text);

}
