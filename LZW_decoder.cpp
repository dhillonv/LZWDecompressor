#include "LZW_decoder.h"

LZWdecode::LZWdecode(){}

LZWdecode::~LZWdecode(){}

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

void LZWdecode::decompress(std::string fileName)
{
    std::ifstream inputFile;
    inputFile.open(fileName, std::ifstream::binary | std::ifstream::ate);

    //check if file was successfully opened
    if(!inputFile.is_open())
    {
        std::cout << "Error. Unable to open " << fileName << std::endl;
        return;
    }

    //output file
    std::ofstream outputFile;
    outputFile.open(fileName.substr(0,fileName.find(".")) + "_decoded.txt");

    //find input file size
    unsigned int numBytes = inputFile.tellg(), numCodes = (8*numBytes)/bits, charKey;
    char c;
    std::string prevString, currentString, threeByteString;

    //check if the last code has been padded to 16 bit
    if(!(8*numBytes % bits == 0)){
        numCodes-=1;
    }

    //return to beginning of the file
    inputFile.seekg(0, std::ios::beg);

    //initialise dictionary and find dictionary size
    initialiseDictionary();
    unsigned int dictionarySize = dictionary.size();

    //Deal with two 12 bit codes at a time
    for(unsigned int y=0; y<numCodes; y+=2)
    {
        threeByteString.clear();

        for(int i=0;i<3;i++) //read 3 bytes from the input file
        {
            inputFile.get(c);
            std::bitset<8> charBin(c);
            threeByteString += charBin.to_string();
        }

        //threeByteString contains two 12 bit codes, now process these
        for(int i=0;i<2;i++)
        {
            //evaluate key for 12 bit code
            std::bitset<12> codeBin(threeByteString.substr(i*bits,bits));
            charKey = codeBin.to_ulong();

            //see if key is in dictionary or not
            if(dictionary.find(charKey) != dictionary.end())
            {
                currentString = dictionary[charKey];
                outputFile << currentString;
            } else {
                currentString = prevString + prevString.substr(0,1);
                outputFile << currentString;
            }

            //add running string to dictionary
            if(!prevString.empty()){
                dictionary.insert({dictionarySize,prevString+currentString.substr(0,1)});
                dictionarySize++;
            }

            prevString = currentString;

            //reset dictionary if too big
            if(dictionarySize>=pow(2,bits))
            {
                initialiseDictionary();
                dictionarySize = dictionary.size();
            }
        }
    }

    //may have a 16 bit code left, if so do
    //the same as above but with a 16 bit code
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
        //since this is the last code, it must be in the dictionary
        currentString = dictionary[charKey];
        outputFile << currentString;
    }
    inputFile.close();
    outputFile.close();
}
