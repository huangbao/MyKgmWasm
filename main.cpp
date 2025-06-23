#include <iostream>
#include "KgmCodec.h"


int main() {
    std::cout << "Hello, World!" << std::endl;


    KgmCodec *kgmCodec = new KgmCodec();

    //    char *filepath = "D:\\ProjectUnlockMusic\\MyKgmWasm\\data\\aa.txt";
    char *filepath = "D:\\ProjectUnlockMusic\\MyKgmWasm\\data\\bb.kgm";


    std::vector<uint8_t> *result = kgmCodec->decodeKgm(filepath);
    std::cout << "解密完成：size " << result->size() << std::endl;

    writeFile("D:\\ProjectUnlockMusic\\MyKgmWasm\\data\\tmp4.flac", result);

    delete kgmCodec;
    kgmCodec = nullptr;
    return 0;


}
