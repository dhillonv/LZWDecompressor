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

    std::ofstream outputFile;
    outputFile.open(fileName.substr(0,fileName.find(".")+1) + "_decoded.txt");

    //find file size
    unsigned int numBytes = inputFile.tellg();
    unsigned int numCodes = (8*numBytes)/bits;
    char c;
    std::string prevString, currentString;
    unsigned int long charKey;
    std::string threeByteString; //stores two or three bytes

    if(!(8*numBytes % 12 == 0)){
        numCodes--;
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
            currentString = dictionary[charKey];
            //std::cout << charKey << std::endl;
            //outputFile << charKey << " ";
            outputFile << currentString;
            //add key to dictionary
            if(!prevString.empty()){
                //std::cout << "Adding: " << dictionarySize << ", " << prevString+currentString << std::endl;
                //dictionary.insert({dictionarySize,prevString+currentString});
                dictionary.insert({dictionarySize,prevString+currentString.substr(0,1)});
                dictionarySize++;
            }
            //std::cout << charKey << std::endl; //dictionary[charKey];
            //output character to file

            //std::cout << dictionary[charKey] << std::endl;
            //reset if dictionary is too big
            if(dictionarySize>=pow(2,bits))
            {
                initialiseDictionary();
                dictionarySize = dictionary.size();
                prevString.clear();
            } else {
                prevString = dictionary[charKey];
            }
        }
    }

    //may have a 16 bit code left
    if(inputFile.get(c)){
    std::cout << "we have not finished" << std::endl;
    }

    outputFile.close();
    inputFile.close();
}
