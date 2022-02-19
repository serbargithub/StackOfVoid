#include "gtest/gtest.h"
#include "stack_of_void.h"

#define ITEMS_MAX  3

StackItem_t g_testStack[ITEMS_MAX];
StackOfVoid_t g_Stack;

uint32_t item1 = 1, item2 = 2, item3 = 3, itemOdd = 99;

void StackErorrHandler(uint32_t stackID, StackResults_t result)
{
	printf("\r\n###### Into stack with ID: %i catched an error %i ####\r\n\r\n", stackID, result);
}

void GlobalStackInit() {

	g_Stack.pFirstItem = g_testStack;
	g_Stack.sizeMax = ITEMS_MAX;
	g_Stack.errorCallback = StackErorrHandler;
	g_Stack.stackID = 0;
}

TEST(StackOfVoid, Reset) {

  GlobalStackInit();
  EXPECT_EQ(STACK_RESULT_OK, StackOfVoid__Reset(&g_Stack));
  g_Stack.pFirstItem = NULL;
  EXPECT_EQ(STACK_IS_NOT_INITED, StackOfVoid__Reset(&g_Stack));

  EXPECT_EQ(STACK_IS_NOT_INITED, StackOfVoid__Reset(NULL));

  GlobalStackInit();
  EXPECT_EQ(STACK_RESULT_OK, StackOfVoid__Reset(&g_Stack));
  g_Stack.sizeMax = 0;
  EXPECT_EQ(STACK_IS_NOT_INITED, StackOfVoid__Reset(&g_Stack));
}

TEST(StackOfVoid, IsEmpty) {

	GlobalStackInit();
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&g_Stack));
	StackOfVoid__Push(&g_Stack, (StackItem_t)item1);
	EXPECT_EQ(false, StackOfVoid__IsEmpty(&g_Stack));

}

TEST(StackOfVoid, OnePushPop) {

	GlobalStackInit();
	StackOfVoid__Reset(&g_Stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&g_Stack));
	StackOfVoid__Push(&g_Stack, (StackItem_t)item1);
	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(checkedItem, item1);
	printf(" Checked Item: %i Item %i ", checkedItem, item1);
}

TEST(StackOfVoid, TwoPushPop) {

	GlobalStackInit();
	StackOfVoid__Reset(&g_Stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&g_Stack));
	StackOfVoid__Push(&g_Stack, (StackItem_t)item1);
	StackOfVoid__Push(&g_Stack, (StackItem_t)item2);

	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(checkedItem, item2);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(checkedItem, item1);

}

TEST(StackOfVoid, ThreePushPop) {

	GlobalStackInit();
	StackOfVoid__Reset(&g_Stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&g_Stack));
	StackOfVoid__Push(&g_Stack, (StackItem_t)item1);
	StackOfVoid__Push(&g_Stack, (StackItem_t)item2);
	StackOfVoid__Push(&g_Stack, (StackItem_t)item3);

	EXPECT_EQ(g_Stack.sizeActual, 3);

	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(checkedItem, item3);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(checkedItem, item2);
	EXPECT_EQ(g_Stack.sizeActual, 2);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(checkedItem, item1);
	EXPECT_EQ(g_Stack.sizeActual, 1);
	checkedItem = 5;
	StackResults_t result = StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(STACK_EMPTY, result);
	EXPECT_EQ(g_Stack.sizeActual, 0);
	EXPECT_EQ(checkedItem, 5);

}

TEST(StackOfVoid, FourPushPop) {

	StackResults_t result;
	GlobalStackInit();
	StackOfVoid__Reset(&g_Stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&g_Stack));
	StackOfVoid__Push(&g_Stack, (StackItem_t)item1);
	StackOfVoid__Push(&g_Stack, (StackItem_t)item2);
	result = StackOfVoid__Push(&g_Stack, (StackItem_t)item3);
	EXPECT_EQ(STACK_RESULT_OK, result);
	result= StackOfVoid__Push(&g_Stack, (StackItem_t)itemOdd);
	EXPECT_EQ(STACK_IS_FULL_ERROR, result);
	EXPECT_EQ(g_Stack.sizeActual, 3);

	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(checkedItem, item1);
	EXPECT_EQ(g_Stack.sizeActual, 1);
	checkedItem = 5;
	result = StackOfVoid__Pop((StackItem_t*)&checkedItem, &g_Stack);
	EXPECT_EQ(STACK_EMPTY, result);
	EXPECT_EQ(g_Stack.sizeActual, 0);
	EXPECT_EQ(checkedItem, 5);
}

TEST(StackOfVoid, GetByIndex) {

	StackResults_t result;
	uint32_t checkedItem = 0;
	GlobalStackInit();
	StackOfVoid__Reset(&g_Stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&g_Stack));
	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &g_Stack, 1);
	EXPECT_EQ(STACK_OUT_OF_SCOPE_ERROR, result);

	StackOfVoid__Push(&g_Stack, (StackItem_t)item1);
	StackOfVoid__Push(&g_Stack, (StackItem_t)item2);
	StackOfVoid__Push(&g_Stack, (StackItem_t)item3);
	StackOfVoid__Push(&g_Stack, (StackItem_t)itemOdd);
	EXPECT_EQ(g_Stack.sizeActual, 3);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &g_Stack, 1);
	EXPECT_EQ(STACK_RESULT_OK, result);
	EXPECT_EQ(checkedItem, item1);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &g_Stack, 2);
	EXPECT_EQ(STACK_RESULT_OK, result);
	EXPECT_EQ(checkedItem, item2);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &g_Stack, 3);
	EXPECT_EQ(STACK_RESULT_OK, result);
	EXPECT_EQ(checkedItem, item3);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &g_Stack, 4);
	EXPECT_EQ(STACK_OUT_OF_SCOPE_ERROR, result);


}