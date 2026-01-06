// 正则表达式匹配：支持 '.' 和 '*'
int is_match_regex(char* s, char* p) {
    int m = strlen(s);
    int n = strlen(p);
    
    // dp[i][j] 表示s的前i个字符和p的前j个字符是否匹配
    int** dp = (int**)malloc((m+1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n+1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[0][0] = 1;
    
    // 处理p以*开头的情况
    for (int j = 1; j <= n; j++) {
        if (p[j-1] == '*') {
            dp[0][j] = dp[0][j-2];
        }
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') {
                // *匹配0次
                dp[i][j] = dp[i][j-2];
                
                // *匹配1次或多次
                if (p[j-2] == '.' || p[j-2] == s[i-1]) {
                    dp[i][j] = dp[i][j] || dp[i-1][j];
                }
            } else {
                if (p[j-1] == '.' || p[j-1] == s[i-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }
    }
    
    int result = dp[m][n];
    
    // 清理内存
    for (int i = 0; i <= m; i++) free(dp[i]);
    free(dp);
    
    return result;
}