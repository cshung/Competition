#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() < 3)
        {
            return 0;
        }
        int root;
        vector<int> left;
        vector<int> right;
        build_cartestian_tree(height, root, left, right);
        // running_sum[i] = [0, i)
        vector<int> running_sum;
        running_sum.resize(height.size() + 1);
        running_sum[0] = 0;
        for (int i = 0; i < height.size(); i++)
        {
            running_sum[i + 1] = running_sum[i] + height[i];
        }
        return trap(height, root, left, right, running_sum);
    }
    
    int trap(const vector<int>& arr, int root, vector<int>& left, vector<int>& right, const vector<int>& running_sum)
    {
        if (root == -1)
        {
            return 0;
        }
        bool has_left = left[root] != -1;
        bool has_right = right[root] != -1;
        int counted = 0;
        if (has_left)
        {
            int from = left[root] + 1;
            int to = root - 1;
            int level = arr[left[root]];
            int length = to - from + 1;
            int volume = level * length;
            int occupied = running_sum[to + 1] - running_sum[from];
            right[left[root]] = -1;
            counted += (volume - occupied);
        }
        if (has_right)
        {
            int from = root + 1;
            int to = right[root] - 1;
            int level = arr[right[root]];
            int length = to - from + 1;
            int volume = level * length;
            int occupied = running_sum[to + 1] - running_sum[from];
            left[right[root]] = -1;
            counted += (volume - occupied);
        }
        return trap(arr, left[root], left, right, running_sum) + counted + trap(arr, right[root], left, right, running_sum);
    }
    
    void build_cartestian_tree(const vector<int>& arr, int& root, vector<int>& left, vector<int>& right)
    {
        size_t n = arr.size();
        // Arrays to hold the index of parent, left-child,
        // right-child of each number in the input array
        vector<int> parent;
        parent.resize(arr.size());
        left.resize(arr.size());
        right.resize(arr.size());
        
        // Initialize all array values as -1
        for (int i = 0; i < arr.size(); i++)
        {
            parent[i] = -1;
            left[i] = -1;
            right[i] = -1;
        }
        
        // 'root' and 'last' stores the index of the root and the
        // last processed of the Cartesian Tree.
        // Initially we take root of the Cartesian Tree as the
        // first element of the input array. This can change
        // according to the algorithm
        root = 0;
        int last;
        
        // Starting from the second element of the input array
        // to the last on scan across the elements, adding them
        // one at a time.
        for (int i = 1; i <= n - 1; i++)
        {
            last = i - 1;
            right[i] = -1;
            
            // Scan upward from the node's parent up to
            // the root of the tree until a node is found
            // whose value is greater than the current one
            // This is the same as Step 2 mentioned in the
            // algorithm
            while (arr[last] <= arr[i] && last != root)
                last = parent[last];
            
            // arr[i] is the largest element yet; make it
            // new root
            if (arr[last] <= arr[i])
            {
                parent[root] = i;
                left[i] = root;
                root = i;
            }
            
            // Just insert it
            else if (right[last] == -1)
            {
                right[last] = i;
                parent[i] = last;
                left[i] = -1;
            }
            
            // Reconfigure links
            else
            {
                parent[right[last]] = i;
                left[i] = right[last];
                right[last] = i;
                parent[i] = last;
            }
            
        }
        
        // Since the root of the Cartesian Tree has no
        // parent, so we assign it -1
        parent[root] = -1;
    }
};

int main(int argc, char** argv)
{
    Solution s;
    //                   0 1 2 3 4 5 6 7 8 9 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
    int test1_array[] = {6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3};
    vector<int> test1(test1_array, test1_array + 26);
    cout << s.trap(test1) << endl;
    return 0;
}
