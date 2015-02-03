
#SUBDIRS=src
#DIST_SUBDIRS=src

bin_PROGRAMS = rpc_client rpc_service

rpc_client_SOURCES = \
		      ../cs_sample/rpc_client.cc \
			  ../common/connection_manager.h \
			  ../common/connection_manager.cpp \
			  ../common/rpc_channel.h \
			  ../common/rpc_channel.cpp \
			  ../common/rpc_msg.pb.h \
			  ../common/rpc_msg.pb.cc \
			  ../common/rpc_util.h \
			  ../common/rpc_util.cpp \
		      ../proto/simple_rpc.pb.h \
		      ../proto/simple_rpc.pb.cc

#INCLUDES = -I../third-64/libevent/include/
#CXXFLAGS = -std=c++11 -Wall -g -fPIC
rpc_client_CPPFLAGS = -I../../../third-64/protobuf/include/
rpc_client_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
rpc_client_LDADD = -lpthread -lz -ldl -lrt  \
	               ../../../third-64/protobuf/lib/*.a 
#http_server_a_LDADD = ../third-64/libevent/lib/*.a

rpc_service_SOURCES = \
		      ../cs_sample/rpc_service.cc \
			  ../common/connection_manager.h \
			  ../common/connection_manager.cpp \
			  ../common/rpc_server.h \
			  ../common/rpc_server.cpp \
			  ../common/rpc_util.h \
			  ../common/rpc_util.cpp \
			  ../common/rpc_msg.pb.h \
			  ../common/rpc_msg.pb.cc \
		      ../proto/simple_rpc.pb.h \
		      ../proto/simple_rpc.pb.cc

#INCLUDES = -I../third-64/libevent/include/
#CXXFLAGS = -std=c++11 -Wall -g -fPIC
rpc_service_CPPFLAGS = -I../../../third-64/protobuf/include/ \
					   -I../../../util/thread/include/
rpc_service_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
rpc_service_LDADD = -lpthread -lz -ldl -lrt  \
					../../../third-64/protobuf/lib/*.a 
#
