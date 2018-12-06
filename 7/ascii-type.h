#ifndef ASCIITYPE_H_INCLUDED                                              
#define ASCIITYPE_H_INCLUDED

#include "functions.h"

class HexType;
class Base64Type;

class AsciiType
{        
    public:    
        AsciiType (char *ascii, size_t l);
        AsciiType (Words ascii);
        AsciiType (void);

        Words GetAsciiWords (void);

        void CreateHex (void); 
        HexType GetHex (void);
        
        void CreateBase64 (void);
        Base64Type GetBase64 (void);

        void Print (void);
    private:

        //ascii input
        Words ascii;
        HexType *hex;
        Base64Type *b64;
};    

#endif
