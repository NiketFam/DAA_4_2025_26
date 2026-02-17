#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool ispos(vector<int>& piles, int mid, int h) {
        long long cnt = 0;

        for(int i = 0; i < piles.size(); i++) {
            cnt += piles[i] / mid;
            if(piles[i] % mid != 0) {
                cnt++;
            }
        }
        return cnt <= h;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1;
        int r = *max_element(piles.begin(), piles.end());
        int ans = 0;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(ispos(piles, mid, h)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return ans;
    }
};
int main() {
    int n;
    cout << "Enter number of piles: ";
    cin >> n;
    vector<int> piles(n);
    cout << "Enter pile sizes: ";
    for(int i = 0; i < n; i++) {
        cin >> piles[i];
    }
    int h;
    cout << "Enter hours: ";
    cin >> h;
    Solution obj;
    cout << "Minimum eating speed: "
         << obj.minEatingSpeed(piles, h) << endl;
    return 0;
}