#include <deque>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 定义帖子结构体，用于存储帖子ID和对应的浏览量
struct Post {
    int id;         // 帖子ID
    int max_views;  // 最近T天内的最大浏览量

    // 优先队列按max_views降序排列，如果max_views相同，按id升序排列
    bool operator<(const Post &other) const
    {
        if (max_views == other.max_views) {
            return id < other.id;  // 浏览量相同时ID较大的优先
        }
        return max_views < other.max_views;  // 浏览量较大的优先
    }
};

int main()
{
    int T, D, P;
    cin >> T >> D >> P;

    // 记录每天每个帖子的浏览量
    vector<vector<int>> data(D, vector<int>(P));
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < P; j++) {
            cin >> data[i][j];
        }
    }

    // 用 deque 存储每个帖子的最近 T 天的浏览量
    vector<deque<int>> post_views(P);

    // 用优先队列来找出最大浏览量的帖子
    for (int day = 0; day < D; day++) {
        // 更新每个帖子的浏览量
        for (int post_id = 0; post_id < P; post_id++) {
            post_views[post_id].push_back(data[day][post_id]);

            // 如果超过T天，移除最旧的浏览量
            if (post_views[post_id].size() > T) {
                post_views[post_id].pop_front();
            }
        }

        // 使用优先队列来找最大浏览量的帖子
        priority_queue<Post> pq;

        // 对于每个帖子，计算其最近 T 天的最大浏览量
        for (int post_id = 0; post_id < P; post_id++) {
            int max_views = *max_element(post_views[post_id].begin(), post_views[post_id].end());
            pq.push(Post{post_id + 1, max_views});  // 帖子ID从1开始
        }

        // 输出当前热门帖的ID
        cout << pq.top().id << " ";
    }

    cout << endl;
    return 0;
}
