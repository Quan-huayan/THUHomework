//索引链表

#include <stdio.h>

typedef struct __struct_node
{
    int index;
    struct __struct_node* next;
} Node, *PNode;

PNode head, *arrayIndex;

void init(int n)
{
    head = nullptr;
    arrayIndex = new PNode[n];
}

void insert(int index, int n)//插到index为n的节点后面
{
    auto sIndex = index-1;
    if(!head)
    {
        head = new Node{index,nullptr};
        arrayIndex[sIndex] = head;
        return;
    }
    if(!n)//队首
    {
        PNode pInsert = new Node{index, head};
        head = pInsert;
        arrayIndex[sIndex] = pInsert;
        return;
    }
    PNode pInsertLast = arrayIndex[n-1];
    PNode pInsert = new Node{index, pInsertLast->next};
    arrayIndex[sIndex] = pInsert;
    pInsertLast->next = pInsert;
}

void output_and_release()
{
    if(arrayIndex) delete[] arrayIndex;
    if(head)
    {
        PNode p=head,q;
        while(p)
        {
            printf("%d ",p->index);
            q = p->next;
            delete p;
            p = q;
        }
    }
}

int main()
{
    int n,x;
    scanf("%d",&n);
    init(n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        insert(i,x);
    }
    output_and_release();
    return 0;
}