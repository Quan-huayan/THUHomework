#pragma once

// deepseek 生成

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// ==================== 辅助模版 ======================

template<typename T>
void swap(T a, T b)
{
    T c = a;
    a = b;
    b = c;
}

// ==================== 字符串操作 ====================

// 字符串转小写
inline void str_to_lower(char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
    }
}

inline void str_to_lower2(char* str) {
    for (char *p = str; *p; p++) *p = tolower(*p);
}

// 字符串转大写
inline void str_to_upper(char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

inline void str_to_upper2(char* str) {
    for (char *p = str; *p; p++) *p = toupper(*p);
}

// 字符串反转
inline void str_reverse(char* str) {
    if (!str) return;
    int len = 0;
    while (str[len] != '\0') ++len;
    
    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

inline void str_reverse2(char* str) {
    char *p = str, *q = str;
    while (*(q++));
    q--, q--;
    while(p<q)
    {
        char temp = *p;
        *p = *q;
        *q = temp;
        p++, q--;
    }
}

// 获得尾部NULL的指针
char* getTail(char* str)
{
    char* q = str;
    while(*(q++));
    q--;
    return q;
}

// ==================== 进制转换 ====================

// 将字符转换为对应的数字值
inline int char_to_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1; // 无效字符
}

// 将数字值转换为字符
inline char digit_to_char(int num) {
    if (num >= 0 && num <= 9) return '0' + num;
    if (num >= 10 && num <= 35) return 'A' + (num - 10);
    return '?'; // 无效数字
}

// 字符串转整数（支持2-36进制）
inline long str_to_int(const char* str, int base = 10) {
    if (!str || base < 2 || base > 36) return 0;
    
    long result = 0;
    bool negative = false;
    int i = 0;
    
    // 处理符号
    if (str[i] == '-') {
        negative = true;
        ++i;
    } else if (str[i] == '+') {
        ++i;
    }
    
    // 转换数字
    while (str[i] != '\0') {
        int digit = char_to_digit(str[i]);
        if (digit < 0 || digit >= base) break;
        
        result = result * base + digit;
        ++i;
    }
    
    return negative ? -result : result;
}

// 整数转字符串（支持2-36进制）
inline char* int_to_str(long num, char* buffer, int base = 10) {
    if (!buffer || base < 2 || base > 36) return nullptr;
    
    bool negative = false;
    int i = 0;
    
    // 处理0的情况
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }
    
    // 处理负数
    if (num < 0) {
        negative = true;
        num = -num;
    }
    
    // 转换数字（反向）
    while (num > 0) {
        int digit = num % base;
        buffer[i++] = digit_to_char(digit);
        num /= base;
    }
    
    // 添加负号
    if (negative) {
        buffer[i++] = '-';
    }
    
    buffer[i] = '\0';
    
    // 反转字符串
    str_reverse(buffer);
    
    return buffer;
}

// ==================== 排序算法 ====================

// 冒泡排序（稳定）
inline void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 选择排序
inline void selection_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// 插入排序（稳定）
inline void insertion_sort(int* arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 快速排序辅助函数
inline int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

// 快速排序
inline void quick_sort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// 堆排序辅助函数
inline void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// 堆排序
inline void heap_sort(int* arr, int n) {
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    
    // 一个一个提取元素
    for (int i = n - 1; i > 0; --i) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// 归并排序 

// 合并两个已排序的子数组
inline void merge(int* arr, int left, int mid, int right, int* temp) {
    int i = left;       // 左子数组起始索引
    int j = mid + 1;    // 右子数组起始索引
    int k = left;       // 临时数组起始索引
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    // 复制剩余元素
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    // 将临时数组复制回原数组
    for (i = left; i <= right; ++i) {
        arr[i] = temp[i];
    }
}

// 递归归并排序
inline void merge_sort_recursive(int* arr, int left, int right, int* temp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // 递归排序左右两部分
        merge_sort_recursive(arr, left, mid, temp);
        merge_sort_recursive(arr, mid + 1, right, temp);
        
        // 合并已排序的两部分
        merge(arr, left, mid, right, temp);
    }
}

// 归并排序（稳定）
inline void merge_sort(int* arr, int n) {
    if (n <= 1) return;
    
    // 分配临时数组
    int* temp = new int[n];
    
    merge_sort_recursive(arr, 0, n - 1, temp);
    
    // 释放临时数组
    delete[] temp;
}

// 迭代归并排序（非递归，稳定）
inline void merge_sort_iterative(int* arr, int n) {
    if (n <= 1) return;
    
    int* temp = new int[n];
    
    // 从1开始，每次合并的子数组大小翻倍
    for (int size = 1; size < n; size *= 2) {
        // 合并相邻的子数组
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = left + size - 1;
            int right = left + 2 * size - 1;
            
            // 确保right不超过数组边界
            if (right >= n) {
                right = n - 1;
            }
            
            // 确保mid不超过数组边界
            if (mid >= n) {
                mid = n - 1;
            }
            
            // 合并相邻的子数组
            if (mid < right) {
                merge(arr, left, mid, right, temp);
            }
        }
    }
    
    delete[] temp;
}

// ==================== 素数判断 ====================

// 简单判断（试除法）
inline bool is_prime_simple(int n) {
    if (n <= 1) return false;
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// 优化判断（试除到sqrt）
inline bool is_prime_sqrt(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    int limit = (int)sqrt((double)n);
    for (int i = 5; i <= limit; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// 6k±1优化法
inline bool is_prime_6k(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    int limit = (int)sqrt((double)n);
    //for (int i = 5; i * i <= n; i += 6) {
    for (int i = 5; i <= limit; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Miller-Rabin素数测试（快速，有一定概率误判）
inline long long power_mod(long long a, long long d, long long n) {
    long long result = 1;
    a = a % n;
    
    while (d > 0) {
        if (d & 1) {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        d >>= 1;
    }
    return result;
}

inline bool miller_test(long long d, long long n) {
    long long a = 2 + rand() % (n - 4);
    long long x = power_mod(a, d, n);
    
    if (x == 1 || x == n - 1) return true;
    
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        
        if (x == 1) return false;
        if (x == n - 1) return true;
    }
    return false;
}

inline bool is_prime_miller_rabin(long long n, int k = 5) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    
    for (int i = 0; i < k; ++i) {
        if (!miller_test(d, n)) return false;
    }
    return true;
}

// ==================== 回文数判断 ====================

// 整数回文判断（不使用字符串）
inline bool is_palindrome_int(int n) {
    if (n < 0) return false;
    
    int reversed = 0;
    int original = n;
    
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    
    return original == reversed;
}

// 字符串回文判断
inline bool is_palindrome_str(const char* str) {
    if (!str) return false;
    
    int len = 0;
    while (str[len] != '\0') ++len;
    
    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        if (str[i] != str[j]) return false;
    }
    return true;
}

// ==================== 单向链表 ====================

struct SinglyNode {
    int data;
    SinglyNode* next;
    
    SinglyNode(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    SinglyNode* head;
    SinglyNode* tail; // 可选尾指针
    int size;
    
public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~SinglyLinkedList() {
        clear();
    }
    
    // 在头部追加
    void push_front(int val) {
        SinglyNode* new_node = new SinglyNode(val);
        new_node->next = head;
        head = new_node;
        if (!tail) tail = head;
        ++size;
    }
    
    // 在尾部追加
    void push_back(int val) {
        SinglyNode* new_node = new SinglyNode(val);
        if (!head) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        ++size;
    }
    
    // 反转链表
    void reverse() {
        SinglyNode* prev = nullptr;
        SinglyNode* current = head;
        SinglyNode* next = nullptr;
        
        tail = head; // 反转后尾变头
        
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    
    // 查找元素
    SinglyNode* find(int val) {
        SinglyNode* current = head;
        while (current) {
            if (current->data == val) return current;
            current = current->next;
        }
        return nullptr;
    }
    
    // 在特定序号插入（0-based）
    bool insert_at(int index, int val) {
        if (index < 0 || index > size) return false;
        
        if (index == 0) {
            push_front(val);
            return true;
        }
        
        if (index == size) {
            push_back(val);
            return true;
        }
        
        SinglyNode* new_node = new SinglyNode(val);
        SinglyNode* current = head;
        
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        new_node->next = current->next;
        current->next = new_node;
        ++size;
        return true;
    }
    
    // 在特定内容前插入
    bool insert_before(int target_val, int new_val) {
        if (!head) return false;
        
        if (head->data == target_val) {
            push_front(new_val);
            return true;
        }
        
        SinglyNode* current = head;
        while (current->next) {
            if (current->next->data == target_val) {
                SinglyNode* new_node = new SinglyNode(new_val);
                new_node->next = current->next;
                current->next = new_node;
                ++size;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // 删除特定序号元素
    bool remove_at(int index) {
        if (index < 0 || index >= size || !head) return false;
        
        if (index == 0) {
            SinglyNode* temp = head;
            head = head->next;
            if (tail == temp) tail = head;
            delete temp;
            --size;
            return true;
        }
        
        SinglyNode* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        SinglyNode* to_delete = current->next;
        current->next = to_delete->next;
        
        if (tail == to_delete) tail = current;
        
        delete to_delete;
        --size;
        return true;
    }
    
    // 删除特定内容元素（第一个匹配的）
    bool remove_value(int val) {
        if (!head) return false;
        
        if (head->data == val) {
            SinglyNode* temp = head;
            head = head->next;
            if (tail == temp) tail = head;
            delete temp;
            --size;
            return true;
        }
        
        SinglyNode* current = head;
        while (current->next) {
            if (current->next->data == val) {
                SinglyNode* to_delete = current->next;
                current->next = to_delete->next;
                
                if (tail == to_delete) tail = current;
                
                delete to_delete;
                --size;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // 排序（使用插入排序）
    void sort() {
        if (!head || !head->next) return;
        
        SinglyNode* sorted = nullptr;
        SinglyNode* current = head;
        
        while (current) {
            SinglyNode* next = current->next;
            
            if (!sorted || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                SinglyNode* search = sorted;
                while (search->next && search->next->data < current->data) {
                    search = search->next;
                }
                current->next = search->next;
                search->next = current;
            }
            current = next;
        }
        
        head = sorted;
        // 更新尾指针
        tail = head;
        while (tail && tail->next) tail = tail->next;
    }
    
    // 清空链表
    void clear() {
        while (head) {
            SinglyNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
    
    // 获取大小
    int get_size() const { return size; }
    
    // 打印链表
    void print() const {
        SinglyNode* current = head;
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
};

// ==================== 双向链表 ====================

struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
    
    DoublyNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DoublyNode* head;
    DoublyNode* tail;
    int size;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~DoublyLinkedList() {
        clear();
    }
    
    // 在头部追加
    void push_front(int val) {
        DoublyNode* new_node = new DoublyNode(val);
        
        if (!head) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++size;
    }
    
    // 在尾部追加
    void push_back(int val) {
        DoublyNode* new_node = new DoublyNode(val);
        
        if (!head) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        ++size;
    }
    
    // 反转链表
    void reverse() {
        DoublyNode* current = head;
        DoublyNode* temp = nullptr;
        
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        
        if (temp) {
            tail = head;
            head = temp->prev;
        }
    }
    
    // 查找元素
    DoublyNode* find(int val) {
        DoublyNode* current = head;
        while (current) {
            if (current->data == val) return current;
            current = current->next;
        }
        return nullptr;
    }
    
    // 在特定序号插入
    bool insert_at(int index, int val) {
        if (index < 0 || index > size) return false;
        
        if (index == 0) {
            push_front(val);
            return true;
        }
        
        if (index == size) {
            push_back(val);
            return true;
        }
        
        DoublyNode* new_node = new DoublyNode(val);
        DoublyNode* current;
        
        // 从较近的一端开始遍历
        if (index <= size / 2) {
            current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; --i) {
                current = current->prev;
            }
        }
        
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
        
        ++size;
        return true;
    }
    
    // 删除特定序号元素
    bool remove_at(int index) {
        if (index < 0 || index >= size || !head) return false;
        
        DoublyNode* to_delete;
        
        if (index == 0) {
            to_delete = head;
            head = head->next;
            if (head) head->prev = nullptr;
            if (tail == to_delete) tail = nullptr;
        } else if (index == size - 1) {
            to_delete = tail;
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            if (head == to_delete) head = nullptr;
        } else {
            // 从较近的一端开始遍历
            if (index <= size / 2) {
                to_delete = head;
                for (int i = 0; i < index; ++i) {
                    to_delete = to_delete->next;
                }
            } else {
                to_delete = tail;
                for (int i = size - 1; i > index; --i) {
                    to_delete = to_delete->prev;
                }
            }
            
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
        }
        
        delete to_delete;
        --size;
        return true;
    }
    
    // 删除特定内容元素
    bool remove_value(int val) {
        DoublyNode* current = find(val);
        if (!current) return false;
        
        if (current == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            if (tail == current) tail = nullptr;
        } else if (current == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        
        delete current;
        --size;
        return true;
    }
    
    // 排序（使用插入排序）
    void sort() {
        if (!head || !head->next) return;
        
        DoublyNode* sorted = nullptr;
        DoublyNode* current = head;
        
        while (current) {
            DoublyNode* next = current->next;
            
            if (!sorted || sorted->data >= current->data) {
                current->prev = nullptr;
                current->next = sorted;
                if (sorted) sorted->prev = current;
                sorted = current;
            } else {
                DoublyNode* search = sorted;
                while (search->next && search->next->data < current->data) {
                    search = search->next;
                }
                current->next = search->next;
                current->prev = search;
                if (search->next) search->next->prev = current;
                search->next = current;
            }
            current = next;
        }
        
        head = sorted;
        // 更新尾指针
        tail = head;
        while (tail && tail->next) tail = tail->next;
    }
    
    // 清空链表
    void clear() {
        while (head) {
            DoublyNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
    
    // 获取大小
    int get_size() const { return size; }
    
    // 打印链表（从头到尾）
    void print_forward() const {
        DoublyNode* current = head;
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
    
    // 打印链表（从尾到头）
    void print_backward() const {
        DoublyNode* current = tail;
        while (current) {
            printf("%d ", current->data);
            current = current->prev;
        }
        printf("\n");
    }
};

// 测试函数

int main() {
    // 初始化随机数种子
    srand(time(NULL));
    
    printf("========== 字符串操作测试 ==========\n");
    char str1[] = "Hello World! 123";
    printf("原始字符串: %s\n", str1);
    
    str_to_lower(str1);
    printf("转小写: %s\n", str1);

    str_to_upper(str1);
    printf("转大写: %s\n", str1);

    str_reverse(str1);
    printf("反转: %s\n", str1);

    str_to_lower2(str1);
    printf("转小写2: %s\n", str1);

    str_to_upper2(str1);
    printf("转大写2: %s\n", str1);

    str_reverse2(str1);
    printf("反转2: %s\n", str1);

    printf("尾部字符: %c\n", *(getTail(str1)-1));
    
    printf("\n========== 进制转换测试 ==========\n");
    // 字符串转数字
    printf("二进制字符串\"1010\"转数字: %ld\n", str_to_int("1010", 2));
    printf("十六进制字符串\"FF\"转数字: %ld\n", str_to_int("FF", 16));
    printf("十进制字符串\"-123\"转数字: %ld\n", str_to_int("-123", 10));
    printf("七进制字符串\"-123\"转数字: %ld\n", str_to_int("-123", 7));
    printf("三十五进制字符串\"-x3e\"转数字: %ld\n", str_to_int("-x3e", 35));
    
    // 数字转字符串
    char buffer[65];
    printf("255转二进制: %s\n", int_to_str(255, buffer, 2));
    printf("255转八进制: %s\n", int_to_str(255, buffer, 8));
    printf("255转十六进制: %s\n", int_to_str(255, buffer, 16));
    printf("-123转十进制: %s\n", int_to_str(-123, buffer, 10));
    printf("-22123转七进制: %s\n", int_to_str(-22123, buffer, 7));
    printf("654321转二十九进制: %s\n", int_to_str(654321, buffer, 29));
    
    printf("\n========== 排序算法测试 ==========\n");
    int arr[] = {64, 34, 25, 12, 22, 11, 90, -5, 16, 32};
    int n = sizeof(arr)/sizeof(arr[0]);
    int arr_copy[n];
    
    // 冒泡排序
    for(int i = 0; i < n; i++) arr_copy[i] = arr[i];
    bubble_sort(arr_copy, n);
    printf("冒泡排序: ");
    for(int i = 0; i < n; i++) printf("%d ", arr_copy[i]);
    printf("\n");
    
    // 选择排序
    for(int i = 0; i < n; i++) arr_copy[i] = arr[i];
    selection_sort(arr_copy, n);
    printf("选择排序: ");
    for(int i = 0; i < n; i++) printf("%d ", arr_copy[i]);
    printf("\n");
    
    // 插入排序
    for(int i = 0; i < n; i++) arr_copy[i] = arr[i];
    insertion_sort(arr_copy, n);
    printf("插入排序: ");
    for(int i = 0; i < n; i++) printf("%d ", arr_copy[i]);
    printf("\n");
    
    // 快速排序
    for(int i = 0; i < n; i++) arr_copy[i] = arr[i];
    quick_sort(arr_copy, 0, n-1);
    printf("快速排序: ");
    for(int i = 0; i < n; i++) printf("%d ", arr_copy[i]);
    printf("\n");
    
    // 堆排序
    for(int i = 0; i < n; i++) arr_copy[i] = arr[i];
    heap_sort(arr_copy, n);
    printf("堆排序: ");
    for(int i = 0; i < n; i++) printf("%d ", arr_copy[i]);
    printf("\n");

    printf("\n========== 归并排序测试 ==========\n");

    // 归并排序（递归）

    int arr2[] = {38, 27, 43, 3, 9, 82, 10};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    int arr2_copy[n2];

    for(int i = 0; i < n2; i++) arr2_copy[i] = arr2[i];
    printf("原始数组: ");
    for(int i = 0; i < n2; i++) printf("%d ", arr2_copy[i]);
    printf("\n");

    merge_sort(arr2_copy, n2);
    printf("递归归并排序: ");
    for(int i = 0; i < n2; i++) printf("%d ", arr2_copy[i]);
    printf("\n");

    // 归并排序（迭代）
    for(int i = 0; i < n2; i++) arr2_copy[i] = arr2[i];
    merge_sort_iterative(arr2_copy, n2);
    printf("迭代归并排序: ");
    for(int i = 0; i < n2; i++) printf("%d ", arr2_copy[i]);
    printf("\n");

    // 测试随机数组
    printf("\n随机数组排序测试:\n");
    const int RAND_SIZE = 100;
    int rand_arr[RAND_SIZE];
    for(int i = 0; i < RAND_SIZE; i++) {
        rand_arr[i] = rand() % 100;
    }

    int rand_copy[RAND_SIZE];
    printf("随机数组: ");
    for(int i = 0; i < RAND_SIZE; i++) printf("%d ", rand_arr[i]);
    printf("\n");

    for(int i = 0; i < RAND_SIZE; i++) rand_copy[i] = rand_arr[i];
    merge_sort(rand_copy, RAND_SIZE);
    printf("归并排序结果: ");
    for(int i = 0; i < RAND_SIZE; i++) printf("%d ", rand_copy[i]);
    printf("\n");

    // 验证排序正确性
    bool sorted = true;
    for(int i = 0; i < RAND_SIZE - 1; i++) {
        if(rand_copy[i] > rand_copy[i + 1]) {
            sorted = false;
            break;  
        }
    }
    printf("排序验证: %s\n", sorted ? "正确" : "错误");

    // 与原数组的其他排序算法比较
    printf("\n与其他排序算法结果比较:\n");

    // 快速排序
    for(int i = 0; i < RAND_SIZE; i++) rand_copy[i] = rand_arr[i];
    quick_sort(rand_copy, 0, RAND_SIZE - 1);
    printf("快速排序结果: ");
    for(int i = 0; i < RAND_SIZE; i++) printf("%d ", rand_copy[i]);
    printf("\n");

    // 堆排序
    for(int i = 0; i < RAND_SIZE; i++) rand_copy[i] = rand_arr[i];
    heap_sort(rand_copy, RAND_SIZE);
    printf("堆排序结果:   ");
    for(int i = 0; i < RAND_SIZE; i++) printf("%d ", rand_copy[i]);
    printf("\n");
    
    printf("\n========== 素数判断测试 ==========\n");
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int non_primes[] = {1, 4, 6, 8, 9, 10, 12, 14, 15, 16};
    
    printf("素数测试:\n");
    for(int i = 0; i < 10; i++) {
        printf("%2d: simple=%d, sqrt=%d, 6k=%d, Miller=%d\n", 
               primes[i],
               is_prime_simple(primes[i]),
               is_prime_sqrt(primes[i]),
               is_prime_6k(primes[i]),
               is_prime_miller_rabin(primes[i]));
    }
    
    printf("\n非素数测试:\n");
    for(int i = 0; i < 10; i++) {
        printf("%2d: simple=%d, sqrt=%d, 6k=%d, Miller=%d\n", 
               non_primes[i],
               is_prime_simple(non_primes[i]),
               is_prime_sqrt(non_primes[i]),
               is_prime_6k(non_primes[i]),
               is_prime_miller_rabin(non_primes[i]));
    }
    
    printf("\n========== 回文数判断测试 ==========\n");
    int palindrome_nums[] = {121, 12321, 1234321, 1221};
    int non_palindrome_nums[] = {123, 1234, -121, 10, 669669};
    
    printf("回文数测试:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d: %s\n", palindrome_nums[i], 
               is_palindrome_int(palindrome_nums[i]) ? "true" : "false");
    }
    
    printf("\n非回文数测试:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d: %s\n", non_palindrome_nums[i], 
               is_palindrome_int(non_palindrome_nums[i]) ? "true" : "false");
    }
    
    char* palindrome_strs[] = {"madam", "racecar", "level", "a"};
    char* non_palindrome_strs[] = {"hello", "world", "abc", ""};
    
    printf("\n回文字符串测试:\n");
    for(int i = 0; i < 4; i++) {
        printf("%s: %s\n", palindrome_strs[i], 
               is_palindrome_str(palindrome_strs[i]) ? "true" : "false");
    }
    
    printf("\n========== 单向链表测试 ==========\n");
    SinglyLinkedList sll;
    
    printf("在尾部追加: 1, 2, 3, 4, 5\n");
    for(int i = 1; i <= 5; i++) {
        sll.push_back(i);
    }
    printf("链表内容: ");
    sll.print();
    printf("链表大小: %d\n", sll.get_size());
    
    printf("在头部追加: 0\n");
    sll.push_front(0);
    printf("链表内容: ");
    sll.print();
    
    printf("反转链表\n");
    sll.reverse();
    printf("链表内容: ");
    sll.print();
    
    printf("在序号2插入: 99\n");
    sll.insert_at(2, 99);
    printf("链表内容: ");
    sll.print();
    
    printf("删除序号3的元素\n");
    sll.remove_at(3);
    printf("链表内容: ");
    sll.print();
    
    printf("删除值为99的元素\n");
    sll.remove_value(99);
    printf("链表内容: ");
    sll.print();
    
    printf("排序链表\n");
    sll.sort();
    printf("链表内容: ");
    sll.print();
    
    printf("查找元素3: ");
    SinglyNode* found = sll.find(3);
    if(found) printf("找到，值为%d\n", found->data);
    else printf("未找到\n");
    
    printf("\n========== 双向链表测试 ==========\n");
    DoublyLinkedList dll;
    
    printf("在尾部追加: 10, 20, 30, 40, 50\n");
    for(int i = 1; i <= 5; i++) {
        dll.push_back(i * 10);
    }
    printf("正向打印: ");
    dll.print_forward();
    printf("反向打印: ");
    dll.print_backward();
    printf("链表大小: %d\n", dll.get_size());
    
    printf("在头部追加: 0\n");
    dll.push_front(0);
    printf("正向打印: ");
    dll.print_forward();
    
    printf("反转链表\n");
    dll.reverse();
    printf("正向打印: ");
    dll.print_forward();
    
    printf("在序号3插入: 35\n");
    dll.insert_at(3, 35);
    printf("正向打印: ");
    dll.print_forward();
    
    printf("删除序号2的元素\n");
    dll.remove_at(2);
    printf("正向打印: ");
    dll.print_forward();
    
    printf("删除值为35的元素\n");
    dll.remove_value(35);
    printf("正向打印: ");
    dll.print_forward();
    
    printf("排序链表\n");
    dll.sort();
    printf("正向打印: ");
    dll.print_forward();
    printf("反向打印: ");
    dll.print_backward();
    
    printf("查找元素40: ");
    DoublyNode* dll_found = dll.find(40);
    if(dll_found) printf("找到，值为%d\n", dll_found->data);
    else printf("未找到\n");
    
    printf("\n========== 性能测试对比 ==========\n");
    // 测试不同素数判断方法的性能
    int test_num = 2147483647; // 一个大质数
    printf("测试数字: %d\n", test_num);
    
    clock_t start, end;
    double cpu_time_used;
    
    // 注意：简单方法会很慢，所以注释掉
    /*start = clock();
    bool result1 = is_prime_simple(test_num);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("简单方法: %s (耗时: %.6f秒)\n", 
           result1 ? "素数" : "非素数", cpu_time_used);*/
    
    start = clock();
    bool result2 = is_prime_sqrt(test_num);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("sqrt方法: %s (耗时: %.6f秒)\n", 
           result2 ? "素数" : "非素数", cpu_time_used);
    
    start = clock();
    bool result3 = is_prime_6k(test_num);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("6k方法: %s (耗时: %.6f秒)\n", 
           result3 ? "素数" : "非素数", cpu_time_used);
    
    start = clock();
    bool result4 = is_prime_miller_rabin(test_num, 5);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Miller-Rabin: %s (耗时: %.6f秒)\n", 
           result4 ? "素数" : "非素数", cpu_time_used);
    
    printf("\n========== 测试完成 ==========\n");
    
    return 0;
}