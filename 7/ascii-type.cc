#include "ascii-type.h"
#include "hex-type.h"
#include "base64-type.h"

AsciiType::AsciiType (char *a, size_t len)
{
    ascii.w = (uint8_t *) malloc ((len+1) * sizeof (uint8_t));

    for (size_t i = 0; i < len; i++)
    {
        ascii.w[i] = uint8_t(a[i]);
    }
    
    ascii.w[len] = '\0';
    ascii.l = len;
}

AsciiType::AsciiType(Words a)
{
    size_t len = a.l;

    ascii.w = (uint8_t *) malloc ((len+1) * sizeof (uint8_t));
    memcpy (ascii.w, a.w, len);

    ascii.w[len] = '\0';
    ascii.l = len;
}

AsciiType::AsciiType (void)
{
}

Words
AsciiType::GetAsciiWords (void)
{
    return ascii;
}

void
AsciiType::CreateHex (void)
{
    size_t ascii_length = ascii.l;
    size_t hex_length = 2 * ascii_length;
    Words tmp;

    tmp.w = (uint8_t *) malloc (hex_length * sizeof (uint8_t));
    
    size_t i = 0, j = 0; 
    for (; j < hex_length; i++, j+=2)
    {
        tmp.w[j] = ((ascii.w[i]) & 0xF0) >> 4; 
        tmp.w[j+1] = (ascii.w[i] & 0x0F);
    }

    tmp.l = hex_length;

    hex = (HexType*) malloc (1 * sizeof(HexType));
    *hex = HexType(tmp);
}

HexType
AsciiType::GetHex (void)
{
    return (*hex);
}

void
AsciiType::CreateBase64 (void)
{
    HexType h = HexType(*hex);
    b64 = (Base64Type*) malloc (1 * sizeof (Base64Type));
    h.CreateBase64();
    *b64 = (h.GetBase64 ());    
}

Base64Type
AsciiType::GetBase64 (void)
{
    return (*b64);
}

void
AsciiType::Print (void)
{
    for (size_t i = 0; i < ascii.l; i++)
    {
        printf("%c",ascii.w[i]);
    }
}
