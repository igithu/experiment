/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file md5.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/09 13:36:45
 * @brief 
 *  
 **/

#include <stdio.h>

#include <string>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#pragma comment (lib,"cryptlib.lib")

using namespace CryptoPP;
using namespace std;


int main() {

    byte msg[] = "HelloCrypto";
    byte n_msg[16];

    Weak::MD5 md5;
    string digest;

    md5.Update(msg, 11);
    md5.Final(n_msg);

    for (int32_t i = 0; i < 16; ++i) {
        printf("%02X", n_msg[i]);
    }
    printf("\n");
    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
