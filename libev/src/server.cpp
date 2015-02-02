/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file server.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/02 15:52:17
 * @brief 
 *  
 **/


#include "libev_connector.h"

int main() {
    LibevConnector libev_server;
    libev_server.Initialize("127.0.0.1", 9996);
    libev_server.LibevLoop();
    return 0;
};













/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
