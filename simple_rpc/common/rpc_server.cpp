/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rpc_server.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/24 00:10:22
 * @brief 
 *  
 **/

#include "rpc_server.h"

//#include <string.h>
#include <string>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>

#include "rpc_util.h"

namespace simple_rpc {

//using std::string;

#define MAXEVENTS 100

RpcServer::RpcServer() {
    Initialize();
}

RpcServer::~RpcServer() {
    for (HashMap::iterator iter = method_hashmap_.begin(); 
         iter != method_hashmap_.end();
         ++iter) {
        RpcMethod* rpc_method_ptr = iter->second;
        if (NULL != rpc_method_ptr) {
            delete rpc_method_ptr;
            rpc_method_ptr = NULL;
        }
    }
}

bool RpcServer::Initialize() {
    // should read from config file
    // strcpy(host_, "127.0.0.1");
    // strcpy(port_, "9998");
    return true;
}

bool RpcServer::RegisteService(Service* reg_service) {
    const ServiceDescriptor* descriptor = reg_service->GetDescriptor();
    for (int32_t i = 0; i < descriptor->method_count(); ++i) {
        const MethodDescriptor* method_desc = descriptor->method(i);
        const Message* request = &reg_service->GetRequestPrototype(method_desc);
        const Message* response = &reg_service->GetResponsePrototype(method_desc);

        RpcMethod* rpc_method =
            new RpcMethod(reg_service, request, response, method_desc);

        uint32_t hash_code = BKDRHash(method_desc->full_name().c_str());

        HashMap::iterator ret_iter = method_hashmap_.find(hash_code);
        if (ret_iter == method_hashmap_.end()) {
            method_hashmap_.insert(std::make_pair(hash_code, rpc_method));
        } else {
            delete ret_iter->second;
            method_hashmap_[hash_code] = rpc_method;
        }
    }
   return true; 
}

void RpcServer::Run() {

    int32_t listenfd = connection_manager_.TcpListen();
    if (connection_manager_.EpollInit(listenfd) < 0) {
        fprintf(stderr, "epollInit failed!\n");
        return;
    }
    struct epoll_event events[MAXEVENTS];

    while (true) {
        int32_t ready = connection_manager_.EpollWait(MAXEVENTS, events);
        for (int32_t i = 0; i < ready; ++i) {
            int32_t events_fd = events[i].data.fd;
            uint32_t cur_events = events[i].events;
            if (events_fd == listenfd) {
                printf("new connection\n");
                connection_manager_.EpollNewConnect(listenfd);
            } else if (cur_events & EPOLLIN) {
                Message* request;
                RpcMessage recv_rpc_msg;

                if (!GetMethodRequest(events_fd, recv_rpc_msg, request)) {
                    fprintf(stderr, "get method request failed!\n");
                    ErrorSendMsg(events_fd, "get method request failed!");
                    continue;
                }

                uint32_t hash_code = recv_rpc_msg.head_code();
                HashMap::iterator method_iter = method_hashmap_.find(hash_code);
                if (method_iter == method_hashmap_.end() || NULL == method_iter->second) {
                    fprintf(stderr, "find hash code failed! %u\n", hash_code);
                    ErrorSendMsg(events_fd, "find hash code failed!");
                    continue;
                }
                RpcMethod* rpc_method = method_iter->second;
                request = rpc_method->request->New();
                if (!request->ParseFromString(recv_rpc_msg.body_msg())) {
                    fprintf(stderr, "parse body msg error!");
                    ErrorSendMsg(events_fd, "parse body msg error!");
                    delete request;
                    continue;
                }

                const MethodDescriptor* method_desc = rpc_method->method;
                Message* response = rpc_method->response->New();
                rpc_method->service->CallMethod(method_desc, NULL, request, response, NULL);
    
                if (!SendFormatStringMsg(events_fd, response)) {
                    fprintf(stderr, "send format response failed!\n");
                    ErrorSendMsg(events_fd, "send format response failed!");
                }
                delete request;
                delete response;
            }
        }
    }
}

bool RpcServer::GetMethodRequest(int32_t events_fd, RpcMessage& recv_rpc_msg, Message* request) {
    string msg_str;
    if (connection_manager_.EpollRecvMsg(events_fd, msg_str) < 0) {
        fprintf(stderr, "connection_manager recv msg failed!");
        return false;
    }

    if (!recv_rpc_msg.ParseFromString(msg_str)) {
        fprintf(stderr, "parse from string msg failed!");
        return false;
    }
    return true;
}

bool RpcServer::SendFormatStringMsg(int32_t events_fd, Message* response) {
    string response_str;
    if (!response->SerializeToString(&response_str)) {
        fprintf(stderr, "response_str SerializeToString failed!\n");
        return false;
    }

    RpcMessage send_rpc_msg;
    send_rpc_msg.set_head_code(200);
    send_rpc_msg.set_body_msg(response_str);
    string send_str;
    if (!send_rpc_msg.SerializeToString(&send_str)) {
        fprintf(stderr, "send_str SerializeToString failed!\n");
        return false;
    }
    connection_manager_.EpollSendMsg(events_fd, send_str);

    return true;
}

bool RpcServer::ErrorSendMsg(int32_t events_fd, const string& error_msg) {
    RpcMessage error_rpc_msg;
    // 500 means internal error
    error_rpc_msg.set_head_code(500);
    error_rpc_msg.set_body_msg(error_msg);

    string err_msg_str;
    if (!error_rpc_msg.SerializeToString(&err_msg_str)) {
        fprintf(stderr, "error send error!");
        return false;
    }
    connection_manager_.EpollSendMsg(events_fd, err_msg_str);
    return true;
}

}  // end of namespace simple_rpc





/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
