//
//  main_original.cpp
//  LiftoffCode1
//
//  Created by Vinay Chaudhary on 8/20/24.
//
/*
 #include <stdio.h>
 
 //
 //  main.cpp
 //  LiftoffCode1
 //
 //  Created by Vinay Chaudhary on 8/20/24.
 //
 
 #include <iostream>
 #include <deque>
 #include <vector>
 #include <set>
 #include <unordered_set>
 
 
 std::vector<int> getConnections(int id) {
 static std::vector<std::vector<int>> result{{1,3}, {0,2,3,4,5}, {2, 1}, {0, 1, 5}, {1,5,6}, {1, 3, 4, 6}, {4, 5}, {}};
 return result[id];
 }
 
 int getDistance(int id1, int id2) {
 if (id1 == id2) {
 return 0;
 }
 
 std::deque<int> lhs;
 std::deque<int> rhs;
 std::unordered_set<int> lhs_visited;
 std::unordered_set<int> rhs_visited;
 lhs_visited.insert(id1);
 rhs_visited.insert(id2);
 
 int current_distance = 1;
 lhs.push_back(id1);
 rhs.push_back(id2);
 
 while (true) {
 int lhs_queue_size = lhs.size();
 if (lhs_queue_size == 0) {
 break;
 }
 for (int i = 0; i < lhs_queue_size; ++i) {
 int val = lhs.front();
 lhs.pop_front();
 if (lhs_visited.count(val)) {
 continue;
 }
 if (rhs_visited.count(val)) {
 return true;
 }
 lhs_visited.insert(val);
 auto neighbors = getConnections(val);
 for (int neighbor : neighbors) {
 lhs.push_back(neighbor);
 }
 }
 
 current_distance++;
 int rhs_queue_size = rhs.size();
 if (rhs_queue_size == 0) {
 break;
 }
 for (int i = 0; i < rhs_queue_size; ++i) {
 int val = rhs.front();
 rhs.pop_front();
 if (rhs_visited.count(val)) {
 continue;
 }
 if (lhs_visited.count(val)) {
 return true;
 }
 rhs_visited.insert(val);
 auto neighbors = getConnections(val);
 for (int neighbor : neighbors) {
 rhs.push_back(neighbor);
 }
 }
 current_distance++;
 }
 return -1;
 }
 
 int main(int argc, const char * argv[]) {
 std::cout << getDistance(0,6) << " " << getDistance(1, 5) << " " << getDistance(0, 4) << std::endl;
 return 0;
 }
 */
