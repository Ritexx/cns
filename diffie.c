#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define p 5
#define q 23

int mod_fun(int base, int private, int mod){
    int result = 1;
    while(private>0){
        if(private % 2 == 1){
            result = (result * base) % mod; 
        }
        base = (base*base) % mod;
        private /= 2;
    }
    return result;
}

void operation(int private_key , int *public_key){
    *public_key = mod_fun(p,private_key,q);
}

int main(){
    int private_key_A , private_key_B;
    int public_key_A, public_key_B;
    int share_key_A, share_key_B;

    srand(time(NULL));

    private_key_A = rand() % (q-1) + 1;
    private_key_B = rand() % (q-1) +1;

    operation(private_key_A,&public_key_A);
    operation(private_key_B,&public_key_B);

    share_key_A = mod_fun(public_key_B,private_key_A,q);
    share_key_B = mod_fun(public_key_A,private_key_B,q);

    printf("person A choosed: %d\n",p);
    printf("person b choosed: %d\n",q);
    printf("person A private key: %d\n",private_key_A);
    printf("person b private key: %d\n",private_key_B);
    printf("person A Public key: %d\n",public_key_A);
    printf("person b Public key: %d\n",public_key_B);
    printf("person A shared key: %d\n",share_key_A);
    printf("person b shared key: %d\n",share_key_B);


}
