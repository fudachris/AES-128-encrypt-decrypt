#ifndef DECRYPT_H_INCLUDED                                                
#define DECRYPT_H_INCLUDED

#include "functions.h"
#include <vector>
#include <sstream>
#include <string.h>

class HexType;

class Decrypt
{
    public:
        Decrypt (HexType in, std::vector<HexType> ks);
        
        void CreatePlainText (void);
        HexType GetPlainText (void);

        HexType KeyAdd (HexType words_in, HexType key);
        HexType RotateBlock (HexType in);
        HexType InvShiftRows (HexType in);
        HexType InvByteSub (HexType in);
        HexType InvMixCol (HexType words_in);

        void Print (void);
    private:
        HexType *cipherText;
        HexType *plainText;
        std::vector<HexType> keySchedule;
};
#endif
