#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

// AES key for encryption and decryption (128-bit key)
unsigned char aes_key[] = "0123456789abcdef";

// Function to pad the plaintext
int pad(unsigned char *input, unsigned char *output) {
    int len = strlen((char *)input);
    int pad_len = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    memcpy(output, input, len);
    for (int i = len; i < len + pad_len; i++) {
        output[i] = pad_len;
    }
    return len + pad_len;
}

// Function to unpad the decrypted text
int unpad(unsigned char *input, unsigned char *output, int len) {
    int pad_len = input[len - 1];
    memcpy(output, input, len - pad_len);
    output[len - pad_len] = '\0';
    return len - pad_len;
}

// Function to encrypt plaintext using AES
void aes_encrypt(unsigned char *plaintext, unsigned char *ciphertext) {
    AES_KEY key;
    AES_set_encrypt_key(aes_key, 128, &key);
    for (int i = 0; i < AES_BLOCK_SIZE; i += AES_BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &key);
    }
}

// Function to decrypt ciphertext using AES
void aes_decrypt(unsigned char *ciphertext, unsigned char *decryptedtext) {
    AES_KEY key;
    AES_set_decrypt_key(aes_key, 128, &key);
    for (int i = 0; i < AES_BLOCK_SIZE; i += AES_BLOCK_SIZE) {
        AES_decrypt(ciphertext + i, decryptedtext + i, &key);
    }
}

int main() {
    unsigned char plaintext[] = "welcome to ISE";
    unsigned char paddedtext[32]; // To hold padded text
    unsigned char ciphertext[32];
    unsigned char decryptedtext[32];
    unsigned char unpaddedtext[32];

    // Pad the plaintext
    int padded_len = pad(plaintext, paddedtext);

    // Encrypt the padded plaintext
    aes_encrypt(paddedtext, ciphertext);

    // Decrypt the ciphertext
    aes_decrypt(ciphertext, decryptedtext);

    // Unpad the decrypted text
    int unpadded_len = unpad(decryptedtext, unpaddedtext, padded_len);

    printf("Original message: %s\n", plaintext);
    printf("Encrypted message: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted message: %s\n", unpaddedtext);

    return 0;
}
