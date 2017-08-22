# ESP8266 ChaCha20 and Poly1305 helper library
Simple encapsulation library for [Crypto](https://github.com/rweather/arduinolibs/tree/master/libraries/Crypto) library, used for encrypting and decrypting with ChaCha20 and Poly1305 algorithms.

ChaCha20-Poly1305 is an AEAD, Authenticated Encryption with Additional Data cipher. It uses four components:
* A secret **key**.
* A unique **initialization value** - aka the IV. It must be unique between encrypt invocations.
* Non-secret, additional data. This data will not be encrypted, but will be **authenticated** - this is the AD in AEAD and **tag** is generated from this and IV with usage of key.
* The **message** to be encrypted.

It works in two parts, first is encryption with ChaCha20 and second is generating hash with Poly1305. Final output is ciphertext with MAC (Message Authentication Code).

[More details.](https://blog.cloudflare.com/it-takes-two-to-chacha-poly/)

# Provided methods

```C
    void cipher(const byte key[CHA_CHA_POLY_KEY_SIZE],              // input: secret key
                const byte iv[CHA_CHA_POLY_IV_SIZE],                // input: IV
                const byte auth[CHA_CHA_POLY_AUTH_SIZE],            // input: authentication message
                const byte plainText[CHA_CHA_POLY_MESSAGE_SIZE],    // input: message to be encrypted
                byte cipherText[CHA_CHA_POLY_MESSAGE_SIZE],         // output: encrypted message
                byte tag[CHA_CHA_POLY_TAG_SIZE]);                   // output: authentication tag

    bool decipher(const byte key[CHA_CHA_POLY_KEY_SIZE],            // input: secret key
                  const byte iv[CHA_CHA_POLY_IV_SIZE],              // input: IV
                  const byte auth[CHA_CHA_POLY_AUTH_SIZE],          // input: authentication message
                  const byte cipherText[CHA_CHA_POLY_MESSAGE_SIZE], // input: encrypted message
                  byte plainText[CHA_CHA_POLY_MESSAGE_SIZE],        // output: decrypted message
                  const byte tag[CHA_CHA_POLY_TAG_SIZE]);           // input: authentication tag

    // generates random IV
    void generateIv(byte iv[CHA_CHA_POLY_IV_SIZE]);
```

# Size of elements

```C
#define CHA_CHA_POLY_KEY_SIZE 32
#define CHA_CHA_POLY_IV_SIZE 12
#define CHA_CHA_POLY_AUTH_SIZE 16
#define CHA_CHA_POLY_TAG_SIZE 16
#define CHA_CHA_POLY_MESSAGE_SIZE 60
```

# Usage
```C
    byte key[CHA_CHA_POLY_KEY_SIZE] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};
    byte auth[CHA_CHA_POLY_AUTH_SIZE] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    byte iv[CHA_CHA_POLY_IV_SIZE];
    ChaChaPolyCipher.generateIv(iv);

    // construct plain text message
    byte plainText[CHA_CHA_POLY_MESSAGE_SIZE];
    String plain = "{\"my secret message\"}";
    plain.getBytes(plainText, CHA_CHA_POLY_MESSAGE_SIZE);

    // encrypt plain text message from plainText to cipherText
    byte cipherText[CHA_CHA_POLY_MESSAGE_SIZE];
    byte tag[CHA_CHA_POLY_TAG_SIZE];
    ChaChaPolyCipher.cipher(key, iv, auth, plainText, cipherText, tag);

    // decrypt message from cipherText to plainText
    // output is valid only if result is true
    bool result = ChaChaPolyCipher.decipher(key, iv, auth, cipherText, plainText, tag);
```