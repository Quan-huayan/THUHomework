#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Box
{
    char name[30];
    int size, weight;
    bool operator < (Box& B)
    {
        if(size != B.size) return size < B.size;
        if(weight != B.weight) return weight > B.weight;
        return strcmp(name, B.name) < 0;
    }
    Box& operator = (Box& B)
    {
        size = B.size;
        weight = B.weight;
        strcpy(name, B.name);
        return *this;
    }
};

struct BoxList
{
    struct BoxNode
    {
        struct Box box;
        struct BoxNode *last;
        struct BoxNode *next;
    } *head, *foot;
public:
    BoxList():head(nullptr),foot(nullptr) {}
    ~BoxList()
    {
        BoxNode *p = head;
        while(p)
        {
            BoxNode *q = p;
            p = p->next;
            delete q;
        }
    }
    void add(Box box)
    {
        BoxNode *now = new BoxNode{box,nullptr,nullptr};
        if(!head)//列表为空
        {
            head = foot = now;
            return;
        }
        foot -> next = now;
        now -> last = foot;
        foot = now;
    }
    void top(char* str)
    {
        BoxNode *box = find(str);
        if(box)
        {
            // 将box从当前位置拿出
            if(box->last) box->last->next=box->next;//box不在头部
            else head = box->next;
            if(box->next) box->next->last=box->last;//box不在尾部
            else foot = box->last;
            // 然后放到头部
            box -> last = nullptr;
            box -> next = head;
            head -> last = box;
            head =  box;
        }
    }
    void remove(char* str)
    {
        BoxNode *box = find(str);
        if(box)
        {
            // 将box从当前位置拿出
            if(box->last) box->last->next=box->next;//box不在头部
            else head = box->next;
            if(box->next) box->next->last=box->last;//box不在尾部
            else foot = box->last;
            // 然后删除
            delete box;
        }
    }
    void order()
    {
        BoxNode *p = head, *q = foot;
        // 冒泡排序
        for(;p->next;p=p->next)
            for(q = foot;q != p; q = q->last)
                if(q->box < q->last->box)
                {
                    Box temp = q->box;
                    q->box = q->last->box;
                    q->last->box = temp;
                }
    }
    void reverse()
    {
        // 从尾部开始
        if(foot)
        {
            BoxNode *p = foot;
            while(p)
            {
                BoxNode *p1 = p->last;
                BoxNode *pTemp = p -> last;
                p -> last = p -> next;
                p -> next = pTemp;
                p = p1;
            }
            BoxNode *pTemp = head;
            head = foot;
            foot = pTemp;
        }
    }
    void output()
    {
        if(head)
        {
            BoxNode *p = head;
            while(p)
            {
                printf("%s %d %d\n",p->box.name,p->box.size,p->box.weight);
                p = p->next;
            }
        }
    }
private:
    BoxNode* find(char* str)
    {
        // 对半查找
        BoxNode* p=head, *q=foot;
        if(p == q)
        {
            if(0 == strcmp(p->box.name, str)) return p;
            return nullptr;
        }
        while((q != (p -> last)) && (p!=q))
        {
            if(0 == strcmp(p->box.name, str)) return p;
            if(0 == strcmp(q->box.name, str)) return q;
            p = p -> next, q = q -> last;
        }
        if(p == q)
        {
            if(0 == strcmp(p->box.name, str)) return p;
            return nullptr;
        }
        return nullptr;
    }
} list;

int main()
{
    int commandNumber = 0, processNumber = 0;
    scanf("%d", &commandNumber);
    char s[20],name[20];
    int c;
    while(commandNumber)
    {
        scanf("%s",s);
        if(0==strcmp(s,"ADD"))
        {
            Box box;
            scanf("%s",box.name);
            scanf("%d",&box.size);
            scanf("%d",&box.weight);
            list.add(box);
            commandNumber--;
        }
        else if(0==strcmp(s,"TOP"))
        {
            scanf("%s", name);
            list.top(name);
            commandNumber--;
        }
        else if(0==strcmp(s,"REMOVE"))
        {
            scanf("%s", name);
            list.remove(name);
            commandNumber--;
        }
        else if(0==strcmp(s,"ORDER"))
        {
            list.order();
            commandNumber--;
        }
        else if(0==strcmp(s,"REVERSE"))
        {
            list.reverse();
            commandNumber--;
        }
    }
    list.output();
    return 0;
}