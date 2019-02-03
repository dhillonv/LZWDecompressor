#include "LZW_decoder.h"

using namespace std;

int main()
{
    string inputFile;
    lzwText test;

    //example input
    inputFile = "compressedfile3.z";

    //writes to compressedfile3_decoded.txt
    test.decompress(inputFile);

    return 0;
}
