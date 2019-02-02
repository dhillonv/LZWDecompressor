#ifndef LZW_DECODER_H_INCLUDED
#define LZW_DECODER_H_INCLUDED

#include<math.h>

#include <string>
#include <unordered_map>
#include <bitset>

#include <iostream>
#include <fstream>

class LZWdecode{

private:
    int bits=12;
    //std::unordered_map<int,std::string> dictionary;

public:
    std::unordered_map<int,std::string> dictionary;

    LZWdecode();
    ~LZWdecode();

    //opens the file with filename
    void openFile(std::string filename);

    //initialises dictionary with the first 256 ASCII characters
    void initialiseDictionary();

    //decompresses the input file and outputs as a .txt file.
    void decompress(std::string fileName);


};

#endif // LZW_DECODER_H_INCLUDED
