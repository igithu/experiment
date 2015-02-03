/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rpc_server.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/23 16:49:42
 * @brief 
 *  
 **/




#ifndef  __RPC_SERVER_H_
#define  __RPC_SERVER_H_

#include <ext/hash_map>

#include <google/protobuf/service.h>

#include "connection_manager.h"
#include "rpc_msg.pb.h"
#include "thread.h"

using namespace PUBLIC_UTIL;
using namespace google::protobuf;
using __gnu_cxx::hash_map;


namespace simple_rpc {


struct RpcMethod {
    RpcMethod(Service* p_service, const Message* p_req, const Message* p_rep, const MethodDescriptor* p_meth)
        : service(p_service), request(p_req), response(p_rep), method(p_meth){
    }

    Service* service;
    const Message* request;
    const Message* response;
    const MethodDescriptor* method;
};

typedef hash_map<uint32_t, RpcMethod*> HashMap;

// single thread
class RpcServer : public Thread  {
    public:
        RpcServer();

        ~RpcServer();

        virtual void Run();

        bool RegisteService(Service* reg_service);

    private:

        bool Initialize();

        bool GetMethodRequest(int32_t events_fd, RpcMessage& recv_rpc_msg, Message* request);

        bool SendFormatStringMsg(int32_t events_fd, Message* response);

        bool ErrorSendMsg(int32_t events_fd, const string& error_msg);
    private:

        HashMap method_hashmap_;

        ConnectionManager connection_manager_;

};

}  // end of namespace simple_rpc








#endif  //__RPC_SERVER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
