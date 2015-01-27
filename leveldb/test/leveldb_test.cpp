/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file leveldb_test.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/08 13:01:31
 * @brief 
 *  
 **/

#include <leveldb/db.h>

#include <string>
#include <iostream>

#include "../src/common_db.h"
#include "../src/level_db.h"

using namespace std;
 
int main()
{
/*
    leveldb::DB *db = NULL;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::DB::Open(options, "tmp/testdb", &db);
     
    string key = "MyKey29", value = "Hello World!", result;

    if (NULL == db) {
        cout << "error" << endl;
        return 0;
    }
    db->Put(leveldb::WriteOptions(), key.c_str(), value.c_str());
    db->Get(leveldb::ReadOptions(), key.c_str(), &result);
    db->Delete(leveldb::WriteOptions(), key.c_str());
    cout << "result = " << result << endl;
    delete db;
*/
    CommonDB* common_db_ptr = new LeveDB();
    common_db_ptr->Put("kettest", "valuetest");
    string ret;
    common_db_ptr->Get("kettest", ret);
    cout << ret << endl;
    delete common_db_ptr;
    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
