#include "base64-type.h"
#include "ascii-type.h"
#include "hex-type.h"

Base64Type::Base64Type(char *b, size_t len)
{
    size_t bl = len;

    if (bl % 2 != 0)
    {
        std::cout << "\nBase64Type init. error: length should be even " << std::endl;
        b64.w = (uint8_t *) malloc (2 * sizeof (uint8_t));
        b64.w[0] = '0';
        b64.w[1] = '0';
    }
    else
    {
        b64.w = (uint8_t *) malloc (bl * sizeof (uint8_t));

        for (size_t i = 0; i < len; i++)
        {
            b64.w[i] =  GetBase64Value (b[i]);
        }

        b64.l = bl;
    }
}

Base64Type::Base64Type(uint8_t *b, size_t len)
{
    size_t bl = len;

    if (bl % 2 != 0)
    {
        std::cout << "\nHexType init. error: length should be even " << std::endl;
        b64.w = (uint8_t *)malloc (2 * sizeof (uint8_t));
        b64.w[0] = 0;
        b64.w[1] = 0;
    }
    else 
    {
        b64.w = (uint8_t *) malloc (bl * sizeof (uint8_t));
        memcpy (b64.w,b,bl);

        b64.l = bl;
    }

}

Base64Type::Base64Type(Words b)
{
    size_t len = b.l;

    b64.w = (uint8_t *) malloc (len * sizeof(uint8_t));
    memcpy (b64.w, b.w, len);

    b64.l = len;
}

Base64Type::Base64Type(void)
{
}

Words
Base64Type::GetBase64Words (void)
{
    return b64;
}

void
Base64Type::CreateHex (void)
{
    size_t b64_length = b64.l;

    int count = 0;

    count += b64.w[b64_length-1] == 64? 64 : 0;
    count += b64.w[b64_length-2] == 64? 64 : 0;

    size_t hex_length = (b64_length * 3)/2;

    Words tmp;
    tmp.l = hex_length;

    tmp.w = (uint8_t *) malloc (hex_length * sizeof(uint8_t));
    size_t i = 0, j = 0;
    for (; i < b64_length; i+=2, j +=3 )
    {
        uint8_t b0 = b64.w[i];
        uint8_t b1 = b64.w[i+1];

        b0 = b0 == 64 ? 255 : b0;
        b1 = b1 == 64 ? 255 : b1;
            
        uint8_t h0 = (b0 & 0x3C) >> 2;
        uint8_t h1 = (b0 & 0x03) << 2 | (b1 & 0x30) >> 4;
        uint8_t h2 = b1 & 0x0F;

        tmp.w[j] = h0;
        tmp.w[j+1] = h1;
        tmp.w[j+2] = h2;
    }

    hex = (HexType*) malloc (1 * sizeof(HexType));
    
    if (count == 64 || count == 128)
    {     
        size_t h_length = hex_length  - 2 * (count/64);
        Words h;
        h.w = (uint8_t *) malloc (h_length * sizeof(uint8_t));
        memcpy (h.w,tmp.w, h_length);
        h.l = h_length;
        *hex = HexType(h);
        return;
    }

    *hex = HexType(tmp);
}

HexType
Base64Type::GetHex (void)
{   
    return (*hex);
}

void
Base64Type::CreateAscii (void)
{
    HexType h = HexType (*hex);
    ascii = (AsciiType*) malloc (1 * sizeof(AsciiType));
    h.CreateAscii();
    *ascii = (h.GetAscii());
}

AsciiType
Base64Type::GetAscii (void)
{
    return (*ascii);
}

void
Base64Type::Print (void)
{
    for (size_t i = 0; i < b64.l; i++)
    {
        printf("%c",GetBase64Char(b64.w[i]));
    }
}
