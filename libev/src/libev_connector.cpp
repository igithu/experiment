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


LibevConnector::LibevConnector() : family_(AF_UNSPEC), sock_type_(SOCK_STREAM) {
}

LibevConnector::~LibevConnector() {
}

bool LibevConnector::Initialize() {
    return true;
}

int32_t LibevConnector::Socket(int32_t family, int32_t type, int32_t protocol) {
    if (family != 0) {
        family_ = family;
    }

    if (type != 0) {
        sock_type_ = type;
    }

    int32_t fd = -1;
    if ((fd = socket(family, type, protocol)) < 0) {
        return -1;
    }
    return fd;
}

int32_t LibevConnector::TcpListen(const char *host, const char *port) {
    if (!ConfigSet(host, port)) {
        return -1;
    }

    int listenfd;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = family_;
    hints.ai_socktype = sock_type_;

    if ((getaddrinfo(set_host_, set_port_, &hints, &res)) != 0) {  
        DS_LOG(ERROR, "tcp_connect error for %s, %s", set_host_, set_port_);
        return -1;
    }

    ressave = res;
    const int on = 1;
    do {
        if (NULL == res) {
            return -1;
        }
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0) {
            continue;       /* error, try next one */
        }
        
        if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
            DS_LOG(ERROR, "setsockopt error listenfd %d", listenfd);
            return -1;
        }

        SetNonBlock(listenfd);
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0) {
            break;
        }
        close(listenfd);    
    } while ((res = res->ai_next) != NULL);

    if (res == NULL) {
        return -1;
    }

    if (listen(listenfd, 20/*LISTENQ*/) < 0) {
        DS_LOG(ERROR, "listen error listenfd is %d\n", listenfd);
        return -1;
    }


    // if (addrlenp) {
    //     *addrlenp = res->ai_addrlen;    /* return size of protocol address */
    // }

    freeaddrinfo(ressave);
    return listenfd;

}

int32_t LibevConnector::TcpConnect(const char *host, const char *port) {
    if (!ConfigSet(host, port)) {
        return -1;
    }

    int32_t  sockfd;
    struct addrinfo hints, *res, *ressave;
       
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = family_;
    hints.ai_socktype = sock_type_;

    if ((getaddrinfo(set_host_, set_port_, &hints, &res)) != 0) {  
        DS_LOG(ERROR,"tcp_connect error for %s, %s", set_host_, set_port_);
        return -1;
    }
    
    ressave = res;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0) {
            continue;
        }
        
        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
            break;
        }
        close(sockfd);  /* ignore this one */
    } while ( (res = res->ai_next) != NULL);
    
    if (res == NULL) {    /* errno set from final connect() */
        DS_LOG(ERROR, "tcp_connect error!");
        return -1;
    }
    freeaddrinfo(ressave);
    return sockfd;

}

int32_t LibevConnector::Accept(int fd, struct sockaddr_in &sa, int32_t addrlen) {
    int32_t new_fd;
    do {
        new_fd = accept(fd, (struct sockaddr *) &sa, (socklen_t *) &addrlen);

        if (new_fd < 0) {
#ifdef  EPROTO
            if (errno == EPROTO || errno == ECONNABORTED)
#else
            if (errno == ECONNABORTED)
#endif
                continue;
        }

    } while (false);
    return new_fd;

}

int32_t LibevConnector::RecvMsg(int32_t fd, std::string& recv_msg_str) {
    recv_msg_str = "";

    const uint32_t MAXBUFLEN = 2048 * 2;
    char buf[MAXBUFLEN];
    memset(buf, 0, MAXBUFLEN);

    do {
        int32_t buf_len = recv(fd, buf, sizeof(buf) + 1, 0);
        if (buf_len < 0) {
            if (EAGAIN == errno || EINTR == errno) {
                break;
            } else {
                return -1;
            }
        } else if (0 == buf_len) {
            break;
        }


        if (buf_len > 0) {
            string new_buf(buf);
            recv_msg_str.append(new_buf);
            memset(buf, 0, MAXBUFLEN);
            continue;
        }
    } while (true);

    return 0;

}

int32_t LibevConnector::SendMsg(int32_t fd, std::string& send_msg_str) {
    int32_t send_size = send_msg_str.size();
    const char* send_ptr = send_msg_str.c_str();

    do {
        int32_t buf_len = send(fd, send_ptr, send_size + 1, 0);
        if (buf_len < 0) {
            if (EINTR == errno) {
                DS_LOG(ERROR, "send error errno is EINTR");
                return -1;
            } 
            if (EAGAIN == errno) {
                sleep(1);
                continue;
            }
            return -1;
        }
        if (buf_len >= send_size) {
            return buf_len;
        }

        send_size -= buf_len;
        send_ptr += buf_len;
    } while(send_size > 0);

    return 0;
}   

bool LibevConnector::SetNonBlock(int32_t sock) {
    int32_t opts = fcntl(sock, F_GETFL);

    if (opts < 0) {
        DS_LOG(ERROR, "set non block failed! fcntl(sock,GETFL).");
        return false;
    }

    opts = opts | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0) {
        DS_LOG(ERROR, "set non block failed! fcntl(sock,GETFL).");
        return false;
    }
    return true;
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
