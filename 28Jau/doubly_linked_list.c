#include <my_header.h>
// DoubleList.h
#pragma once

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct DoubleList {
    struct Node* head;
    struct Node* tail;
};

// 创建空的双向链表
DoubleList* DoubleList_Create() {
    struct DoubleList *pList = (struct DoubleList*)calloc(1,sizeof(struct DoubleList));
    return pList;
}

// 判空
bool DoubleList_Empty(struct DoubleList* list) {
    return list->head == NULL;
}

// 销毁双向链表
void DoubleList_Destroy(struct DoubleList* list) {
    if (DoubleList_Empty(list)) {
        return;
    }
    struct Node* tmp = list->head;
    struct Node* cur = tmp->next;
    // 删除到只剩一个结点
    while (cur) {
        tmp->next = tmp->prev = NULL;
        free(tmp);
        tmp = cur;
        cur = cur->next;
    }
    // 删除最后一个结点
    tmp->next = tmp->prev = NULL;
    free(tmp);

    // 清理头指针
    list->head = list->tail = NULL;
    free(list);
}


// 遍历双向链表并按下面格式打印
// 9 --> 5 --> 2 --> 7
void DoubleList_Display(struct DoubleList* list) {
    if (DoubleList_Empty(list)) {
        printf("The list is empty.\n");
        return;
    }
    struct Node* tmp = list->head;
    // print 前n-1个
    while(tmp->next) {
        printf("%d ---> ", tmp->data);
        tmp = tmp->next;
    }
    // print 第n个
    printf("%d\n", tmp->data);
}

// 头插
void DoubleList_Insert1(struct DoubleList* list, int value) {
    // creat a new node
    struct Node* pnew = (struct Node*)calloc(1,sizeof(struct Node));
    pnew->data = value;

    // 如果插入的是第一个结点
    if (list->head == NULL) {
        list->head = list->tail = pnew;
        return;
    }
    
    pnew->next = list->head;
    list->head->prev = pnew;
    list->head = pnew;
}

// 尾插
void DoubleList_Insert2(struct DoubleList* list, int value) {
    // creat a new node
    struct Node* pnew = (struct Node*)calloc(1,sizeof(struct Node));
    pnew->data = value;

    // first node
    if (list->head == NULL) {
        list->head = list->tail = pnew;
        return;
    }

    // remain node
    pnew->prev = list->tail;
    list->tail->next = pnew;
    list->tail = pnew;
    
}

// 头删
void DoubleList_Delete1(struct DoubleList* list) {
    if (DoubleList_Empty(list)) {
        return;
    }
    // There is only one node in the list;
    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
        return;
    }
    // There are at least two nodes in the list.
    struct Node* tmp = list->head;
    list->head =  list->head->next;
    list->head->prev = NULL;
    free(tmp);
}

/* Usage:  */
int main(int argc, char *argv[]){                                  
    printf("Hello world\n");
    return 0;
}

