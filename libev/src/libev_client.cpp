/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file libev_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/03 14:26:20
 * @brief 
 *  
 **/

#include <stdio.h>

#include <string>

#include "socket_util.h"

using std::string;

int main() {
    int32_t connect_fd = TcpConnect("127.0.0.1", "9996");
    printf("Start libev client\n");

    printf("Start libev client sendmsg \n");
    string recv_str = "libev client call libev echo server!";
    SendMsg(connect_fd, recv_str);

    printf("Start libev client recvmsg \n");
    string rev_str;
    RecvMsg(connect_fd, rev_str);

    printf("Echo content: \n");
    printf("            %s \n", rev_str.c_str());
    return 0;
}










/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
