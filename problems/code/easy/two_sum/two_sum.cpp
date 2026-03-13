
#include "vector"

using namespace std;

class SolutionOn2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        bool solution_found = false;
        vector<int> ret(2);

        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    solution_found = true;
                    ret[0] = i;
                    ret[1] = j;
                }
            }
            if (solution_found)
            {
                break;
            }
        }

        return ret;
    }
};

#include <unordered_map>

class SolutionOn {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> pairIdx;

        for (int i = 0; i < nums.size(); ++i) {
            int num = nums[i];
            if (pairIdx.find(target - num) != pairIdx.end()) {
                return {i, pairIdx[target - num]};
            }
            pairIdx[num] = i;
        }

        return {};        
    }
};
