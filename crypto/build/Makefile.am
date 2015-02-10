
#SUBDIRS=src
#DIST_SUBDIRS=src


COMMON_CF = -I../../../third-64/crypto/include/

COMMON_LD = -lpthread -lz -ldl -lrt \
		    ../../../third-64/crypto/lib/*.a

bin_PROGRAMS = md5
md5_SOURCES = ../src/md5_example.cpp

md5_CPPFLAGS = $(COMMON_CF)
md5_LDFLAGS = -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
md5_LDADD = $(COMMON_LD)


