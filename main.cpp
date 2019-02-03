#include "LZW_decoder.h"

using namespace std;

int main()
{
    string inputFile;
    //example input
    inputFile = "compressedfile3.z";

    LZWdecode test;

    //writes to compressedfile3_decoded.txt
    test.decompress(inputFile);

    return 0;
}
