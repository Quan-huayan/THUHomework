#include <stdio.h>

struct Node
{
    int now = 0;
    int depth = 0;
    Node():now(0),depth(0) {}
    Node(int n, int d):now(n), depth(d) {}
    Node(const Node& r):now(r.now),depth(r.depth) {}
    Node(Node&& r):now(r.now),depth(r.depth) {}
    Node operator=(Node&& r) {now = r.now;depth = r.depth; return *this;}
} *head;

//首尾queue
template<typename T>
class Queue
{
    struct __QueueNode
    {
        T data;
        struct __QueueNode* next;
    } *head, *foot;
public:
    int size;
public:
    Queue():head(nullptr),foot(nullptr),size(0) {}
    void insert(T data)//插在队尾
    {
        __QueueNode* pInsert = new __QueueNode{data, nullptr};
        if(pInsert)
        {
            if(!head) //队列为空
            {
                head = foot = pInsert;
            }
            else //队列不为空
            {
                foot -> next = pInsert;
                foot = pInsert;
            }
            size++;
        }
    }
    T pop()
    {
        if(head) // 队列不为空时进行操作
        {
            struct __QueueNode *now = head;
            head = now->next;
            if(!head) foot = head; // 队列中最后一个元素
            T ret = now->data;
            delete now;
            size--;
            return ret;
        }
        return T();
    }
};

Queue<struct Node*> queue;

// 二叉树，用于标记查找
class NumberTree
{
    struct __binary_tree_node
    {
        int num;
        struct __binary_tree_node* left;
        struct __binary_tree_node* right;
    } *head;
public:
    NumberTree()
    {
        head = new __binary_tree_node {-1, nullptr, nullptr};
    }
    void insert(int num)
    {
        struct __binary_tree_node* p = head, *p1 = nullptr;
        int tag = 0, numBack = num;
        while(p && num)
        {
            switch(tag = num%2)
            {
            case 0:
                p1 = p, p = p->left;break;
            case 1:
                p1 = p, p = p->right;break;
            }
            num >>= 1;
        }
        //num为0,p不为空，说明位置已存在。
        //num不为空,p为空，说明位置不存在且中间需补空。
        //num为0,p也为空，说明位置正确且未插入
        if(!p)//p为空
        {
            while(num)//继续循环
            {
                switch(tag)
                {
                case 0:
                    p1 -> left = new __binary_tree_node{-1,nullptr, nullptr}, p1 = p1->left; break;
                case 1:
                    p1 -> right = new __binary_tree_node{-1,nullptr, nullptr}, p1 = p1->right; break;
                }
                tag = num%2;
                num >>= 1;
            }
        }
        switch(tag)
        {
        case 0:
            p1 -> left = new __binary_tree_node{numBack, nullptr, nullptr};
            break;
        case 1:
            p1 -> right = new __binary_tree_node{numBack, nullptr, nullptr};
            break;
        }
    }
    bool find(int num)
    {
        struct __binary_tree_node* p = head, *p1 = nullptr;
        int numBack = num;
        while(p && num)
        {
            switch(num%2)
            {
            case 0:
                p1 = p, p = p->left;break;
            case 1:
                p1 = p, p = p->right;break;
            }
            num >>= 1;
        }
        return p && p->num == numBack;
    }
} findTags;

int main()
{
    int begin, dest;
    scanf("%d %d", &begin, &dest);
    if(begin == dest) {putchar('0');return 0;}
    else if(begin == 0 || dest == 0) { printf("%d",begin == 0? dest : begin);return 0;}
    struct Node *buff = new Node[12 * (1<<20)];//Node：8 字节，buff:96 M
    int index = 0;
    buff[index++] = {begin,0};
    struct Node* start = &buff[0], *pNow = start;
    queue.insert(start);
    while(queue.size > 0)
    {
        pNow = queue.pop();
        //从当前节点出发，遍历
        int nNow = pNow -> now;
        int nDepth = pNow -> depth;
        if(dest == nNow - 1 || dest == nNow + 1 || dest == 2*nNow)
        {
            printf("%d", nDepth+1);
            delete[] buff;
            return 0;
        }
        if(nNow>1 && !findTags.find(nNow - 1))
        {
            buff[index] = {nNow - 1, nDepth+1};
            Node* pNext = &buff[index++];
            queue.insert(pNext);
            findTags.insert(nNow - 1);
        }
        if(!findTags.find(nNow + 1))
        {
            buff[index] = {nNow + 1, nDepth+1};
            Node* pNext = &buff[index++];
            queue.insert(pNext);
            findTags.insert(nNow + 1);
        }
        if(nNow < 2*dest && !findTags.find(2 * nNow))
        {
            buff[index] = {2*nNow, nDepth+1};
            Node* pNext = &buff[index++];
            queue.insert(pNext);
            findTags.insert(2 * nNow);
        }
    };
    delete[] buff;
    return 0;
}