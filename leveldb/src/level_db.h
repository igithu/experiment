/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file level_db.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/08 13:44:26
 * @brief 
 *  
 **/




#ifndef  __LEVEL_DB_H_
#define  __LEVEL_DB_H_

#include <leveldb/db.h>

#include "common_db.h"

class LeveDB : public CommonDB {

    public:

        LeveDB();

        ~LeveDB();

        virtual bool Put(const char* key, const char* value);

        virtual bool Get(const char* key, std::string& value);

        virtual bool Delete(const char* key);

    private:
         bool LeveDBInit();

    private:
        leveldb::Options options_;

        leveldb::DB* db_ptr_;

};














#endif  //__LEVEL_DB_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
