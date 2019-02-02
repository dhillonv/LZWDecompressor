#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <map>
#include <vector>
#include <bitset>

#include "LZW_decoder.cpp"

using namespace std;

string charToBinary(char c){
    string binaryChar = "";
    int bit;
    for(int i=7; i>=0;i--)
    {
        bit = ((c >> i) & 1);
        binaryChar += bit;
    }

    return binaryChar;
    }

int main()
{       //num bytes are 21 45 19928 400328
        //num codes 14 30 13285F 266885F

    //ifstream file;
    //ifstream f("compressedfile1.z", ios::binary | ios::in);
    //file.open("compressedfile4.z", std::ifstream::binary | std::ifstream::ate | std::ifstream::in);
    //cout << file.tellg() << endl;
    /* file.seekg(0, ios::beg);
    char c;
    string cString;
    while (file.get(c))
    {
        bitset<8> cBin(c);
        cString += cBin.to_string();
    }
    cout << cString << endl;
    file.close();
    */



    LZWdecode i1;
    i1.initialiseDictionary();
    i1.decompress("compressedfile3.z");

    return 0;
}
