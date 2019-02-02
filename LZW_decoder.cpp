#include "LZW_decoder.h"

LZWdecode::LZWdecode(){}

LZWdecode::~LZWdecode(){}


//initialises dictionary with the first 256 ASCII characters
void LZWdecode::initialiseDictionary()
{

    if(!dictionary.empty())
    {
        dictionary.clear();
    }

    //add first 256 ASCII characters to dictionary
    for (int i=0; i<256; i++)
    {
        //char asciiChar = i;
        std::string asciiString(1,i) ;
        dictionary.insert({i,asciiString});
    }
};

//decompresses the input file and outputs as a .txt file.
//fileName should include its file extension
void LZWdecode::decompress(std::string fileName)
{
    std::ifstream inputFile;
    inputFile.open(fileName, std::ifstream::binary | std::ifstream::ate);

    if(!inputFile.is_open())
    {
        std::cout << "Error. Unable to open " << fileName << std::endl;
        return;
    }

    //std::string inputFileString;

    //find file size
    unsigned int numBytes = inputFile.tellg();
    unsigned int numCodes = ((8*numBytes)/bits)%12 == 0 ? ((8*numBytes)/bits) : ((8*numBytes)/bits) + 1;
    char c;
    unsigned int long charKey;
    std::string threeByteString; //stores two or three bytes

    inputFile.seekg(0, std::ios::beg);

    //Deal with two 12 bit codes at a time
    for(int y=0; y<((8*numBytes)/bits); y+=2)
    {
        threeByteString.clear();

        for(int i=0;i<3;i++) //read 3 bytes from the input file
        {
            inputFile.get(c);
            std::bitset<8> charBin(c);
            threeByteString += charBin.to_string();
        }

        for(int i=0;i<2;i++)
        {
            std::bitset<12> codeBin(threeByteString.substr(i*bits,bits));
            charKey = codeBin.to_ulong();
            std::cout << charKey << std::endl; //dictionary[charKey];
        }
    }

    inputFile.close();
}
