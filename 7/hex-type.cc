#include "hex-type.h"
#include "ascii-type.h"
#include "base64-type.h"
#include "functions.h"

HexType::HexType(char *input, size_t len)
{
    size_t hl = len;

    if (hl % 2 != 0)
    {
        std::cout << "\nHexType init. error: length should be even " << std::endl;
        hex.w = (uint8_t *)malloc (2 * sizeof (uint8_t));
        hex.w[0] = 0;
        hex.w[1] = 0;
    }
    else 
    {
        hex.w = (uint8_t *) malloc (hl * sizeof (uint8_t));

        for (size_t i = 0; i < len; i++)
        {
            hex.w[i] = GetHexValue (input[i]);
        }

        hex.l = hl;
    }
}

HexType::HexType(uint8_t *input, size_t len)
{
    size_t hl = len;

    if (hl % 2 != 0)
    {
        std::cout << "\nHexType init. error: length should be even " << std::endl;
        hex.w = (uint8_t *)malloc (2 * sizeof (uint8_t));
        hex.w[0] = 0;
        hex.w[1] = 0;
    }
    else 
    {
        hex.w = (uint8_t *) malloc (hl * sizeof (uint8_t));
        memcpy (hex.w,input,hl);

        hex.l = hl;
    }
}

HexType::HexType(Words h)
{
    size_t len = h.l;

    hex.w = (uint8_t *) malloc (len * sizeof(uint8_t));
    memcpy (hex.w, h.w, len);

    hex.l = len;
}

HexType::HexType(void)
{
}

Words
HexType::GetHexWords (void)
{
    return hex;
}

void
HexType::CreateAscii (void)
{
    size_t length = hex.l;
    length /= 2;    //ascii will be 0.5 length of hex

    Words tmp;

    tmp.w = (uint8_t *) malloc (length * sizeof(uint8_t));

    size_t j = 0;

    for (size_t i = 0; j < length; i+=2, j++)
    {                              
        tmp.w[j] = ((hex.w[i]) & 0x0F) << 4 | (hex.w[i+1]) & 0x0F;
    }

    tmp.l = length;

    ascii = (AsciiType*) malloc (1 * sizeof(AsciiType));
    *ascii = (AsciiType(tmp));
}

AsciiType
HexType::GetAscii (void)
{
    return (*ascii);
}

void
HexType::CreateBase64 (void)
{
    CreateAscii();
    AsciiType bytes = GetAscii();
    Words ab = bytes.GetAsciiWords();
    size_t length = ab.l;
    size_t pad = length % 3 > 0 ? (3 - length % 3):0;

    length += pad;

    size_t b64_length = (length * 4) / 3;
    
    uint8_t pad_str[2];
    pad_str[0] = 0;
    pad_str[1] = 0;

    ab.w = (uint8_t *) realloc (ab.w, length * sizeof(uint8_t));
    memcpy(ab.w+length-pad, pad_str, pad);

    Words tmp;
    tmp.w = (uint8_t *) malloc (b64_length * sizeof(uint8_t));
    tmp.l = b64_length;

    for (size_t i = 0, j = 0; i < b64_length; i+= 4, j+=3)
    {
        tmp.w[i] = (ab.w[j] & 0xFC) >> 2;
        tmp.w[i+1] = (ab.w[j] & 0x03) << 4 | (ab.w[j+1] & 0xF0) >> 4;
        tmp.w[i+2] = (ab.w[j+1] & 0x0F) << 2 | (ab.w[j+2] & 0xC0) >> 6;
        tmp.w[i+3] = (ab.w[j+2] & 0x3F);

    }

    if (pad == 1)
    {
        tmp.w[b64_length-1] = 64;
    }

    if (pad == 2)
    {
        tmp.w[b64_length-1] = 64;
        tmp.w[b64_length-2] = 64;
    }

    b64 = (Base64Type*) malloc (1 * sizeof (Base64Type));
    *b64 = Base64Type(tmp);
}

Base64Type
HexType::GetBase64 (void)
{
    return (*b64);
}

void
HexType::Print(void)
{
    for (size_t i = 0; i < hex.l; i++)
    {
        printf("%x",hex.w[i]);
    }
}
