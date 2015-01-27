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

    public:
        //  wrapper socket, imitate the <Unix socket> code
        int32_t Socket(int32_t family = 0, int32_t type = 0, int32_t protocol = 0);

        int32_t TcpListen(const char *host = "", const char *port = "");

        int32_t Accept(int fd, struct sockaddr_in &sa, int32_t addrlen);

        int32_t RecvMsg(int32_t fd, std::string& recv_msg_str);

        int32_t SendMsg(int32_t fd, std::string& send_msg_str);

        bool SetNonBlock(int32_t sock);

    private:
        bool ConfigSet(const char* host, const char* port);


    private:
        char conf_host_[SOCKINFO_MAXSIZE];
        char conf_port_[SOCKINFO_MAXSIZE];

        char set_host_[SOCKINFO_MAXSIZE];
        char set_port_[SOCKINFO_MAXSIZE];

        int32_t family_;
        int32_t sock_type_;

};







#endif  //__LIBEV_CONNECTOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
