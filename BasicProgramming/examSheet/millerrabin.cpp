// 对于32位整数，Miller-Rabin可以确定性地判断
bool isPrimeMillerRabin(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if ((n & 1) == 0) return false;
    
    // 将n-1分解为d * 2^r
    int d = n - 1;
    int r = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    
    // 32位整数只需要测试a = 2, 7, 61
    int testBases[] = {2, 7, 61};
    
    for (int i = 0; i < 3; i++) {
        int a = testBases[i];
        if (a >= n) continue;  // 如果a >= n，跳过这个测试
        
        // 计算a^d mod n
        long long x = 1;
        long long base = a;
        int exp = d;
        
        // 快速幂取模
        while (exp > 0) {
            if (exp & 1) {
                x = (x * base) % n;
            }
            base = (base * base) % n;
            exp >>= 1;
        }
        
        if (x == 1 || x == n - 1) {
            continue;  // 通过测试
        }
        
        // 平方r-1次
        bool composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        
        if (composite) {
            return false;  // 确定是合数
        }
    }
    
    return true;  // 很可能是质数（对于32位整数是确定的）
}