#ifndef BASE64TYPE_H_INCLUDED
#define BASE64TYPE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <string.h>
#include "functions.h"

class AsciiType;
class HexType;
//converts to hex
//converts to ascii
class Base64Type
{
    public:
        Base64Type (char *b64, size_t l);
        Base64Type (uint8_t *b64, size_t l);
        Base64Type (Words b);
        Base64Type (void);

        
        Words GetBase64Words (void);

        void CreateHex(void);
        HexType GetHex (void);
        
        void CreateAscii (void);
        AsciiType GetAscii (void);

        void Print(void);
    private: 
        //b64 input    
        Words b64;
        HexType *hex;
        AsciiType *ascii;
};



#endif
