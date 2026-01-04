#include <stdio.h>
#include <stdlib.h>

#define N 5


// 定义方向：上、右、下、左
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

struct Point {
    int x, y;
    Point* parent;  // 用于回溯路径
};

// 队列
class Queue {
private:
    struct QueueNode {
        Point* data;
        QueueNode* next;
    };// 链表
    QueueNode* front;
    QueueNode* rear;
    int size;
public:
    Queue() {
        front = rear = nullptr;
        size = 0;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return size == 0;
    }
    
    void enqueue(Point* point) {
        QueueNode* newNode = new QueueNode;
        newNode->data = point;
        newNode->next = nullptr;
        
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    Point* dequeue() {
        if (isEmpty()) {
            return nullptr;
        }
        
        QueueNode* temp = front;
        Point* point = front->data;
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        size--;
        return point;
    }
    
    int getSize() {
        return size;
    }
};

void printPath(Point* point) {
    if (point == nullptr) {
        return;
    }
    
    printPath(point->parent);
    
    printf("(%d, %d)\n", point->x, point->y);
}

// BFS算法寻找最短路径
void bfs(int maze[N][N]) {
    // 记录访问状态
    bool visited[N][N] = {false};
    
    Queue queue;
    
    Point* start = new Point;
    start->x = 0;
    start->y = 0;
    start->parent = nullptr;
    
    visited[0][0] = true;
    
    queue.enqueue(start);
    
    // BFS主循环
    while (!queue.isEmpty()) {
        Point* current = queue.dequeue();
        
        // 如果到达终点
        if (current->x == N - 1 && current->y == N - 1) {
            printPath(current);
            //queue自然释放
            return;
        }
        
        // 探索四个方向
        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];
            
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && 
                maze[nx][ny] == 0 && !visited[nx][ny]) {
                
                Point* next = new Point;
                next->x = nx;
                next->y = ny;
                next->parent = current;

                visited[nx][ny] = true;
                
                queue.enqueue(next);
            }
        }
    }
}

int main() {
    int maze[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    
    bfs(maze);
    
    return 0;
}