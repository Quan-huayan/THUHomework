// 最长公共子序列（LCS）
// 二维dp表：dp[i][j]表示字符串1前i个字符和字符串2前j个字符的公共子序列最大长度。
int longest_common_subsequence(char* text1, char* text2) {
    int m = strlen(text1);
    int n = strlen(text2);
    
    int** dp = (int**)malloc((m+1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n+1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }
    
    int result = dp[m][n];
    
    // 打印LCS
    char* lcs = (char*)malloc((result + 1) * sizeof(char));
    lcs[result] = '\0';
    
    int i = m, j = n, k = result - 1;
    while (i > 0 && j > 0) {
        if (text1[i-1] == text2[j-1]) {
            lcs[k--] = text1[i-1];
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    printf("最长公共子序列: %s\n", lcs);
    free(lcs);
    
    // 清理内存
    for (int i = 0; i <= m; i++) free(dp[i]);
    free(dp);
    
    return result;
}

// 最长公共子串
int longest_common_substring(char* text1, char* text2) {
    int m = strlen(text1);
    int n = strlen(text2);
    
    int** dp = (int**)malloc((m+1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n+1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    
    int max_len = 0;
    int end_pos = 0;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > max_len) {
                    max_len = dp[i][j];
                    end_pos = i - 1;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    // 打印最长公共子串
    if (max_len > 0) {
        char* lcstr = (char*)malloc((max_len + 1) * sizeof(char));
        strncpy(lcstr, &text1[end_pos - max_len + 1], max_len);
        lcstr[max_len] = '\0';
        printf("最长公共子串: %s\n", lcstr);
        free(lcstr);
    }
    
    // 清理内存
    for (int i = 0; i <= m; i++) free(dp[i]);
    free(dp);
    
    return max_len;
}