#include<stdio.h>
#include<ctype.h>
#include<string.h>

void  getkeymatrix( char *key, int keymatrix[3][3]){
    int k =0;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            keymatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }

}

void encrypted( int ciphermatrix[][1], int keymatirx[3][3], int messagematrix[][1]){
    int i,j,k;
    for(int i=0; i<3; i++){
        for(int j=0; j<1; j++){
            ciphermatrix[i][j] = 0;
            for(int k =0; k<3; k++){
                ciphermatrix[i][j] += keymatirx[i][k] * messagematrix [k][j];
            }
            ciphermatrix[i][j] = ciphermatrix[i][j] % 26;
        }
    }
    
}

void hillcipher(char *message, char *key){
    int keymatrix[3][3];
    getkeymatrix(key,keymatrix);

    int messagematrix[3][1];
    for(int i=0; i<3; i++){
        messagematrix[i][0] = message[i] % 65;
    }

    int ciphermatrix[3][1];
    encrypted(ciphermatrix,keymatrix,messagematrix);

    char cipher[4];
    cipher[3] = '\0';

    for(int i =0; i<3; i++){
        cipher[i] = ciphermatrix[i][0] + 65;
    }

    printf("your cipher text: %s", cipher);

    
}


int main(){

    char message[]="ACT";
    char key[] = "GYBNQKURP";
    hillcipher(message,key);

    return 0;
}
