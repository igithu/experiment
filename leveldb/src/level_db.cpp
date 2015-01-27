/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file level_db.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/08 13:54:31
 * @brief 
 *  
 **/


#include "level_db.h"

#include <leveldb/c.h>

LeveDB::LeveDB() : db_ptr_(NULL) {
    LeveDBInit();
}

LeveDB::~LeveDB() {
}

bool LeveDB::LeveDBInit() {
    options_.create_if_missing = true;
    leveldb::DB::Open(options_, "tmp/testdb", &db_ptr_);
    if (NULL == db_ptr_) {
        fprintf(stderr, "level_db init error! db_ptr_ is null!\n");
        return false;
    }
    return true;
}

bool LeveDB::Put(const char* key, const char* value) {
    if (NULL == key || NULL == value /*|| "" == *key || "" == *value*/) {
        //fprintf(stderr, "put exception key or value is null");
        return false;
    }
    if (NULL == db_ptr_) {
        fprintf(stderr, "level_db put op error! db_ptr_ is null!\n");
        return false;
    }
    leveldb::Status status = db_ptr_->Put(leveldb::WriteOptions(), key, value);
    if (!status.ok()) {
        fprintf(stderr, "put op failed!\n");
        return false;
    }
    return true;
}

bool LeveDB::Get(const char* key, std::string& value) {
    if (NULL == key /*|| "" = *key*/) {
        //fprintf(stderr, "key is null");
        return false;
    }
    if (NULL == db_ptr_) {
        fprintf(stderr, "level_db get op error! db_ptr_ is null!\n");
        return false;
    }
    leveldb::Status status = db_ptr_->Get(leveldb::ReadOptions(), key, &value);
    if (!status.ok()) {
        fprintf(stderr, "get op failed!\n");
        return false;
    }
    return true;
}

bool LeveDB::Delete(const char* key) {
    if (NULL == key /*|| "" = *key*/) {
        //fprintf(stderr, "key is null");
        return false;
    }
    if (NULL == db_ptr_) {
        fprintf(stderr, "level_db delete op error! db_ptr_ is null!\n");
        return false;
    }
    leveldb::Status status = db_ptr_->Delete(leveldb::WriteOptions(), key);
    if (!status.ok()) {
        fprintf(stderr, "delete op failed!\n");
        return false;
    }
    return true;
}









/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
