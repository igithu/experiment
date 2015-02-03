/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rpc_channel.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/23 16:37:20
 * @brief 
 *  
 **/




#ifndef  __RPC_CHANNEL_H_
#define  __RPC_CHANNEL_H_


#include <google/protobuf/service.h>
#include <google/protobuf/message.h>

#include "connection_manager.h"

namespace simple_rpc {

using namespace google::protobuf;

class Channel : public RpcChannel {
    public:
        Channel(const string& host, int32_t port);

        virtual ~Channel();

        virtual void CallMethod(const MethodDescriptor* method,
                                RpcController* controll,
                                const Message* request,
                                Message* response,
                                Closure* done);

        void Close();
    
    private:

        ConnectionManager connection_manager_;
};


}  // end of namespace simple_rpc



#endif  //__RPC_CHANNEL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
