#!/bin/bash


export LD_LIBRARY_PATH=:/home/users/aishuyu/.jumbo/lib:/usr/local/lib:/home/users/aishuyu/open_src/demo/third-64/leveldb/lib
#g++ leveldb_test.cpp -lleveldb -lpthread -I../../../third-64/leveldb/include/ -L../../../third-64/leveldb/lib
g++ leveldb_test.cpp ../src/common_db.h ../src/level_db.h ../src/level_db.cpp -lleveldb -lpthread -I../../../third-64/leveldb/include/ -L../../../third-64/leveldb/lib
