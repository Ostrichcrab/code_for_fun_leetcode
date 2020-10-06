#include "common/struct.h"
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_map>
#include<limits.h>
using namespace std;

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    vector<int> arr;
    unordered_map<int,int> hash;
    int cnt = 0;
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(hash.find(val) == hash.end()){
            hash[val] = cnt ++;
            arr.push_back(val);
            return true;
        }
        return false;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = hash.find(val);
        if(it != hash.end()){
            int idx = it->second;
            arr[idx] = arr.back();
            hash[arr[idx]] = idx;
            arr.pop_back();
            cnt --;
            hash.erase(it);
            return true;
        }
        return false;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return arr[rand() % cnt];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */