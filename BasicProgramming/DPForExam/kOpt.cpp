// 斜率优化示例：任务安排问题
typedef struct {
    int t;  // 时间
    int c;  // 费用系数
} Task;

int compare_tasks(const void* a, const void* b) {
    Task* task_a = (Task*)a;
    Task* task_b = (Task*)b;
    return task_a->t - task_b->t;
}

// 任务安排最小费用（斜率优化）
long long min_cost_schedule(Task* tasks, int n) {
    // 按时间排序
    qsort(tasks, n, sizeof(Task), compare_tasks);
    
    // 计算前缀和
    long long* sum_t = (long long*)malloc((n+1) * sizeof(long long));
    long long* sum_c = (long long*)malloc((n+1) * sizeof(long long));
    sum_t[0] = sum_c[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        sum_t[i] = sum_t[i-1] + tasks[i-1].t;
        sum_c[i] = sum_c[i-1] + tasks[i-1].c;
    }
    
    long long* dp = (long long*)malloc((n+1) * sizeof(long long));
    dp[0] = 0;
    
    // 使用单调队列优化
    int* queue = (int*)malloc((n+1) * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = 0;
    
    for (int i = 1; i <= n; i++) {
        // 维护队列的斜率单调性
        while (front + 1 < rear) {
            int j = queue[front];
            int k = queue[front+1];
            
            // 计算斜率
            long long y1 = dp[j] - sum_t[j] * sum_c[n] + sum_t[j] * sum_c[j];
            long long y2 = dp[k] - sum_t[k] * sum_c[n] + sum_t[k] * sum_c[k];
            long long x1 = sum_t[j];
            long long x2 = sum_t[k];
            
            if (y2 - y1 <= sum_c[i] * (x2 - x1)) {
                front++;
            } else {
                break;
            }
        }
        
        int j = queue[front];
        dp[i] = dp[j] + sum_t[i] * (sum_c[i] - sum_c[j]) - 
                sum_t[j] * (sum_c[i] - sum_c[j]) + 
                sum_t[i] * sum_c[n] - sum_t[i] * sum_c[i];
        
        // 将i加入队列
        while (front + 1 < rear) {
            int k1 = queue[rear-2];
            int k2 = queue[rear-1];
            
            long long y1 = dp[k1] - sum_t[k1] * sum_c[n] + sum_t[k1] * sum_c[k1];
            long long y2 = dp[k2] - sum_t[k2] * sum_c[n] + sum_t[k2] * sum_c[k2];
            long long y3 = dp[i] - sum_t[i] * sum_c[n] + sum_t[i] * sum_c[i];
            long long x1 = sum_t[k1];
            long long x2 = sum_t[k2];
            long long x3 = sum_t[i];
            
            if ((y2 - y1) * (x3 - x2) >= (y3 - y2) * (x2 - x1)) {
                rear--;
            } else {
                break;
            }
        }
        queue[rear++] = i;
    }
    
    long long result = dp[n];
    
    free(sum_t);
    free(sum_c);
    free(dp);
    free(queue);
    
    return result;
}