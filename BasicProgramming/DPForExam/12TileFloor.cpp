// 铺砖问题：用1x2的砖铺满n x m的地板
long long tile_floor(int n, int m) {
    if ((n * m) % 2 != 0) return 0;
    
    int total_states = 1 << m;
    long long** dp = (long long**)malloc((n+1) * sizeof(long long*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (long long*)malloc(total_states * sizeof(long long));
        for (int j = 0; j < total_states; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[0][0] = 1;
    
    for (int row = 0; row < n; row++) {
        for (int state = 0; state < total_states; state++) {
            if (dp[row][state] > 0) {
                // 递归填充下一行
                void dfs(int col, int next_state, long long count) {
                    if (col == m) {
                        dp[row+1][next_state] += count;
                        return;
                    }
                    
                    // 如果当前位置已经被覆盖（来自上一行的竖砖）
                    if (state & (1 << col)) {
                        dfs(col + 1, next_state, count);
                    } else {
                        // 尝试放竖砖（覆盖当前行和下一行）
                        if (row < n - 1) {
                            dfs(col + 1, next_state | (1 << col), count);
                        }
                        
                        // 尝试放横砖（覆盖当前行的两列）
                        if (col < m - 1 && !(state & (1 << (col + 1)))) {
                            dfs(col + 2, next_state, count);
                        }
                    }
                }
                
                dfs(0, 0, dp[row][state]);
            }
        }
    }
    
    long long result = dp[n][0];
    
    // 清理内存
    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);
    
    return result;
}