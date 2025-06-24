#include <iostream>
#include "KgmCodec.h"


int main() {
    std::cout << "Hello, World!" << std::endl;


    KgmCodec *kgmCodec = new KgmCodec();

    //    char *filepath = "D:\\ProjectUnlockMusic\\MyKgmWasm\\data\\aa.txt";
    char *filepath = "D:\\ProjectUnlockMusic\\MyKgmWasm\\data\\bb.kgm";


    DecodeResult *result = kgmCodec->decodeKgm(filepath);
    std::cout << "解密完成：size " << result->data->size() << std::endl;
    char outputPath[50] = "D:\\ProjectUnlockMusic\\MyKgmWasm\\data\\tmp4.";
    strcat(outputPath, result->ext);
    //char *outputPath = "D:\\ProjectUnlockMusic\\MyKgmWasm\\data\\tmp4." + result->ext;
    writeFile(outputPath, result->data);

    std::cout << "保存文件：" << outputPath << std::endl;

    delete result;
    delete kgmCodec;
    kgmCodec = nullptr;

    std::cout << "end" << std::endl;
    return 0;


}
