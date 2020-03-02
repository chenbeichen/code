/*
 * Copyright (c)  Fantasy Corporation 2019-2019. All rights reserved.
 * Description: 模拟Linux内核内存管理伙伴算法，相关链表操作
 * Author: chen
 * Create: 2019-08-30
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define INIT_MEM_SIZE 32768
#define MAX_ADDR_TO_ORD_INDEX 11
#define MAX_BIT_LENGTH 4
#define MAX_LIST 4
#define BUDDY_MEM_SIZE 4
#define MAX_LIST_INDEX 3
#define MEM_SIZE 4096
#define ORDER_BASE 2
#define CHECK_LEFT_OR_RIGHT 2
#define TEST_MEM_LENGTH_THREE 3
#define TEST_MEM_LENGTH_FIVE 5
#define TEST_MEM_LENGTH_TEN 10
#define TEST_MEM_LENGTH_THIRTY 30
#define ADDR_TO_ORD_LENGTH 2

typedef struct MemNode {
    int data;
    struct MemNode* next;
} MemNode, *pNode;

// 单链表相关操作
MemNode* ListInit(int var)
{
    // 创建根节点
    MemNode* head = (MemNode*)malloc(sizeof(MemNode));
    if (head == NULL) {
        printf("错误。申请内存失败，创建节点失败\n");
    }
    // 初始化头节点
    head->data = var;
    head->next = NULL;
    return head;
}

// 尾部插入
int ListTailInsert(MemNode* listHead, int data)
{
    MemNode* listNewNode = (MemNode*)malloc(sizeof(MemNode));
    if (listNewNode == NULL) {
        printf("error,malloc failed\n");
        return -1;
    }
    while ((listHead->next) != NULL) {
        listHead = listHead->next;
    }
    // 将值给该节点，并将上一个节点的指针域指向该节点地址
    listNewNode->data = data;
    listNewNode->next = NULL;
    listHead->next = listNewNode;
    return 0;
}
// 头部插入
MemNode* ListHeadInsert(MemNode* listHead, int data)
{
    MemNode* listNewNode = (MemNode*)malloc(sizeof(MemNode));

    if (listNewNode == NULL) {
        printf("error,malloc failed\n");
        return NULL;
    }

    listNewNode->next = listHead;
    listNewNode->data = data;
    listHead = listNewNode;

    return listHead;
}

// 删除链表中的指定元素
MemNode* DelSpecificVar(MemNode* listHead, int delVar)
{
    MemNode* listTemp = NULL;
    MemNode* listHeadTemp = listHead;

    while (listHead != NULL) {
        if (listHead->data == delVar) {
            // 如果删除的是头结点
            if (listTemp == NULL) {
                listTemp = listHead;
                listHead = listHead->next;
                free(listTemp);

                return listHead;
            } else {
                // 删除的不是头结点
                listTemp->next = listHead->next;
                free(listHead);
                return listHeadTemp;
            }
        }
        listTemp = listHead;
        listHead = listHead->next;
    }
    return listHeadTemp;
}

MemNode* ListSearch(MemNode* pFirst, int data)
{
    for (MemNode* cur = pFirst; cur != NULL; cur = cur->next) {
        if (cur->data == data) {
            return cur;
        }
    }
    return NULL;
}