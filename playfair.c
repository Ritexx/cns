#include <stdio.h>
#include <string.h>

typedef struct {
    int row;
    int col;
} position;

char mat[5][5]; 

void generateMatrix(char key[])
{
    
    int flag[26] = {0};
    int x = 0, y = 0;

   
    for(int i = 0; i < strlen(key); i++)
    {
        if(key[i] == 'j') key[i] = 'i'; // replace j with i

        if(flag[key[i]-'a'] == 0)
        {
            mat[x][y++] = key[i];
            flag[key[i]-'a'] = 1;
        }
        if(y == 5) x++, y = 0;
    }

    
    for(char ch = 'a'; ch <= 'z'; ch++)
    {
        if(ch == 'j') continue; // don't fill j since j was replaced by i

        if(flag[ch - 'a'] == 0)
        {
            mat[x][y++] = ch;
            flag[ch - 'a'] = 1 ;
        }
        if(y == 5) x++, y = 0;
    }
}


void formatMessage(char msg[])
{
    for(int i = 0; i < strlen(msg); i++)
    {
        if(msg[i] == 'j')  msg[i] = 'i';
    }

    for(int i = 1; i < strlen(msg); i += 2) //pairing two characters
    {
        if(msg[i-1] == msg[i])  msg[i] = 'x';
    }
    
    if(strlen(msg) % 2 != 0)  strcat(msg, "x");
}


position getPosition(char c)
{
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            if(c == mat[i][j])
            {
                position p = {i, j};
                return p;
            }
}

void encrypt(char message[])
{
    char ctext[1000] = "";
    for(int i = 0; i < strlen(message); i += 2)    // i is incremented by 2 inorder to check for pair values
    {
        position p1 = getPosition(message[i]);
        position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;
    
        if(x1 == x2) // same row
        {
            ctext[strlen(ctext)] = mat[x1][(y1 + 1) % 5];
            ctext[strlen(ctext)] = mat[x2][(y2 + 1) % 5];
        }
        else if(y1 == y2) // same column
        {
            ctext[strlen(ctext)] = mat[(x1 + 1) % 5][y1];
            ctext[strlen(ctext)] = mat[(x2 + 1) % 5][y2];
        }
        else
        {
            ctext[strlen(ctext)] = mat[x1][y2];
            ctext[strlen(ctext)] = mat[x2][y1];
        }
    }
    strcpy(message, ctext);
}

void decrypt(char message[])
{
    char ptext[1000] = "";
    for(int i = 0; i < strlen(message); i += 2) // i is incremented by 2 inorder to check for pair values
    {
        position p1 = getPosition(message[i]);
        position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;

        if(x1 == x2) // same row
        {
            ptext[strlen(ptext)] = mat[x1][y1 == 0 ? 4 : y1 - 1];
            ptext[strlen(ptext)] = mat[x2][y2 == 0 ? 4 : y2 - 1];
        }
        else if(y1 == y2) // same column
        {
            ptext[strlen(ptext)] = mat[x1 == 0 ? 4 : x1 - 1][y1];
            ptext[strlen(ptext)] = mat[x2 == 0 ? 4 : x2 - 1][y2];
        }
        else
        {
            ptext[strlen(ptext)] = mat[x1][y2];
            ptext[strlen(ptext)] = mat[x2][y1];
        }
    }
    strcpy(message, ptext);
}

int main()
{
    char plaintext[1000];
    printf("Enter message : ");
    scanf("%s", plaintext);

    int n; // number of keys
    printf("Enter number of keys : ");
    scanf("%d", &n);

    char key[n][1000];
    for(int i = 0; i < n; i++)
    {
        printf("\nEnter key %d : ", i + 1);
        scanf("%s", key[i]);

        generateMatrix(key[i]);

        printf("Key %d Matrix:\n", i + 1);
        for(int k = 0; k < 5; k++)
        {
            for(int j = 0; j < 5; j++)
            {
                printf("%c  ", mat[k][j]);
            }
            printf("\n");
        }

        printf("Actual Message \t\t: %s\n", plaintext);

        formatMessage(plaintext);
        printf("Formatted Message \t: %s\n", plaintext);

        encrypt(plaintext);
        printf("Encrypted Message \t: %s\n", plaintext);

        decrypt(plaintext);
        printf("Decrypted Message \t: %s\n", plaintext);
    }
    return 0;
}
