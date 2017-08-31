#include <ChaChaPoly.h>
#include "ChaChaPolyHelper.h"

ChaChaPoly chaChaPoly;

void ChaChaPolyHelper::encrypt(const byte key[CHA_CHA_POLY_KEY_SIZE], const byte iv[CHA_CHA_POLY_IV_SIZE], const byte auth[CHA_CHA_POLY_AUTH_SIZE], const byte plainText[CHA_CHA_POLY_MESSAGE_SIZE], byte cipherText[CHA_CHA_POLY_MESSAGE_SIZE], byte tag[CHA_CHA_POLY_TAG_SIZE])
{
    chaChaPoly.clear();
    chaChaPoly.setKey(key, CHA_CHA_POLY_KEY_SIZE);
    chaChaPoly.setIV(iv, CHA_CHA_POLY_IV_SIZE);
    chaChaPoly.addAuthData(auth, CHA_CHA_POLY_AUTH_SIZE);
    chaChaPoly.encrypt(cipherText, plainText, CHA_CHA_POLY_MESSAGE_SIZE);
    chaChaPoly.computeTag(tag, CHA_CHA_POLY_TAG_SIZE);
}

bool ChaChaPolyHelper::decrypt(const byte key[CHA_CHA_POLY_KEY_SIZE], const byte iv[CHA_CHA_POLY_IV_SIZE], const byte auth[CHA_CHA_POLY_AUTH_SIZE], const byte cipherText[CHA_CHA_POLY_MESSAGE_SIZE], byte plainText[CHA_CHA_POLY_MESSAGE_SIZE], const byte tag[CHA_CHA_POLY_TAG_SIZE])
{
    chaChaPoly.clear();
    chaChaPoly.setKey(key, CHA_CHA_POLY_KEY_SIZE);
    chaChaPoly.setIV(iv, CHA_CHA_POLY_IV_SIZE);
    chaChaPoly.addAuthData(auth, CHA_CHA_POLY_AUTH_SIZE);
    chaChaPoly.decrypt(plainText, cipherText, CHA_CHA_POLY_MESSAGE_SIZE);
    return chaChaPoly.checkTag(tag, CHA_CHA_POLY_TAG_SIZE);
}

uint8_t getrnd()
{
    uint8_t really_random = *(volatile uint8_t *)0x3FF20E44;
    return really_random;
}

void generateRandom(byte *bytes, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        bytes[i] = (byte)getrnd();
    }
}

void ChaChaPolyHelper::generateIv(byte iv[CHA_CHA_POLY_IV_SIZE])
{
    generateRandom(iv, CHA_CHA_POLY_IV_SIZE);
}

ChaChaPolyHelper ChaChaPolyCipher;
