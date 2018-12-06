#ifndef HEXTYPE_H_INCLUDED                                                
#define HEXTYPE_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include "functions.h"

class AsciiType;
class Base64Type;

//converts to ascii
//converts to base64
class HexType
{
    public:    
        HexType (char *hex, size_t l);
        HexType (uint8_t *hex, size_t l);
        HexType (Words h);
        HexType (void);

        Words GetHexWords (void);

        void CreateAscii (void);
        AsciiType GetAscii (void);
    
        void CreateBase64 (void);
        Base64Type GetBase64 (void);
        

        void Print (void);
    private:
        //hex input
        Words hex;
        AsciiType *ascii;
        Base64Type *b64;
};

#endif
