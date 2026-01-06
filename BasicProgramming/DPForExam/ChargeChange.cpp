// 零钱兑换I：最少硬币数
// 一维DP表：dp[j]表示换j元所需的最小硬币数
int coin_change_min(int* coins, int n, int amount) {
    int* dp = (int*)malloc((amount + 1) * sizeof(int));
    
    // 初始化
    for (int i = 0; i <= amount; i++) {
        dp[i] = amount + 1;  // 设置为一个不可能的大值
    }
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                dp[i] = dp[i] < (dp[i - coins[j]] + 1) ?
                       dp[i] : (dp[i - coins[j]] + 1);
            }
        }
    }
    
    int result = dp[amount] > amount ? -1 : dp[amount];
    free(dp);
    return result;
}

// 零钱兑换II：组合数
// 一维DP表：dp[j]表示换j元可用的硬币组合数
int coin_change_combinations(int* coins, int n, int amount) {
    int* dp = (int*)calloc(amount + 1, sizeof(int));
    dp[0] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    int result = dp[amount];
    free(dp);
    return result;
}