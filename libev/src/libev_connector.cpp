/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file libev_connector.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/27 15:35:38
 * @brief 
 *  
 **/


#include "libev_connector.h"

#include "socket_util.h"


LibevConnector::LibevConnector() : epoller_(NULL) {
}

LibevConnector::~LibevConnector() {
    if (NULL = epoller_) {
        ev_loop_destroy(epoller_);
    }
}

bool LibevConnector::Initialize(const char *host, const char *port) {
    int32_t listenfd = TcpListen(host, port);
    if (listenfd < 0) {
        return false;
    }
    
    epoller_ = ev_loop_new(EVBACKEND_EPOLL | EVFLAG_NOENV);
    struct ev_io socket_watcher;

    ev_io_init(&socket_watcher, LibevConnector::ProcessCb, listenfd, EV_READ);
    ev_io_start(epoller_, &socket_watcher);

    return true;
}

void LibevConnector::LibevLoop() {
    
    while (true) {
        ev_loop(epoller_, 0);
    }
}

bool LibevConnector::ConfigSet() {
    uint32_t conf_host_size = strlen(conf_host_);
    uint32_t conf_port_size = strlen(conf_port_);

    uint32_t param_host_size = strlen(host);
    uint32_t param_port_size = strlen(port);


    if (conf_host_size > SOCKINFO_MAXSIZE || param_host_size > SOCKINFO_MAXSIZE) {
        DS_LOG(ERROR, "invalid host  conf host: %s, param host: %s\n",  conf_host_, host);
        return false;
    }
    if (conf_port_size > SOCKINFO_MAXSIZE || param_port_size > SOCKINFO_MAXSIZE) {
        DS_LOG(ERROR, "invalid port  conf port: %s, param port: %s\n", conf_port_, port);
        return false;
    }

    // the user set is priority
    if (0 != param_host_size && 0 != param_port_size) {
        strcpy(set_host_, host);
        strcpy(set_port_, port);
    } else if (0 != conf_host_size && 0 != conf_port_size) {
        strcpy(set_host_, conf_host_);
        strcpy(set_port_, conf_port_); 
    } else {
        return false;
    }
 
    return true;
} 









/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
