#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
long long int mod(long long int base, long long int exp, long long int modulo)
{
    long long int res = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            res = (base * res) % modulo;
        }
        base = (base * base) % modulo;
        exp /= 2;
    }
    return res;
}
int main()
{
    long long int p = 3;
    long long int q = 11;
    long long int n = (p * q);
    long long int phi = (p - 1) * (q - 1);

    long long int e = 7;
    long long int d = 3;

    long long int a = 31;

    long long int cipher = mod(a, e, n);
    printf("Encrypted message is %lld\n", cipher);

    long long int text = mod(cipher, d, n);
    printf("Decrypted message is %lld\n", text);
    return 0;
}
