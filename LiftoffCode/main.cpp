//
//  main.cpp
//  LiftoffCode
//
//  Created by Vinay Chaudhary on 8/15/24.
//

#include <iostream>
#include <cassert>
#include "counting_store.hpp"
#include <sstream>

#define NDEBUG

void TestCountingStore() {
    CountingStore store;
    store.Write("hello", 1);
    store.Write("hi", 2);
    
    int val;
    bool read = store.Read("hello", &val);
    assert(read);
    assert(val == 1);
    assert(store.CountVal(1) == 1);
    
    read = store.Read("hi", &val);
    assert(read);
    assert(val == 2);
    assert(store.CountVal(2) == 1);
    
    store.Write("yo", 2);
    read = store.Read("yo", &val);
    assert(read);
    assert(val == 2);
    assert(store.CountVal(2) == 2);
    
    store.Write("yo", 1);
    read = store.Read("yo", &val);
    assert(read);
    assert(val == 1);
    assert(store.CountVal(2) == 1);
    assert(store.CountVal(1) == 2);
    
    store.Checkpoint();
    assert(store.CountVal(2) == 1);
    assert(store.CountVal(1) == 2);
    store.Write("yoyo", 17);
    assert(store.Read("yoyo", &val));
    assert(val == 17);
    
    store.Revert();
    assert(store.CountVal(2) == 1);
    assert(store.CountVal(1) == 2);
    assert(!store.Read("yoyo", &val));
    
    assert(!store.Revert());
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ///std::cout << "Hello, World!\n";
    TestCountingStore();
    CountingStore store;
    for (std::string line; std::getline(std::cin, line);) {
        std::stringstream line_stream(line);
        std::string command;
        line_stream >> command;
        if (command == "REVERT") {
            store.Revert();
        } else if (command == "COMMIT") {
            store.Checkpoint();
        } else if (command == "WRITE") {
            std::string write_string;
            line_stream >> write_string;
            int write_val;
            line_stream >> write_val;
            store.Write(write_string, write_val);
        } else if (command == "READ") {
            int val;
            std::string read_string;
            line_stream >> read_string;
            if (store.Read(read_string, &val)) {
                std::cout << val << std::endl;
            } else {
                std::cout << "Not found" << std::endl;
            }
        } else if (command == "COUNTVAL") {
            int count_val;
            line_stream >> count_val;
            std::cout << store.CountVal(count_val) << std::endl;
        }
    }
    return 0;
}
