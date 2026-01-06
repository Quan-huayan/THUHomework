// 股票买卖最佳时机I：一次交易
int max_profit_one_transaction(int* prices, int n) {
    if (n < 2) return 0;
    
    int min_price = prices[0];
    int max_profit = 0;
    
    for (int i = 1; i < n; i++) {
        if (prices[i] < min_price) {
            min_price = prices[i];
        } else {
            int profit = prices[i] - min_price;
            if (profit > max_profit) {
                max_profit = profit;
            }
        }
    }
    
    return max_profit;
}

// 股票买卖最佳时机II：无限次交易
int max_profit_unlimited(int* prices, int n) {
    if (n < 2) return 0;
    
    int max_profit = 0;
    
    for (int i = 1; i < n; i++) {
        if (prices[i] > prices[i-1]) {
            max_profit += prices[i] - prices[i-1];
        }
    }
    
    return max_profit;
}

// 股票买卖最佳时机III：最多两次交易
int max_profit_two_transactions(int* prices, int n) {
    if (n < 2) return 0;
    
    // dp1[i]: 从0到i的最大利润（一次交易）
    int* dp1 = (int*)malloc(n * sizeof(int));
    dp1[0] = 0;
    int min_price = prices[0];
    
    for (int i = 1; i < n; i++) {
        min_price = prices[i] < min_price ? prices[i] : min_price;
        dp1[i] = (prices[i] - min_price) > dp1[i-1] ? 
                (prices[i] - min_price) : dp1[i-1];
    }
    
    // dp2[i]: 从i到n-1的最大利润（一次交易）
    int* dp2 = (int*)malloc(n * sizeof(int));
    dp2[n-1] = 0;
    int max_price = prices[n-1];
    
    for (int i = n-2; i >= 0; i--) {
        max_price = prices[i] > max_price ? prices[i] : max_price;
        dp2[i] = (max_price - prices[i]) > dp2[i+1] ? 
                (max_price - prices[i]) : dp2[i+1];
    }
    
    // 合并两次交易
    int max_profit = 0;
    for (int i = 0; i < n; i++) {
        int profit = dp1[i] + dp2[i];
        if (profit > max_profit) {
            max_profit = profit;
        }
    }
    
    free(dp1);
    free(dp2);
    
    return max_profit;
}

// 股票买卖最佳时机IV：最多k次交易
int max_profit_k_transactions(int k, int* prices, int n) {
    if (n < 2 || k == 0) return 0;
    
    // 如果k很大，相当于没有限制
    if (k >= n / 2) {
        return max_profit_unlimited(prices, n);
    }
    
    // dp[j][0]: 第j次交易后不持有股票的最大利润
    // dp[j][1]: 第j次交易后持有股票的最大利润
    int** dp = (int**)malloc((k+1) * sizeof(int*));
    for (int i = 0; i <= k; i++) {
        dp[i] = (int*)malloc(2 * sizeof(int));
        dp[i][0] = 0;
        dp[i][1] = -prices[0];
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = k; j >= 1; j--) {
            // 第j次交易不持有股票
            dp[j][0] = dp[j][0] > (dp[j][1] + prices[i]) ?
                      dp[j][0] : (dp[j][1] + prices[i]);
            
            // 第j次交易持有股票
            dp[j][1] = dp[j][1] > (dp[j-1][0] - prices[i]) ?
                      dp[j][1] : (dp[j-1][0] - prices[i]);
        }
    }
    
    int result = dp[k][0];
    
    // 清理内存
    for (int i = 0; i <= k; i++) free(dp[i]);
    free(dp);
    
    return result;
}