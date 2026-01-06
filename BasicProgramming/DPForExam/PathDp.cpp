// 不同路径
int unique_paths(int m, int n) {
    int** dp = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
    }
    
    // 初始化第一行和第一列
    for (int i = 0; i < m; i++) dp[i][0] = 1;
    for (int j = 0; j < n; j++) dp[0][j] = 1;
    
    // 填充DP表
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    
    int result = dp[m-1][n-1];
    
    // 清理内存
    for (int i = 0; i < m; i++) free(dp[i]);
    free(dp);
    
    return result;
}

// 带障碍物的不同路径
int unique_paths_with_obstacles(int** obstacle_grid, int m, int n) {
    if (obstacle_grid[0][0] == 1 || obstacle_grid[m-1][n-1] == 1) {
        return 0;
    }
    
    long long** dp = (long long**)malloc(m * sizeof(long long*));
    for (int i = 0; i < m; i++) {
        dp[i] = (long long*)malloc(n * sizeof(long long));
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[0][0] = 1;
    
    // 初始化第一行
    for (int j = 1; j < n; j++) {
        dp[0][j] = obstacle_grid[0][j] == 0 ? dp[0][j-1] : 0;
    }
    
    // 初始化第一列
    for (int i = 1; i < m; i++) {
        dp[i][0] = obstacle_grid[i][0] == 0 ? dp[i-1][0] : 0;
    }
    
    // 填充DP表
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (obstacle_grid[i][j] == 0) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    long long result = dp[m-1][n-1];
    
    // 清理内存
    for (int i = 0; i < m; i++) free(dp[i]);
    free(dp);
    
    return (int)result;
}

// 最小路径和
int min_path_sum(int** grid, int m, int n) {
    int** dp = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
    }
    
    dp[0][0] = grid[0][0];
    
    // 初始化第一行
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    
    // 初始化第一列
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    
    // 填充DP表
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = (dp[i-1][j] < dp[i][j-1] ? dp[i-1][j] : dp[i][j-1]) + grid[i][j];
        }
    }
    
    int result = dp[m-1][n-1];
    
    // 清理内存
    for (int i = 0; i < m; i++) free(dp[i]);
    free(dp);
    
    return result;
}