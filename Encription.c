#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void aes_encrypt(const unsigned char *plaintext, int plaintext_length, const unsigned char *key, unsigned char *ciphertext) {
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    AES_set_encrypt_key(key, 256, &aes_key);
    RAND_bytes(iv, AES_BLOCK_SIZE);

    AES_cbc_encrypt(plaintext, ciphertext, plaintext_length, &aes_key, iv, AES_ENCRYPT);
}

void aes_decrypt(const unsigned char *ciphertext, int ciphertext_length, const unsigned char *key, unsigned char *decryptedtext) {
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];

    AES_set_decrypt_key(key, 256, &aes_key);

    AES_cbc_encrypt(ciphertext, decryptedtext, ciphertext_length, &aes_key, iv, AES_DECRYPT);
}

int main() {
    const unsigned char encryption_key[32]; // 256-bit key
    unsigned char plaintext[] = "Hello, AES!";
    int plaintext_length = strlen((const char *)plaintext);
    unsigned char ciphertext[plaintext_length];
    unsigned char decryptedtext[plaintext_length];

    // Generate a random key
    RAND_bytes(encryption_key, sizeof(encryption_key));

    // Encrypt the plaintext
    aes_encrypt(plaintext, plaintext_length, encryption_key, ciphertext);

    // Decrypt the ciphertext
    aes_decrypt(ciphertext, plaintext_length, encryption_key, decryptedtext);

    // Print results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_length; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\nDecrypted: %s\n", decryptedtext);

    return 0;
}
