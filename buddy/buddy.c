/*
 * Copyright (c)  Fantasy Corporation 2019-2019. All rights reserved.
 * Description: 模拟Linux内核内存管理伙伴算法，主要API
 * Author: chen
 * Create: 2019-08-30
 */

#include "buddy.h"

// 指针数组
MemNode* g_list[MAX_LIST];
// 链表对应的位图
int g_bit[MAX_LIST][MAX_BIT_LENGTH] = {0};
// 连续内存块首地址
int g_memTemp = 0;
// 地址与块大小指数对应数组
int g_addrToOrder[MAX_ADDR_TO_ORD_INDEX + 1][ADDR_TO_ORD_LENGTH] = {0};
// 地址与指数对应关系数组索引值
int g_initATO = 0;

/*
 * 功能说明：根据内存地址计算内存块指数
 * 返回值：内存块指数（order）
 */
int AddrToOrder(int n)
{
    int order = 0;
    for (int i = 0; i <= MAX_ADDR_TO_ORD_INDEX; i++) {
        if (n == g_addrToOrder[i][0]) {
            order = g_addrToOrder[i][1];
            break;
        }
    }
    return order;
}

/*
 * 功能说明：创建一段连续空闲内存并初始化链表
 */
void Create()
{
    // 初始申请内存的首地址
    char* mem;
    // 固定分配内存大小字节32k*1024=32768
    const int N = INIT_MEM_SIZE;
    mem = (int*)malloc(N);
    // 记录初始首地址
    g_memTemp = (uintptr_t)mem;
    // 头结点记录对应链表快大小单位为b
    for (int i = 0; i < MAX_LIST; i++) {
        const int SIZE = MEM_SIZE * pow(ORDER_BASE, i);
        g_list[i] = ListInit(SIZE);
    }
    ListTailInsert(g_list[MAX_LIST_INDEX], g_memTemp);
    printf("create ok------");
}

/*
 * 功能说明：申请分配n（k）的内存
 * 返回值：申请到的内存块首地址
 */
int Alloc(int n)
{
    // 所在的链表索引值
    int order = 0;
    // 申请成功返回内存首地址
    int p = 0;
    for (int i = 0; i < MAX_LIST - 1; i++) {
        if (n == BUDDY_MEM_SIZE * pow(ORDER_BASE, i)) {
            order = i;
        }
        if (n > BUDDY_MEM_SIZE * pow(ORDER_BASE, i) && n <= BUDDY_MEM_SIZE * pow(ORDER_BASE, i + 1)) {
            order = i + 1;
        }
    }
    int initOrder = order;
    int finalOrder = 0;
    // 找到可用的内存块
    for (int i = order; i <= MAX_LIST - 1; i++) {
        if ((g_list[i]->next) != NULL) {
            p = g_list[i]->next->data;
            finalOrder = i;
            break;
        }
        if ((i == MAX_LIST - 1) && (g_list[i]->next) == NULL) {
            printf("no free mem\n");
            return;
        }
    }
    // 找到物理首地址为p的内存块，将其从链表中删除
    g_list[finalOrder] = DelSpecificVar(g_list[finalOrder], p);
    // 修改摘除的内存块对应的位图值
    int index = ((p - g_memTemp) / MEM_SIZE) >> (1 + finalOrder);
    g_bit[finalOrder][index] = g_bit[finalOrder][index] ^ 1;
    // 拆分重构链表
    // 修改对应位图值
    int step = finalOrder - initOrder;
    int pTemp = p;
    for (int i = 1; i <= step; i++) {
        int index;
        const int MEMSTEP = MEM_SIZE * pow(ORDER_BASE, finalOrder - i);
        int pNew = pTemp + MEMSTEP;
        // 更新链表
        ListTailInsert(g_list[finalOrder - i], pNew);
        // 更新位图
        index = ((pNew - g_memTemp) / MEM_SIZE) >> (1 + finalOrder - i);
        g_bit[finalOrder - i][index] = g_bit[finalOrder - i][index] ^ 1;
    }
    // 记录分配的内存块大小
    g_addrToOrder[g_initATO][0] = p;
    g_addrToOrder[g_initATO][1] = initOrder;
    g_initATO++;
    printf("alloc ok------");
    return p;
}

/*
 * 功能说明：释放首地址为n的内存块
 */
void MemFree(int n)
{
    int index;       // 位图索引
    int number;      // 地址偏移后的地址，用于计算位图索引
    int indexToNum;  // 物理顺序序号0,1,2,3,...用于判断伙伴块位置
    int stepTemp;    // 每次偏移的大小
    // 查看位图数值判断伙伴快状态
    int newN;
    int order = AddrToOrder(n);
    for (int i = order; i <= MAX_LIST - 1; i++) {
        int testTemp = n - g_memTemp;
        number = testTemp / MEM_SIZE;
        index = (number) >> (1 + i);
        // 伙伴块被占用
        if (g_bit[i][index] == 0) {
            g_bit[i][index] = g_bit[i][index] ^ 1;
            ListTailInsert(g_list[i], n);
            break;
        }
        // 伙伴块空闲
        if (g_bit[i][index] == 1) {
            indexToNum = testTemp / (MEM_SIZE * pow(ORDER_BASE, i));
            // 判断伙伴块位置
            // 伙伴块在右
            if (indexToNum % CHECK_LEFT_OR_RIGHT == 0) {
                stepTemp = MEM_SIZE * pow(ORDER_BASE, i);
                newN = n + stepTemp;
                g_bit[i][index] = g_bit[i][index] ^ 1;
                DelSpecificVar(g_list[i], newN);
            }
            // 伙伴块在左
            if (indexToNum % CHECK_LEFT_OR_RIGHT == 1) {
                stepTemp = MEM_SIZE * pow(ORDER_BASE, i);
                newN = n - stepTemp;
                g_bit[i][index] = g_bit[i][index] ^ 1;
                DelSpecificVar(g_list[i], newN);
            }
            n = newN;
        }
    }
    printf("free ok------");
}