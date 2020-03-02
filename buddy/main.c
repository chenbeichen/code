/*
 * Copyright (c)  Fantasy Corporation 2019-2019. All rights reserved.
 * Description: 模拟Linux内核内存管理伙伴算法，主函数，用于测试
 * Author: chen 
 * Create: 2019-08-30
 */

#include <stdio.h>
#include "buddy.c"

/*
 * 功能说明：打印bit信息
 */
void BitPrint()
{
    printf("bit---\n");
    for (int i = 0; i < MAX_LIST_INDEX; i++) {
        for (int j = 0; j < BUDDY_MEM_SIZE / pow(ORDER_BASE, i); j++) {
            printf("%d ", g_bit[i][j]);
        }
        printf("\n");
    }
}

/*
 * 功能说明：test1，连续分配内存3k-3k-3k-3k，内存足够分配
 */
void Test1()
{
    Create();
    printf("new mem from %d\n", g_memTemp);

    int test1MemP0 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", test1MemP0);
    BitPrint();

    int test1MemP1 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", test1MemP1);
    BitPrint();

    int test1MemP2 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", test1MemP2);
    BitPrint();

    int test1MemP3 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", test1MemP3);
    BitPrint();
}

/*
 * 功能说明：test2，连续分配内存3k-3k-5k-5k-10k-10k-30k-30k，内存不够分配
 */
void Test2()
{
    Create();
    printf("new mem from %d\n", g_memTemp);

    int test2Mem3P0 = Alloc(TEST_MEM_LENGTH_THREE);
    if (test2Mem3P0 != 0) {
        printf("alloc 3k mem from %d\n", test2Mem3P0);
        BitPrint();
    } else {
        printf("------\n");
    }

    int test2Mem3P1 = Alloc(TEST_MEM_LENGTH_THREE);
    if (test2Mem3P1 != 0) {
        printf("alloc 3k mem from %d\n", test2Mem3P1);
        BitPrint();
    } else {
        printf("------\n");
    }

    int test2Mem5P0 = Alloc(TEST_MEM_LENGTH_FIVE);
    if (test2Mem5P0 != 0) {
        printf("alloc 5k mem from %d\n", test2Mem5P0);
        BitPrint();
    } else {
        printf("------\n");
    }

    int test2Mem5P1 = Alloc(TEST_MEM_LENGTH_FIVE);
    if (test2Mem5P1 != 0) {
        printf("alloc 5k mem from %d\n", test2Mem5P1);
        BitPrint();
    } else {
        printf("------\n");
    }

    int test2Mem10P0 = Alloc(TEST_MEM_LENGTH_TEN);
    if (test2Mem10P0 != 0) {
        printf("alloc 10k mem from %d\n", test2Mem10P0);
        BitPrint();
    } else {
        printf("------\n");
    }

    int test2Mem10P1 = Alloc(TEST_MEM_LENGTH_TEN);
    if (test2Mem10P1 != 0) {
        printf("alloc 10k mem from %d\n", test2Mem10P1);
        BitPrint();
    } else {
        printf("------\n");
    }

    int test2Mem30P0 = Alloc(TEST_MEM_LENGTH_THIRTY);
    if (test2Mem30P0 != 0) {
        printf("alloc 30k mem from %d\n", test2Mem30P0);
        BitPrint();
    } else {
        printf("------\n");
    }

    int test2Mem30P1 = Alloc(TEST_MEM_LENGTH_THIRTY);
    if (test2Mem30P1 != 0) {
        printf("alloc 30k mem from %d\n", test2Mem30P1);
        BitPrint();
    } else {
        printf("------\n");
    }
}

/*
 * 功能说明：主函数，连续分配内存3-3-5-5-3-3，连续释放3-3-5-5-3-3，正常分配，正常释放
 */
int main()
{
    Create();
    printf("new mem from %d\n", g_memTemp);
    
    int memP0 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", (memP0 - g_memTemp) / MEM_SIZE);
    BitPrint();
    int memP1 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", (memP1 - g_memTemp) / MEM_SIZE);
    BitPrint();

    int memP2 = Alloc(TEST_MEM_LENGTH_FIVE);
    printf("alloc 5k mem from %d\n", (memP2 - g_memTemp) / MEM_SIZE);
    BitPrint();
    int memP3 = Alloc(TEST_MEM_LENGTH_FIVE);
    printf("alloc 5k mem from %d\n", (memP3 - g_memTemp) / MEM_SIZE);
    BitPrint();

    int memP4 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", (memP4 - g_memTemp) / MEM_SIZE);
    BitPrint();
    int memP5 = Alloc(TEST_MEM_LENGTH_THREE);
    printf("alloc 3k mem from %d\n", (memP5 - g_memTemp) / MEM_SIZE);
    BitPrint();

    MemFree(memP0);
    printf("mem_p0 free %d\n", (memP0 - g_memTemp) / MEM_SIZE);
    BitPrint();
    MemFree(memP1);
    printf("mem_p1 free %d\n", (memP1 - g_memTemp) / MEM_SIZE);
    BitPrint();

    MemFree(memP2);
    printf("mem_p2 free %d\n", (memP2 - g_memTemp) / MEM_SIZE);
    BitPrint();
    MemFree(memP3);
    printf("mem_p3 free %d\n", (memP3 - g_memTemp) / MEM_SIZE);
    BitPrint();

    MemFree(memP4);
    printf("mem_p4 free %d\n", (memP4 - g_memTemp) / MEM_SIZE);
    BitPrint();
    MemFree(memP5);
    printf("mem_p5 free %d\n", (memP5 - g_memTemp) / MEM_SIZE);
    BitPrint();
}