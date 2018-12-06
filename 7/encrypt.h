#ifndef ENCRYPT_H_INCLUDED                                                  
#define ENCRYPT_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <stdint.h>

class HexType;

class Encrypt
{
    public:
        Encrypt (HexType i, std::vector<HexType> ks);

        void CreateCipherText(void);
        HexType GetCipherText (void);

        HexType KeyAdd (HexType words_in, HexType key);
        HexType ByteSub (HexType words_in);
        HexType RotateBlock (HexType words_in);
        HexType ShiftRows (HexType words_in);
        HexType MixCol (HexType words_in);

        void Print (void);
    private:
        HexType *plainText;		
        HexType *cipherText;		
        std::vector<HexType> keySchedule;
};

#endif
