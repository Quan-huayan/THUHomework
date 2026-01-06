// 旅行商问题（TSP）
int tsp(int** dist, int n) {
    int size = 1 << n;
    
    // dp[mask][i] 表示访问过mask中的城市，最后停在i的最短路径
    int** dp = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    
    // 初始化：从城市0出发
    dp[1][0] = 0;
    
    // 遍历所有状态
    for (int mask = 1; mask < size; mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] < INT_MAX) {
                // 尝试访问下一个城市
                for (int j = 0; j < n; j++) {
                    if (!(mask & (1 << j))) {  // j不在mask中
                        int new_mask = mask | (1 << j);
                        int new_dist = dp[mask][i] + dist[i][j];
                        if (new_dist < dp[new_mask][j]) {
                            dp[new_mask][j] = new_dist;
                        }
                    }
                }
            }
        }
    }
    
    // 找到最短回路
    int min_cost = INT_MAX;
    int all_visited = (1 << n) - 1;
    
    for (int i = 1; i < n; i++) {
        if (dp[all_visited][i] < INT_MAX) {
            int total_cost = dp[all_visited][i] + dist[i][0];
            if (total_cost < min_cost) {
                min_cost = total_cost;
            }
        }
    }
    
    // 清理内存
    for (int i = 0; i < size; i++) free(dp[i]);
    free(dp);
    
    return min_cost;
}