#ifndef _BETTER_LOCKED_HASH_TABLE_H_
#define _BETTER_LOCKED_HASH_TABLE_H_

#define TABLE_SIZE 1000
#define N 4

#include <iostream>
#include <mutex>
#include <thread>
#include "hash_table.h"
#include "linked_list.h"

class better_locked_hash_table : public hash_table {

    // TODO
    linked_list* table;
    std::mutex global_mutex[N];

    // TODO 
    public:
        better_locked_hash_table(){
            // TODO
            this->table = new linked_list[TABLE_SIZE]();
            // TODO
        }

        bool contains(int key){
            // TODO
            std::lock_guard<std::mutex> lock(global_mutex[key%N]);
            int hash_value = key%TABLE_SIZE;

            return this->table[hash_value].contains(key);

            // TODO
        }

        
        bool insert(int key) {
            // TODO
            // lock guard
            std::lock_guard<std::mutex> lock(global_mutex[key%N]);
            // move to left of key
            int hash_value = key%TABLE_SIZE;

            return this->table[hash_value].insert(key);

            // TODO
        }

        bool remove(int key) {
            // TODO
            // lock guard
            std::lock_guard<std::mutex> lock(global_mutex[key%N]);
            // if empty do nothing
            int hash_value = key%TABLE_SIZE;

            return this->table[hash_value].remove(key);
            // TODO
        }
};

#endif