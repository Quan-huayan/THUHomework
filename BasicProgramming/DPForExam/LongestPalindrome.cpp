// 最长回文子序列
// 二维dp表：dp[i][j]表示i开头,j结尾的字符串中最长的回文子序列长度
int longest_palindromic_subsequence(char* s) {
    int n = strlen(s);
    
    int** dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
        dp[i][i] = 1;
    }
    
    // 从长度2开始
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] == s[j]) {
                if (len == 2) {
                    dp[i][j] = 2;
                } else {
                    dp[i][j] = dp[i+1][j-1] + 2;
                }
            } else {
                dp[i][j] = dp[i+1][j] > dp[i][j-1] ? dp[i+1][j] : dp[i][j-1];
            }
        }
    }
    
    int result = dp[0][n-1];
    
    // 清理内存
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);
    
    return result;
}

// 最长回文子串
char* longest_palindromic_substring(char* s) {
    int n = strlen(s);
    if (n < 2) return s;
    
    int start = 0, max_len = 1;
    
    // 动态规划方法
    int** dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
        dp[i][i] = 1;
    }
    
    // 检查长度为2的子串
    for (int i = 0; i < n-1; i++) {
        if (s[i] == s[i+1]) {
            dp[i][i+1] = 1;
            start = i;
            max_len = 2;
        }
    }
    
    // 检查长度大于2的子串
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] == s[j] && dp[i+1][j-1]) {
                dp[i][j] = 1;
                if (len > max_len) {
                    start = i;
                    max_len = len;
                }
            }
        }
    }
    
    // 构建结果字符串
    char* result = (char*)malloc((max_len + 1) * sizeof(char));
    strncpy(result, s + start, max_len);
    result[max_len] = '\0';
    
    // 清理内存
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);
    
    return result;
}