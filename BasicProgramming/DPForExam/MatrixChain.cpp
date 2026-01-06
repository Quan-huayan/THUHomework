// 矩阵链乘法最小计算次数
int matrix_chain_multiplication(int* dimensions, int n) {
    // n个矩阵有n+1个维度
    // dimensions[i] 表示第i个矩阵的行数，dimensions[i+1] 表示第i个矩阵的列数
    
    int** dp = (int**)malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((n+1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    
    // 链长度从2到n
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + 
                          dimensions[i-1] * dimensions[k] * dimensions[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    
    int result = dp[1][n];
    
    // 打印最优括号化方案
    printf("最小乘法次数: %d\n", result);
    
    // 清理内存
    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);
    
    return result;
}