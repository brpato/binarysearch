#include <iostream>
#include <vector>
using namespace std;

/*Implement binary search from scratch in C++17. Your program must work on a sorted vector and return the index of the target or -1 when the target is absent.

Required implementation
Implement an iterative binary search.
Implement a recursive binary search.
Instrument both versions to count element comparisons.
Test at least five searches, including: first element, last element, middle element, missing value below the range, and missing value inside the range.
For the recursive version, write and explain the recurrence T(n) = T(n/2) + O(1) and connect it to O(log n).
Compare binary search to a linear search on the same data.*/

pair<int, int> ibs(vector<int> nums, int tar){
    int low = 0;
    int high = nums.size() - 1;
    int counter = 0;
    while(low <= high){
        counter++;
        int mid = (low + high) / 2;
        if(nums[mid] > tar){
            high = mid - 1;
        }
        else if(nums[mid] < tar){
            low = mid + 1;
        }
        else{
            return {mid, counter};
        }
    }
    return {-1, counter};
}

pair<int,int> rbs(vector<int> nums, int tar, int low, int high, int counter){
    int mid = (low + high) / 2;
    if(low > high){
        return {-1, counter};
    }
    counter++;
    if(nums[mid] > tar){
        return rbs(nums, tar, low, mid - 1, counter);
    }
    else if(nums[mid] < tar){
        return rbs(nums, tar, mid + 1, high, counter);
    }
    return {mid, counter};
}

pair<int,int> linearS(vector<int> nums, int tar){
    int counter = 0;
    for(int i = 0; i < static_cast<int>(nums.size()); ++i){
        counter++;
        if(nums[i] == tar){
            return {i, counter};
        }
    }
    return {-1, counter};
}

int main() {
    vector<vector<int>> tests = {{0, 1, 2, 3, 4},
    {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27},
    {9, 10, 11},
    {0, 1},
    {0, 1, 2, 3, 4, 6}};
    vector<int> tars = {0, 27, 10, 2, 5};
    string value;

    for(int i = 0; i < static_cast<int>(tests.size()); i++){
        pair<int, int> iRes = {ibs(tests[i], tars[i]).first, ibs(tests[i], tars[i]).second};
        pair<int, int> rRes = {rbs(tests[i], tars[i], 0, tests[i].size() - 1, 0).first, rbs(tests[i], tars[i], 0, tests[i].size() - 1, 0).second};
        pair<int, int> lRes = {linearS(tests[i], tars[i]).first, linearS(tests[i], tars[i]).second};
        if(iRes.first < 0 || rRes.first < 0 || lRes.first < 0){
            value = "N/A";
        }
        else{
            value = to_string(tests[i][iRes.first]);
        }

        cout<< "test case: " << i + 1 << " target value: " << tars[i] << endl << " iterative:" << endl << "  index: " << iRes.first << " value: " << value << " counter: " << iRes.second << endl << " recursive:" << endl << "  index: " << rRes.first << " value: " << value << " counter: " << rRes.second << endl << " linear:" << endl << "  index: " << lRes.first << " value: " << value << " counter: " << lRes.second << endl;
    }
}