//
//  counting_store.cpp
//  LiftoffCode
//
//  Created by Vinay Chaudhary on 8/15/24.
//

// a -> [[0: 1], [1: 2]]
// CHECKPOINT
// b -> [(2, 1)]
// CHECKPOINT
// c -> (3, 2)
// CHECKPOINT

// 1 -> [{0, 2}, {3, 3}]
//

#include "counting_store.hpp"

#include <string>
#include <cassert>

void CountingStore::UpdateCountMap(std::map<int, int>& count_map_value, int val) {
    auto lower_bound_value = count_map_value.lower_bound(current_level_);
    if (lower_bound_value == count_map_value.end()) {
        count_map_value.emplace(current_level_, 
                                std::prev(count_map_value.end())->second + val);
    } else if (lower_bound_value->first == current_level_) {
        lower_bound_value->second += val;
    }
}

void CountingStore::DecrementCountMap(int val) {
    auto count_map_value = count_map_.find(val);
    assert (count_map_value != count_map_.end());
    UpdateCountMap(count_map_value->second, -1);
}

void CountingStore::IncrementCountMap(int val) {
    auto count_map_value = count_map_.find(val);
    if (count_map_value == count_map_.end()) {
        count_map_[val][current_level_] = 1;
        return;
    }
    UpdateCountMap(count_map_value->second, 1);
}

void CountingStore::Write(const std::string& name, int val) {
    auto all_values = value_map_.find(name);
    if (all_values != value_map_.end()) {
        auto upper_bound_value = all_values->second.lower_bound(current_level_);
        if (upper_bound_value == all_values->second.end()) {
            // In a previous checkpoint but not this one, have to subtract out.
            DecrementCountMap(std::prev(all_values->second.end())->second);
        } else if (upper_bound_value->first == current_level_) {
            // In this checkpoint, need to subtract out.
            DecrementCountMap(upper_bound_value->second);
        } else {
            // In later checkpoint, doesn't matter.
        }
    }
    
    value_map_[name][current_level_] = val;
    IncrementCountMap(val);
}

bool CountingStore::Read(const std::string& name, int* val) {
    auto result = value_map_.find(name);
    if (result == value_map_.end()) {
        return false;
    }
    
    auto checkpoint_result = result->second.lower_bound(current_level_);
    if (checkpoint_result == result->second.end()) {
        *val = std::prev(result->second.end())->second;
        return true;
    } else if (checkpoint_result->first == current_level_) {
        *val = checkpoint_result->second;
        return true;
    }

    return false;
}

int CountingStore::CountVal(int val) {
    auto result = count_map_.find(val);
    if (result == count_map_.end()) {
        return 0;
    }
    
    auto checkpoint_result = result->second.lower_bound(current_level_);
    if (checkpoint_result == result->second.end()) {
        return std::prev(result->second.end())->second;
    } else if (checkpoint_result->first == current_level_) {
        return checkpoint_result->second;
    }

    return 0;
}

void CountingStore::Checkpoint() {
    current_level_++;
}

bool CountingStore::Revert() {
    if (current_level_ == 0) {
        return false;
    }
    current_level_--;
    return true;
}

void CountingStore::Save(const std::string& filename) {
    // TODO if time.
}

void CountingStore::Load(const std::string& filename) {
    // TODO if time.
}

