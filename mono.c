#include <stdio.h>
#include<string.h>
#include<ctype.h>


void cipher(char plaintext[], char key[], char ciphertext[] ){
    int i;
    for(i=0; plaintext[i] !='\0'; i++){
        
        if(isalpha(plaintext[i])){
                if(islower(plaintext[i])){
                    ciphertext[i] = key[plaintext[i]-'a'];
                }
                else{
                    ciphertext[i] = key[plaintext[i]-'A'];
                }
        }
        else{
            ciphertext[i]=plaintext[i];
        }        
    }
    ciphertext[i] = '\0';
}

void decryption( char cipertext[], char key[] , char decrypted[]){
    int i;
    char *pos;
    for(i=0; cipertext[i] !='\0'; i++){

        if(isalpha(cipertext[i])){        
                if(islower(cipertext[i])){
                    pos = strchr(key, cipertext[i]);
                    decrypted[i] = 'a' + (pos - key);
                }
                else{
                    pos = strchr(key, cipertext[i]);
                    decrypted[i] = 'A' + (pos - key);
                }
        }
        else{
            decrypted[i]=cipertext[i];
        }        
    }
    decrypted[i] = '\0';
}

int main(){

        char plaintext[100];
        char ciphertext[100];
        char decrypted[100];
        char key[27];

        printf("enter the text: ");
        fgets(plaintext,100,stdin);

        printf("enter the key: ");
        fgets(key,27,stdin);

        cipher(plaintext,key,ciphertext);
        printf("your ciphertext : %s",ciphertext);

        decryption(ciphertext, key, decrypted );
        printf("your decrypted text : %s", decrypted);

        
        
}
