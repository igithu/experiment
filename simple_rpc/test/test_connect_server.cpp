/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_connect_server.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/02 10:57:07
 * @brief 
 *  
 **/


#include "../common/connection_manager.h"

using namespace simple_rpc;

#define MAXEVENTS 100

int main() {
    // socklen_t   addrlen;
    ConnectionMananger connect_manager;
    int32_t listenfd = connect_manager.TcpListen();

    if (listenfd < 0) {
        return 0;
    }

    struct epoll_event events[MAXEVENTS];
    connect_manager.EpollInit(listenfd);
                                      
    string msg_str;                   
                                      
    while (true) {                    
        int32_t ready = connect_manager.EpollWait(MAXEVENTS, events);
        printf("Test ready %d\n", ready);
                                      
         for (int32_t i = 0; i < ready; ++i) {
             if (events[i].data.fd == listenfd) {
                 printf("start new new connect!\n");
                 connect_manager.EpollNewConnect(listenfd);
             } else if (events[i].events & EPOLLIN) {
                 printf("start recv msg\n");
                 connect_manager.EpollRecvMsg(events[i].data.fd, msg_str);
                 printf("Server recv msg is %s\n", msg_str.c_str());
                 connect_manager.EpollSendMsg(events[i].data.fd, msg_str);
             }
         }
    }
}


              





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
