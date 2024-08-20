//
//  main.cpp
//  LiftoffCode1
//
//  Created by Vinay Chaudhary on 8/20/24.
//

#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>


std::vector<int> getConnections(int id) {
    static std::vector<std::vector<int>> result{{1,3}, {0,2,3,4,5}, {2, 1}, {0, 1, 5}, {1,5,6}, {1, 3, 4, 6}, {4, 5}, {}};
    if (id < 0 || id >= result.size()) {
        return std::vector<int>();
    }
    return result[id];
}

bool traverseQueue(std::deque<int>& queue, std::unordered_set<int>& this_visited, const std::unordered_set<int>& other_visited) {
    size_t queue_size = queue.size();
    for (size_t i = 0; i < queue_size; ++i) {
        int val = queue.front();
        queue.pop_front();
        if (this_visited.count(val)) {
            continue;
        }
        this_visited.insert(val);
        auto neighbors = getConnections(val);
        for (int neighbor : neighbors) {
            if (other_visited.count(neighbor)) {
                return true;
            }
            queue.push_back(neighbor);
        }
    }
    
    return false;
}

int getDistance(int id1, int id2) {
    if (id1 == id2) {
        return 0;
    }
    
    std::deque<int> lhs;
    std::deque<int> rhs;
    std::unordered_set<int> lhs_visited;
    std::unordered_set<int> rhs_visited;

    int current_distance = 0;
    lhs.push_back(id1);
    rhs.push_back(id2);
    
    while (true) {
        if (lhs.empty()) {
            break;
        } else {
            if (traverseQueue(lhs, lhs_visited, rhs_visited)) {
                return current_distance;
            }
        }
        current_distance++;
        
        if (rhs.empty()) {
            break;
        } else {
            if (traverseQueue(rhs, rhs_visited, lhs_visited)) {
                return current_distance;
            }
        }
        current_distance++;
    }
    return -1;
}

int eddington(const std::vector<int>& record) {
    // Cannot be larger than the size.
    std::map<int, int> frequency;
    for (int entry : record) {
        frequency[entry]++;
    }
    
    int max = -1;
    int remaining = static_cast<int>(record.size());
    for (const std::pair<int, int> frequency_entry : frequency) {
        if (remaining >= frequency_entry.first) {
            max = frequency_entry.first;
            remaining -= frequency_entry.second;
        } else {
            break;
        }
    }
    if (max == -1) {
        return static_cast<int>(record.size());
    }
    return max;
}

int eddington1(const std::vector<int>& record_o) {
    // Obviously wouldn't actually copy, just to make testing easier.
    std::vector<int> record = record_o;
    std::sort(record.begin(), record.end(), std::greater_equal<int>());
    int i = 1;
    for (int entry : record) {
        if (entry < i) {
            break;
        }
        ++i;
    }
    return i - 1;
}

int eddington2(const std::vector<int>& record) {
    int ed = 0;
    int above = 0;
    std::vector<int> H(record.size());
    for (int entry : record) {
        if (entry > ed) {
            above += 1;
            if (entry < record.size()) {
                H[entry] += 1;
            }
            if (above > ed) {
                ed += 1;
                above -= H[ed];
            }
        }
    }
    
    return ed;
}

int main(int argc, const char * argv[]) {
    std::cout << getDistance(0,6) << " " << getDistance(1, 5) << " " << getDistance(0, 4) << " " << getDistance(6, 7) << std::endl;
    std::cout << eddington({3,1,2}) << " " << eddington({99, 100, 101}) << " " << eddington({1, 1, 2, 1, 1}) << " " << eddington({}) << std::endl;
    std::cout << eddington1({3,1,2}) << " " << eddington1({99, 100, 101}) << " " << eddington1({1, 1, 2, 1, 1}) << " " << eddington1({}) << std::endl;
    std::cout << eddington2({3,1,2}) << " " << eddington2({99, 100, 101}) << " " << eddington2({1, 1, 2, 1, 1}) << " " << eddington2({}) << std::endl;
    return 0;
}
