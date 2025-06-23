//
// Created by hb on 2025/6/23.
//


#include "KgmCodec.h"

KgmCodec::KgmCodec() {
    key = std::vector<uint8_t>(17);
    isVpr = false;
}

KgmCodec::~KgmCodec() {

}

//void KgmCodec::Decrypt(uint8_t *fileData, size_t blobSize, size_t offset) {
//    for (size_t i = 0; i < blobSize; ++i) {
//        uint8_t med8 = key[(i + offset) % 17] ^ fileData[i];
//        med8 ^= (med8 & 0xf) << 4;
//
//        uint8_t msk8 = getMask(i + offset);
//        msk8 ^= (msk8 & 0xf) << 4;
//        fileData[i] = med8 ^ msk8;
//
//        if (isVpr) {
//            fileData[i] ^= VprMaskDiff[(i + offset) % 17];
//        }
//    }
//}
void KgmCodec::Decrypt(uint8_t *blockData, size_t blobSize, size_t offset) {

    for (size_t i = 0; i < blobSize; ++i) {
        uint8_t med8 = this->key[(i + offset) % 17] ^ blockData[i];
        med8 ^= (med8 & 0xf) << 4;

        uint8_t msk8 = this->getMask(i + offset);
        msk8 ^= (msk8 & 0xf) << 4;
        blockData[i] = med8 ^ msk8;

        if (this->isVpr) {
            blockData[i] ^= VprMaskDiff[(i + offset) % 17];
        }
    }
}

uint8_t KgmCodec::getMask(size_t pos) {
    size_t offset = pos >> 4;
    uint8_t value = 0;
    while (offset >= 0x11) {
        value ^= table1[offset % 272];
        offset >>= 4;
        value ^= table2[offset % 272];
        offset >>= 4;
    }

    return MaskV2PreDef[pos % 272] ^ value;
}

size_t KgmCodec::PreDec(uint8_t *fileData, size_t size, bool iV) {
    uint32_t headerLen = *(uint32_t *) (fileData + 0x10);
    memcpy(key.data(), (fileData + 0x1C), 0x10);
    key[16] = 0;
    isVpr = iV;
    return headerLen;
}

std::vector<uint8_t> *KgmCodec::decodeKgm(char *filepath) {

    std::vector<uint8_t> *result = new std::vector<uint8_t>;


    int fileSize = 0;

    uint8_t *fileBuf = readFile(filepath, &fileSize);


    std::cout << "fileSize  " << (fileSize / 1024 / 1024) << "M" << std::endl;

    const char *ext= getExt(filepath);

    int headerLen = this->PreDec(fileBuf, fileSize,strcmp(ext, "vpr") == 0);

    std::cout << "headerLen " << headerLen << std::endl;


    int bufSize = fileSize - headerLen;
    uint8_t *buf = new uint8_t[bufSize];

    memcpy(buf, fileBuf + headerLen, bufSize);

    int offset = 0;

    int bytesToDecrypt = bufSize;

    uint8_t *blockData = new uint8_t[DECRYPTION_BUF_SIZE];

    int aaa = 0;


    while (bytesToDecrypt > 0) {

        // 解密一些片段

        memset(blockData, 0, DECRYPTION_BUF_SIZE);

        int blockSize = getMin(bytesToDecrypt, DECRYPTION_BUF_SIZE);

        //std::cout << "blockSize " << blockSize << std::endl;

        memcpy(blockData, buf + offset, blockSize);

        this->Decrypt(blockData, blockSize, offset);


        offset += blockSize;
        bytesToDecrypt -= blockSize;

        for (int i = 0; i < blockSize; ++i) {
            result->push_back(blockData[i]);
        }
        aaa++;


    }


    delete[] blockData;
    blockData = nullptr;

    delete[] buf;
    buf = nullptr;

    delete[] fileBuf;
    fileBuf = nullptr;

    return result;
}
