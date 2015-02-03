/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_connect_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/28 15:24:11
 * @brief 
 *  
 **/


#include "../common/connection_manager.h"

using namespace simple_rpc;

int main() {
    
    ConnectionMananger connection_manager;

    int32_t conn_fd = connection_manager.TcpConnect("127.0.0.1", "9988");

    string msg_str = "Hello!!TTTTTT";
    string ret_str = "";
    connection_manager.SendMsg(conn_fd, msg_str);
    connection_manager.RecvMsg(conn_fd, ret_str);

    printf("The echo ret %s\n", ret_str.c_str());

    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
