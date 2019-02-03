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

    std::ofstream outputFile;
    outputFile.open(fileName.substr(0,fileName.find(".")+1) + "_decoded.txt");

    //find file size
    unsigned int numBytes = inputFile.tellg();
    unsigned int numCodes = (8*numBytes)/bits;
    char c;
    std::string prevString, currentString;
    unsigned int long charKey;
    std::string threeByteString; //stores two or three bytes

    if(!(8*numBytes % bits == 0)){
        numCodes-=1;
    }

    inputFile.seekg(0, std::ios::beg);

    //find dictionary size
    unsigned int dictionarySize = dictionary.size();
    //dictionarySize++;
    //std::cout << dictionarySize << std::endl;

    //Deal with two 12 bit codes at a time
    for(int y=0; y<numCodes; y+=2)
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

            if(dictionary.find(charKey) != dictionary.end())
            {
                currentString = dictionary[charKey];
                outputFile << currentString;
            } else {
                currentString = prevString + prevString.substr(0,1);
                outputFile << currentString;
            }
            //add key to dictionary

            //avoid adding a character
            if(!prevString.empty()){
                dictionary.insert({dictionarySize,prevString+currentString.substr(0,1)});
                dictionarySize++;
            }

            //reset if dictionary is too big
            prevString = currentString;

            if(dictionarySize>=pow(2,bits))
            {

                initialiseDictionary();
                dictionarySize = dictionary.size();
            }

        }
    }

    //may have a 16 bit code left, if so do
    //the same as above with a 16 bit code
    if(!(8*numBytes % bits == 0))
    {
        threeByteString.clear();
        for(int i=0;i<2;i++)
        {
            inputFile.get(c);
            std::bitset<8> charBin(c);
            threeByteString += charBin.to_string();
        }

        std::bitset<16> codeBin(threeByteString);
        charKey = codeBin.to_ulong();

        if(dictionary.find(charKey) != dictionary.end())
            {
                currentString = dictionary[charKey];
                outputFile << currentString;
            } else {
                currentString = prevString + prevString.substr(0,1);
                outputFile << currentString;
            }

    }

    outputFile.close();
    inputFile.close();
}
