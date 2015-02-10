
#SUBDIRS=src
#DIST_SUBDIRS=src

UTIL_LIB=../../../pub_util/tools/tools.h ../../../pub_util/tools/tools.cpp

COMM_LIB=../src/libev_connector.h \
		 ../src/libev_connector.cpp \
		 ../src/socket_util.h \
		 ../src/socket_util.cpp \
		 ../log/ds_log.h \
		 ../log/ds_log.cpp 

COMMON_CF = -I../../../third-64/protobuf/include/ \
		   -I../../../third-64/glog/include/ \
		   -I../../../third-64/boost/include/ \
		   -I../../../third-64/iniparser/include/ \
		   -I../../../third-64/libev/include/ \
		   -I../../../pub_util/tools/include/

COMMON_LD = -lpthread -lz -ldl -lrt \
		   ../../../third-64/protobuf/lib/*.a \
		   ../../../third-64/glog/lib/*.a \
		   ../../../third-64/iniparser/lib/*.a \
		   ../../../third-64/libev/lib/*.a \
		   ../../../third-64/boost/lib/*.a

bin_PROGRAMS = libev_server libev_client

libev_server_SOURCES = \
			  ../src/libev_server.cpp \
			  $(COMM_LIB) \
			  $(UTIL_LIB)
libev_server_CPPFLAGS = $(COMMON_CF) \
						 -I../../../third-64/leveldb/include/ \
  						 -I../../../pub_util/thread/include/
libev_server_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
libev_server_LDADD = $(COMMON_LD)


libev_client_SOURCES = \
			  ../src/libev_client.cpp \
			  $(COMM_LIB) \
			  $(UTIL_LIB)
libev_client_CPPFLAGS = $(COMMON_CF) \
  						 -I../../../pub_util/thread/include/
libev_client_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
libev_client_LDADD = $(COMMON_LD)
