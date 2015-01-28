/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file libev_connector.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/27 15:12:51
 * @brief 
 *  
 **/




#ifndef  __LIBEV_CONNECTOR_H_
#define  __LIBEV_CONNECTOR_H_

#define SOCKINFO_MAXSIZE 128


class LibevConnector {
    public:
        // ctor
        LibevConnector();

        // dtor
        ~LibevConnector();

        bool Initialize();

    private:
        bool ConfigSet(const char* host, const char* port);

    private:
        char conf_host_[SOCKINFO_MAXSIZE];
        char conf_port_[SOCKINFO_MAXSIZE];

        char set_host_[SOCKINFO_MAXSIZE];
        char set_port_[SOCKINFO_MAXSIZE];
};







#endif  //__LIBEV_CONNECTOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
