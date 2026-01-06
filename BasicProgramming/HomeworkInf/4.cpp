#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minEditToPalindrome(const char *str) {
    int n = strlen(str);
    
    if (n <= 1) return 0;  // 空串或单个字符已经是回文
    
    // 创建动态规划表
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        memset(dp[i], 0, n * sizeof(int));
    }
    
    // 从短子串开始构建
    for (int len = 2; len <= n; len++) {  // 子串长度从2到n
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;  // 子串结束位置
            
            if (len == 2) {
                // 长度为2的特殊情况
                dp[i][j] = (str[i] == str[j]) ? 0 : 1;
            } else {
                if (str[i] == str[j]) {
                    // 首尾字符相同，不需要修改
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    // 首尾字符不同，考虑三种操作：
                    // 1. 删除或插入：删除str[i]或插入str[j]的副本到i位置
                    int delete_left_or_insert_right = 1 + dp[i + 1][j];
                    
                    // 2. 删除或插入：删除str[j]或插入str[i]的副本到j位置
                    int delete_right_or_insert_left = 1 + dp[i][j - 1];
                    
                    // 3. 替换：将str[i]替换为str[j]或将str[j]替换为str[i]
                    int replace = 1 + dp[i + 1][j - 1];
                    
                    // 取最小值
                    int min_operation = delete_left_or_insert_right;
                    if (delete_right_or_insert_left < min_operation) {
                        min_operation = delete_right_or_insert_left;
                    }
                    if (replace < min_operation) {
                        min_operation = replace;
                    }
                    
                    dp[i][j] = min_operation;
                }
            }
        }
    }
    
    int result = dp[0][n - 1];
    
    // 释放内存
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    char input[101];
    gets(input);
    printf("%d",minEditToPalindrome(input));
    
    return 0;
}