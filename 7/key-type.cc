#include "key-type.h"
#include "ascii-type.h"
#include "hex-type.h"
#include "base64-type.h"

KeyType::KeyType (HexType k)
{
    keySchedule.push_back (k);
    CreateKeySchedule ();
}

KeyType::KeyType (void)
{
}

std::vector<HexType>
KeyType::GetKeySchedule (void)
{
    return keySchedule;    
}

void
KeyType::GetKeyWords (HexType tmp, Words **out)
{
    Words keyHex = tmp.GetHexWords();

    for (int i = 0, k = 0; i < 4; i++, k+=8)
    {
        for (int j = 0; j < 8; j++)
        {                                                    
            (*out)[i].w[j] = keyHex.w[k+j];
        }
    }
}

void
KeyType::NonlinearKeyFunction (Words word_in,
                               Words **word_out,
                               int round_number
                              )
{
    uint8_t rc[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};

    uint8_t *sub = (uint8_t *) malloc (4 * sizeof(uint8_t)); 

    for (int i = 0, j = 0; i < 8; i+=2, j++)
    {
        uint8_t x = word_in.w[i];
        uint8_t y = word_in.w[i+1];
        sub[j] = ForwardSubBox(x,y);
    }

    Words *out = (Words *) malloc (4 * sizeof(Words));
    
    for (int i = 0; i < 4; i++)
    {
        out[i].w = (uint8_t *) malloc (8 * sizeof (uint8_t));
        out[i].l = 8;
    }

    out = *word_out;

    (*out).w[0] = ((rc[round_number-1] ^ sub[1]) & 0xF0) >> 4;
    (*out).w[1] = (rc[round_number-1] ^ sub[1]) & 0x0F;
    
    (*out).w[2] = (sub[2] & 0xF0) >> 4;
    (*out).w[3] = (sub[2] & 0x0F);
    
    (*out).w[4] = (sub[3] & 0xF0) >> 4;
    (*out).w[5] = (sub[3] & 0x0F);
    
    (*out).w[6] = (sub[0] & 0xF0) >> 4;
    (*out).w[7] = (sub[0] & 0x0F);

    free(sub);
}

void
KeyType::CreateKeySchedule (void)
{
    for (int rn = 1; rn < 11; rn++)
    {
        HexType tmp = keySchedule[rn-1];

        Words *w = (Words *) malloc (4 * sizeof (Words));
        Words *v = (Words *) malloc (4 * sizeof (Words));
        Words *f = (Words *) malloc (4 * sizeof (Words));
        
        for (int i = 0; i < 4; i++)
        {
            w[i].w = (uint8_t *) malloc (8 * sizeof(uint8_t));
            w[i].l = 8;
            
            v[i].w = (uint8_t *) malloc (8 * sizeof(uint8_t));
            v[i].l = 8;
            
            f[i].w = (uint8_t *) malloc (8 * sizeof(uint8_t));
            f[i].l = 8;
        }

        GetKeyWords (tmp,&w);

        for (int i = 0; i < 4; i++)
        {
            memcpy (v[i].w,w[i].w,8);
        }


        Words *v3_return = (Words *) malloc (1 * sizeof (Words));
        (*v3_return).w = (uint8_t *) malloc (8 * sizeof (uint8_t));
        (*v3_return).l = 8;
        
        NonlinearKeyFunction(v[3], &v3_return, rn);

        for (int i = 0; i < 8; i++)
        {
            f[0].w[i] = v[0].w[i] ^ (*v3_return).w[i];
            f[1].w[i] = v[1].w[i] ^ f[0].w[i];
            f[2].w[i] = v[2].w[i] ^ f[1].w[i]; 
            f[3].w[i] = v[3].w[i] ^ f[2].w[i];
        }
        
        uint8_t *ks = (uint8_t *) malloc (32 * sizeof(uint8_t));

        for (int i = 0, j = 0; i < 32; i+=8, j++)
        {
            memcpy(ks+i,f[j].w,8);
        }

        HexType ht = HexType(ks,32);
        
        keySchedule.push_back(ht);

        free(w);
        free(v);
        free(f);
        free(ks);   
        free(v3_return);   
    }    
}

void
KeyType::Print (void)
{
    size_t vs = keySchedule.size();

    for (size_t i = 0; i < vs; i++)
    {
        HexType h = keySchedule[i];
        h.Print();
        std::cout << std::endl;
    }
}
