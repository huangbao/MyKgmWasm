//
// Created by hb on 2025/6/23.
//

#ifndef MYKGMWASM_KGMCODEC_H
#define MYKGMWASM_KGMCODEC_H

#include <vector>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include "KgmUtils.h"

// 每次可以处理 2M 的数据
static int DECRYPTION_BUF_SIZE = 2 * 1024 * 1024;

class KgmCodec {
public:
    KgmCodec();

    ~KgmCodec();


    std::vector<uint8_t> * decodeKgm( char *filepath);

    void Decrypt(uint8_t *fileData, size_t blobSize, size_t offset);

     uint8_t getMask(size_t pos);

    size_t PreDec(uint8_t *fileData, size_t size, bool iV);

    std::vector<uint8_t> key;
    bool isVpr = false;


};


#endif //MYKGMWASM_KGMCODEC_H
