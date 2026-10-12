#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

struct Interval {
    int l, r;
    bool operator<(const Interval& other) const {
        return l < other.l || (l == other.l && r < other.r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    set<Interval> intervals;
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            
            int deleted_count = 0;
            
            // Find the first interval with start >= l
            auto it = intervals.lower_bound({l, r});
            
            // Check the previous interval (if any) for overlap
            if (it != intervals.begin()) {
                auto prev_it = prev(it);
                if (prev_it->r >= l) {
                    // Previous interval overlaps
                    deleted_count++;
                    it = intervals.erase(prev_it);
                }
            }
            
            // Remove all intervals that overlap with [l, r]
            while (it != intervals.end() && it->l <= r) {
                deleted_count++;
                it = intervals.erase(it);
            }
            
            // Insert the new interval
            intervals.insert({l, r});
            
            cout << deleted_count << "\n";
        } else if (op == 'B') {
            cout << intervals.size() << "\n";
        }
    }
    
    return 0;
}