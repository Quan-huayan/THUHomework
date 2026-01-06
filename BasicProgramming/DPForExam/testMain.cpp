#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// 所有函数声明放在这里
extern int max_subarray_sum(int* nums, int n);
extern int knapsack_01(int* weights, int* values, int n, int capacity);
extern int coin_change_min(int* coins, int n, int amount);
extern int unique_paths(int m, int n);
extern int longest_common_subsequence(char* text1, char* text2);
extern int edit_distance(char* word1, char* word2);
extern int max_coins(int* nums, int n);
extern int tsp(int** dist, int n);
//extern int max_path_sum(TreeNode* root);
extern int max_profit_k_transactions(int k, int* prices, int n);

int main() {
    printf("=== 动态规划算法测试 ===\n\n");
    
    // 测试最大子数组和
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("最大子数组和: %d\n\n", max_subarray_sum(nums, n));
    
    // 测试0-1背包
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int capacity = 5;
    printf("0-1背包最大价值: %d\n\n", 
           knapsack_01(weights, values, 4, capacity));
    
    // 测试零钱兑换
    int coins[] = {1, 2, 5};
    int amount = 11;
    printf("零钱兑换最少硬币数: %d\n\n", 
           coin_change_min(coins, 3, amount));
    
    // 测试不同路径
    printf("3x3网格不同路径数: %d\n\n", unique_paths(3, 3));
    
    // 测试最长公共子序列
    char* text1 = "abcde";
    char* text2 = "ace";
    printf("最长公共子序列长度: %d\n\n", 
           longest_common_subsequence(text1, text2));
    
    // 测试编辑距离
    char* word1 = "horse";
    char* word2 = "ros";
    printf("编辑距离: %d\n\n", edit_distance(word1, word2));
    
    // 测试戳气球
    int balloon_nums[] = {3, 1, 5, 8};
    printf("戳气球最大硬币数: %d\n\n", 
           max_coins(balloon_nums, 4));
    
    // 测试股票买卖
    int prices[] = {3, 2, 6, 5, 0, 3};
    int prices_n = 6;
    printf("最多2次交易的最大利润: %d\n\n", 
           max_profit_k_transactions(2, prices, prices_n));
    
    return 0;
}