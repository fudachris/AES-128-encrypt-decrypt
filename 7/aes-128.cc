#include <fstream>
#include <string.h>
#include <sstream>
#include "functions.h"
#include "ascii-type.h"
#include "hex-type.h"
#include "key-type.h"
#include "encrypt.h"
#include "decrypt.h"
#include "base64-type.h"


int main ()
{

    char akey[17] = "YELLOW SUBMARINE";
    AsciiType ak = AsciiType(akey,16);
    ak.CreateHex();
    HexType hkey = ak.GetHex();
    KeyType kt = KeyType(hkey);
    std::vector<HexType> ks = kt.GetKeySchedule();
    
    std::ifstream input("7.txt");
    char  *a;
    uint8_t *t = (uint8_t *) malloc (1 * sizeof(uint8_t));
    uint8_t *c = (uint8_t *) malloc (1 * sizeof(uint8_t));
    c[0] = 0;

    std::string line;

    size_t total_length = 0;

    for (;getline(input, line);)
    {
        size_t length = line.length();
        a = (char *) malloc (length * sizeof(char));
        memcpy (a,line.c_str(),length);

        Base64Type at = Base64Type(a,length);
        at.CreateHex();

        HexType ht = at.GetHex();
        Words htw = ht.GetHexWords();

        size_t out_length = htw.l;
        t = (uint8_t *) malloc (out_length * sizeof (uint8_t));

        memcpy(t,htw.w,out_length);

        c = (uint8_t *) realloc (c, (out_length+total_length)*sizeof(uint8_t));

        memcpy(c+total_length, t, out_length);
        total_length += out_length;

        bzero(a,line.length());
    }


    std::ofstream stream;
    stream.open("PlainText.txt");

    for (int i = 0; i < total_length; i+=32)
    {
        uint8_t *m = (uint8_t*)malloc(32 * sizeof(uint8_t));
        memcpy(m,c+i,32);
        HexType mh = HexType(m,32);
        Decrypt dm = Decrypt(mh,ks);
        dm.CreatePlainText();
        HexType pt = dm.GetPlainText();
        pt.CreateAscii();
        AsciiType at = pt.GetAscii();
        Words atww = at.GetAsciiWords();
        stream << atww.w;
    }
    
}
