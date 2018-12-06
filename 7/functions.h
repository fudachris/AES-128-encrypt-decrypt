#ifndef FUNCTIONS_H_INCLUDED                           
#define FUNCTIONS_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>

struct Words
{
    uint8_t *w;
    size_t l;
};

char GetBase64Char (int b);
uint8_t GetBase64Value (char b);

char GetHexChar (int h);
uint8_t GetHexValue (char c);
char HexToByte (char a, char b);

uint8_t ForwardSubBox (int x, int y);
uint8_t InverseSubBox (int x, int y);

uint8_t E_Table (int x, int y);
uint8_t L_Table (int x, int y);

#endif
