// 最大子数组和（Kadane算法）
// 一维dp数组：dp[i]
int max_subarray_sum(int* nums, int n) {
    if (n == 0) return 0;
    
    int max_ending_here = nums[0];
    int max_so_far = nums[0];
    
    for (int i = 1; i < n; i++) {
        max_ending_here = nums[i] > (max_ending_here + nums[i]) ? 
                         nums[i] : (max_ending_here + nums[i]);
        max_so_far = max_so_far > max_ending_here ? 
                    max_so_far : max_ending_here;
    }
    
    return max_so_far;4
}

// 返回最大子数组的起始和结束位置
int max_subarray_sum_with_pos(int* nums, int n, int* start, int* end) {
    if (n == 0) return 0;
    
    int max_ending_here = nums[0];
    int max_so_far = nums[0];
    int temp_start = 0;
    *start = *end = 0;
    
    for (int i = 1; i < n; i++) {
        if (nums[i] > max_ending_here + nums[i]) {
            max_ending_here = nums[i];
            temp_start = i;
        } else {
            max_ending_here = max_ending_here + nums[i];
        }
        
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            *start = temp_start;
            *end = i;
        }
    }
    
    return max_so_far;
}