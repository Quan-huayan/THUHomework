// 二叉树节点定义
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 创建树节点
TreeNode* create_node(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 二叉树中的最大路径和
int max_path_sum(TreeNode* root) {
    int max_sum = INT_MIN;
    
    int dfs(TreeNode* node) {
        if (!node) return 0;
        
        int left_gain = dfs(node->left);
        if (left_gain < 0) left_gain = 0;
        
        int right_gain = dfs(node->right);
        if (right_gain < 0) right_gain = 0;
        
        // 当前节点作为转折点的路径和
        int path_sum = node->val + left_gain + right_gain;
        if (path_sum > max_sum) {
            max_sum = path_sum;
        }
        
        // 返回以当前节点为起点的最大路径和
        return node->val + (left_gain > right_gain ? left_gain : right_gain);
    }
    
    dfs(root);
    return max_sum;
}

// 打家劫舍III：二叉树形式
typedef struct {
    int robbed;     // 抢劫当前节点的最大收益
    int not_robbed; // 不抢劫当前节点的最大收益
} RobState;

RobState dfs_rob(TreeNode* root) {
    if (!root) {
        RobState state = {0, 0};
        return state;
    }
    
    RobState left = dfs_rob(root->left);
    RobState right = dfs_rob(root->right);
    
    // 抢劫当前节点：不能抢劫子节点
    int robbed = root->val + left.not_robbed + right.not_robbed;
    
    // 不抢劫当前节点：可以选择抢劫或不抢劫子节点
    int not_robbed = (left.robbed > left.not_robbed ? left.robbed : left.not_robbed) +
                     (right.robbed > right.not_robbed ? right.robbed : right.not_robbed);
    
    RobState state = {robbed, not_robbed};
    return state;
}

int rob_tree(TreeNode* root) {
    RobState state = dfs_rob(root);
    return state.robbed > state.not_robbed ? state.robbed : state.not_robbed;
}