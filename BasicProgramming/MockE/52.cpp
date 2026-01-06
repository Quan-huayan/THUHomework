#include <stdio.h>

#define INT_MAX 2147483647

struct Point
{
    int x,y;
    bool operator == (Point& p)
    {
        return x == p.x && y == p.y;
    }
};
struct gate
{
    Point a;
    Point b;
};

#define MAX_N 100
#define MAX_M 100
#define MAX_K 10
#define MAX_K_STATES (1 << MAX_K)

int grid[MAX_N][MAX_M];             //权值数据
gate gates[MAX_K];                  //传送门数据
int dp[MAX_K_STATES][MAX_N][MAX_M]; //动态规划数据
int gateData[MAX_K_STATES][MAX_N][MAX_M];

int main()
{
    // 输入
    int n, m, k;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&grid[i][j]);
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        scanf("%d %d %d %d",&gates[i].a.x,&gates[i].a.y,&gates[i].b.x,&gates[i].b.y);
        gates[i].a.x--,gates[i].a.y--,gates[i].b.x--,gates[i].b.y--;
    }

    // DP
    // 最外圈对state遍历
    int kStateNum = 1 << k;
    // 初始化
    for(int kState = 0;kState < kStateNum; kState++)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                dp[kState][i][j] = INT_MAX, gateData[kState][i][j] = -2;
        // 如果是被选中的传送门，gateData设置为-1，否则为门的id
        for(int i=0;i<k;i++)
        {
            gateData[kState][gates[i].a.x][gates[i].a.y] = i;
            gateData[kState][gates[i].b.x][gates[i].b.y] = i;
        }
        for(int kStateTemp = kState, i=0;kStateTemp;kStateTemp >>= 1,i++)
            if(kStateTemp % 2)
            {
                gateData[kState][gates[i].a.x][gates[i].a.y] = -1;
                gateData[kState][gates[i].b.x][gates[i].b.y] = -1;
            }
    }
    dp[0][0][0]=grid[0][0];
    for(int kState = 0;kState < kStateNum; kState++)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            {
                int val = dp[kState][i][j];
                //无法到达为INF_MAX
                if(dp[kState][i][j]==INT_MAX || gateData[kState][i][j]>=0) continue;//当前节点不能是不可达到或者是未使用的传送门
                //向右移动:计算dp[kState][i][j+1]
                if(j<m-1 && gateData[kState][i][j+1]!=-1)//跳过使用过的传送门
                {
                    if(dp[kState][i][j+1] > val + grid[i][j+1])//更小则更新
                        dp[kState][i][j+1] = val + grid[i][j+1];
                }
                //向下移动:计算dp[kState][i+1][j]
                if(i<n-1 && gateData[kState][i+1][j]!=-1)//跳过使用过的传送门
                {
                    if(dp[kState][i+1][j] > val + grid[i+1][j])//更小则更新
                        dp[kState][i+1][j] = val + grid[i+1][j];
                }
            }
        // 使用传送门更新
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // 如果当前格子是传送门端点且传送门未使用，即gateData为正数
                int id = gateData[kState][i][j];
                if (id >= 0) {
                    int new_state = kState | (1 << id);
                    Point pNow = {i,j}, pNext;
                    if(gates[id].a == pNow) pNext = gates[id].b;
                    else pNext = gates[id].a;
                    if (dp[kState][i][j] < dp[new_state][pNext.x][pNext.y]) {
                        dp[new_state][pNext.x][pNext.y] = dp[kState][i][j];
                    }
                }
            }
        }
    }
    //寻找最小的终点数值
    int min = dp[0][n-1][m-1];
    for(int i=1;i<kStateNum;i++)
        if(min>dp[i][n-1][m-1])
            min=dp[i][n-1][m-1];
    
    if(min >= INT_MAX-1)
    {
        printf("No Way");
    }
    else printf("%d",min);

    return 0;
}