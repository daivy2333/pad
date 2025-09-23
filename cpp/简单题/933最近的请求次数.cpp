#include <queue>

class RecentCounter {
private:
    std::queue<int> requests;

public:
    RecentCounter() {
        // 初始化队列
    }
    
    int ping(int t) {
        // 将当前时间加入队列
        requests.push(t);
        
        // 移除不在 [t-3000, t] 范围内的时间
        while (requests.front() < t - 3000) {
            requests.pop();
        }
        
        // 返回队列的大小
        return requests.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
