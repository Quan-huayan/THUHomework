// 戳气球最大硬币数
int max_coins(int* nums, int n) {
    // 创建新数组，在首尾添加1
    int* balloons = (int*)malloc((n+2) * sizeof(int));
    balloons[0] = 1;
    balloons[n+1] = 1;
    for (int i = 0; i < n; i++) {
        balloons[i+1] = nums[i];
    }
    
    int m = n + 2;
    int** dp = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dp[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dp[i][j] = 0;
        }
    }
    
    // 从小区间到大区间
    for (int len = 2; len < m; len++) {
        for (int left = 0; left < m - len; left++) {
            int right = left + len;
            
            // 尝试每个位置作为最后戳破的气球
            for (int k = left + 1; k < right; k++) {
                int coins = dp[left][k] + dp[k][right] + 
                           balloons[left] * balloons[k] * balloons[right];
                if (coins > dp[left][right]) {
                    dp[left][right] = coins;
                }
            }
        }
    }
    
    int result = dp[0][m-1];
    
    // 清理内存
    free(balloons);
    for (int i = 0; i < m; i++) free(dp[i]);
    free(dp);
    
    return result;
}