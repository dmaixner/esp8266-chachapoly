#ifndef _cha_cha_poly_helper_h
#define _cha_cha_poly_helper_h

#include <Arduino.h>

#define CHA_CHA_POLY_KEY_SIZE 32 // fixed
#define CHA_CHA_POLY_IV_SIZE 12  // fixed
#define CHA_CHA_POLY_AUTH_SIZE 16
#define CHA_CHA_POLY_TAG_SIZE 16
#define CHA_CHA_POLY_MESSAGE_SIZE 60

class ChaChaPolyHelper
{
  public:
    void cipher(const byte key[CHA_CHA_POLY_KEY_SIZE],           // input: secret key
                const byte iv[CHA_CHA_POLY_IV_SIZE],             // input: IV
                const byte auth[CHA_CHA_POLY_AUTH_SIZE],         // input: authentication message
                const byte plainText[CHA_CHA_POLY_MESSAGE_SIZE], // input: message to be encrypted
                byte cipherText[CHA_CHA_POLY_MESSAGE_SIZE],      // output: encrypted message
                byte tag[CHA_CHA_POLY_TAG_SIZE]);                // output: authentication tag

    bool decipher(const byte key[CHA_CHA_POLY_KEY_SIZE],            // input: secret key
                  const byte iv[CHA_CHA_POLY_IV_SIZE],              // input: IV
                  const byte auth[CHA_CHA_POLY_AUTH_SIZE],          // input: authentication message
                  const byte cipherText[CHA_CHA_POLY_MESSAGE_SIZE], // input: encrypted message
                  byte plainText[CHA_CHA_POLY_MESSAGE_SIZE],        // output: decrypted message
                  const byte tag[CHA_CHA_POLY_TAG_SIZE]);           // input: authentication tag

    // generates random IV
    void generateIv(byte iv[CHA_CHA_POLY_IV_SIZE]);
};

extern ChaChaPolyHelper ChaChaPolyCipher;

#endif // _cha_cha_poly_helper_h
