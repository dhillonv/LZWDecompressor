#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <map>
#include <vector>
#include <bitset>

#include "LZW_decoder.cpp"

using namespace std;

int main()
{       //num bytes are 21 45 19928 400328
        //num codes 14 30 13285F 266885F

    LZWdecode i1;
    i1.initialiseDictionary();
    i1.decompress("compressedfile2.z");

    return 0;
}
