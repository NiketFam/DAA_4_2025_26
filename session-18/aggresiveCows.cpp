#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isPossible(vector<int>& stalls, int k, int dist) {
        int cows = 1;
        int lastPos = stalls[0];
        for (int i = 1; i < stalls.size(); i++) {
            if (stalls[i] - lastPos >= dist) {
                cows++;
                lastPos = stalls[i];
            }
            if (cows == k) return true;
        }
        return false;
    }
    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());
        int left = 1;
        int right = stalls.back() - stalls.front();
        int ans = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (isPossible(stalls, k, mid)) {
                ans = mid;
                left = mid + 1;   
            } else {
                right = mid - 1; 
            }
        }
        return ans;
    }
};
int main() {
    int n;
    cout << "Enter number of stalls: ";
    cin >> n;
    vector<int> stalls(n);
    cout << "Enter stall positions: ";
    for (int i = 0; i < n; i++) {
        cin >> stalls[i];
    }
    int k;
    cout << "Enter number of cows: ";
    cin >> k;
    Solution obj;
    int result = obj.aggressiveCows(stalls, k);
    cout << "Maximum minimum distance: " << result << endl;
    return 0;
}