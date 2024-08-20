//
//  counting_store.hpp
//  LiftoffCode
//
//  Created by Vinay Chaudhary on 8/15/24.
//

#ifndef counting_store_hpp
#define counting_store_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

class CountingStore {
public:
    CountingStore() = default;
    
    void Write(const std::string& name, int val);
    // TODO Should probably return optional rather than use pointer arg ..
    bool Read(const std::string& name, int* val);
    
    int CountVal(int val);
    
    void Checkpoint();
    
    bool Revert();
    
    void Save(const std::string& filename);
    
    void Load(const std::string& filename);
private:
    int current_level_ = 0;
    
    void DecrementCountMap(int val);
    void IncrementCountMap(int val);
    
    std::unordered_map<std::string, std::map<int, int>> value_map_;
    std::unordered_map<int, std::map<int,int>> count_map_;
};

#endif /* counting_store_hpp */
