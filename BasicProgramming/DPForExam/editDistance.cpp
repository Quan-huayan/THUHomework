// 编辑距离
// DP表是二维的
// dp[i][j]表示word1前i个字符转换为word2前j个字符的最小操作数
int edit_distance(char* word1, char* word2) {
    int m = strlen(word1);
    int n = strlen(word2);
    
    int** dp = (int**)malloc((m+1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n+1) * sizeof(int));
    }
    
    // 初始化
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    
    // 填充DP表
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                int replace = dp[i-1][j-1] + 1;
                int del = dp[i-1][j] + 1;
                int insert = dp[i][j-1] + 1;
                dp[i][j] = replace < del ? replace : del;
                dp[i][j] = dp[i][j] < insert ? dp[i][j] : insert;
            }
        }
    }
    
    int result = dp[m][n];
    
    // 清理内存
    for (int i = 0; i <= m; i++) free(dp[i]);
    free(dp);
    
    return result;
}