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
{
    /*
    ifstream file;
    //ifstream f("compressedfile1.z", ios::binary | ios::in);
    file.open("compressedfile1.z", std::ifstream::binary | std::ifstream::ate | std::ifstream::in);
    cout << file.tellg() << endl;
    file.seekg(0, ios::beg);
    char c;
    string cString;
    while (file.get(c))
    {
    //    for (int i = 7; i >= 0; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
    //    cout << ((c >> i) & 1);
        bitset<8> cBin(c);
        cString += cBin.to_string();
        //cout << cBin << endl;
    }
    cout << cString << endl;
    file.close();

    */

    LZWdecode i1;
    i1.initialiseDictionary();
    i1.decompress("compressedfile2.z");
    return 0;
}
