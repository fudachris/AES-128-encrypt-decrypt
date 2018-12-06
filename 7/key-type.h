#ifndef KEYTYPE_H_INCLUDED                        
#define KEYTYPE_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "functions.h"

class HexType;

class KeyType
{
    public:
        KeyType (HexType k);
        KeyType (void);

        std::vector<HexType> GetKeySchedule (void);

        void Print(void);

    private:
        void GetKeyWords (HexType tmp, Words **out);
        void CreateKeySchedule (void);
        void NonlinearKeyFunction (Words in, 
                                   Words **out,
                                   int round_number
                                  );

        //vector to store complete key schedule
        std::vector<HexType> keySchedule;    
};


#endif
