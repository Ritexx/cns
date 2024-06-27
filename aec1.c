#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

// AES key for encryption and decryption (128-bit key)
unsigned char aes_key[] = "0123456789abcdef";

// Function to pad the plaintext
void pad(unsigned char *input, unsigned char *output) {
    int len = strlen((char *)input);
    int pad_len = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    memcpy(output, input, len);
    for (int i = len; i < len + pad_len; i++) {
        output[i] = pad_len;
    }
}

// Function to unpad the decrypted text
void unpad(unsigned char *input, unsigned char *output) {
    int len = strlen((char *)input);
    int pad_len = input[len - 1];
    memcpy(output, input, len - pad_len);
    output[len - pad_len] = '\0';
}

// Function to encrypt plaintext using AES
void aes_encrypt(unsigned char *plaintext, unsigned char *ciphertext) {
    AES_KEY key;
    if (AES_set_encrypt_key(aes_key, 128, &key) < 0) {
        fprintf(stderr, "Unable to set encryption key in AES\n");
        exit(1);
    }
    AES_encrypt(plaintext, ciphertext, &key);
}

// Function to decrypt ciphertext using AES
void aes_decrypt(unsigned char *ciphertext, unsigned char *decryptedtext) {
    AES_KEY key;
    if (AES_set_decrypt_key(aes_key, 128, &key) < 0) {
        fprintf(stderr, "Unable to set decryption key in AES\n");
        exit(1);
    }
    AES_decrypt(ciphertext, decryptedtext, &key);
}

int main() {
    unsigned char plaintext[] = "welcome to ISE";
    unsigned char paddedtext[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char decryptedtext[AES_BLOCK_SIZE];
    unsigned char unpaddedtext[AES_BLOCK_SIZE];

    // Pad the plaintext
    pad(plaintext, paddedtext);

    // Encrypt the padded plaintext
    aes_encrypt(paddedtext, ciphertext);

    // Decrypt the ciphertext
    aes_decrypt(ciphertext, decryptedtext);

    // Unpad the decrypted text
    unpad(decryptedtext, unpaddedtext);

    printf("Original message: %s\n", plaintext);
    printf("Encrypted message: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted message: %s\n", unpaddedtext);

    return 0;
}
