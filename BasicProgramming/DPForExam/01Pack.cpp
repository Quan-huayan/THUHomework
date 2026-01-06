// 0-1背包基础版本
int knapsack_01(int* weights, int* values, int n, int capacity) {
    int** dp = (int**)malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((capacity+1) * sizeof(int));
        for (int j = 0; j <= capacity; j++) {
            dp[i][j] = 0;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= capacity; j++) {
            if (weights[i-1] <= j) {
                dp[i][j] = dp[i-1][j] > (dp[i-1][j-weights[i-1]] + values[i-1]) ?
                          dp[i-1][j] : (dp[i-1][j-weights[i-1]] + values[i-1]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    
    int result = dp[n][capacity];
    
    // 回溯找出选择的物品
    int* selected = (int*)calloc(n, sizeof(int));
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            selected[i-1] = 1;
            w -= weights[i-1];
        }
    }
    
    printf("选择的物品: ");
    for (int i = 0; i < n; i++) {
        if (selected[i]) printf("%d ", i+1);
    }
    printf("\n");
    
    free(selected);
    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);
    
    return result;
}

// 0-1背包空间优化版本
int knapsack_01_optimized(int* weights, int* values, int n, int capacity) {
    int* dp = (int*)calloc(capacity + 1, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        for (int j = capacity; j >= weights[i]; j--) {
            dp[j] = dp[j] > (dp[j - weights[i]] + values[i]) ?
                   dp[j] : (dp[j - weights[i]] + values[i]);
        }
    }
    
    int result = dp[capacity];
    free(dp);
    return result;
}

// 完全背包问题（物品无限）
int knapsack_unbounded(int* weights, int* values, int n, int capacity) {
    int* dp = (int*)calloc(capacity + 1, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        for (int j = weights[i]; j <= capacity; j++) {
            dp[j] = dp[j] > (dp[j - weights[i]] + values[i]) ?
                   dp[j] : (dp[j - weights[i]] + values[i]);
        }
    }
    
    int result = dp[capacity];
    free(dp);
    return result;
}

// 多重背包问题
int knapsack_multiple(int* weights, int* values, int* counts, int n, int capacity) {
    int* dp = (int*)calloc(capacity + 1, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        // 二进制优化
        int k = 1;
        int amount = counts[i];
        
        while (k <= amount) {
            int weight = k * weights[i];
            int value = k * values[i];
            
            for (int j = capacity; j >= weight; j--) {
                dp[j] = dp[j] > (dp[j - weight] + value) ?
                       dp[j] : (dp[j - weight] + value);
            }
            
            amount -= k;
            k *= 2;
        }
        
        if (amount > 0) {
            int weight = amount * weights[i];
            int value = amount * values[i];
            
            for (int j = capacity; j >= weight; j--) {
                dp[j] = dp[j] > (dp[j - weight] + value) ?
                       dp[j] : (dp[j - weight] + value);
            }
        }
    }
    
    int result = dp[capacity];
    free(dp);
    return result;
}