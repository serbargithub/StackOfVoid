#include "gtest/gtest.h"
#include "stack_of_void.h"

#define ITEMS_MAX  3

StackItem_t g_testStack[ITEMS_MAX];

uint32_t item1 = 1, item2 = 2, item3 = 3, itemOdd = 99;

void StackErorrHandler(uint32_t stackID, StackResults_t result) {
	printf("\r\n###### Into stack with ID: %i catched an error %i ####\r\n\r\n", stackID, result);
}

void StackInit(StackOfVoid_t* stack) {
	stack->pFirstItem = g_testStack;
	stack->sizeMax = ITEMS_MAX;
	stack->errorCallback = StackErorrHandler;
}

TEST(StackOfVoid, Reset_StackInited) {
	StackOfVoid_t stack;
	StackInit(&stack);
	stack.stackID = 1;
	EXPECT_EQ(STACK_RESULT__OK, StackOfVoid__Reset(&stack));
}

TEST(StackOfVoid, Reset_StackNotInited) {
	EXPECT_EQ(STACK_RESULT__IS_NOT_INITED, StackOfVoid__Reset(NULL));

	StackOfVoid_t stack;
	StackInit(&stack);
	stack.stackID = 1;
	EXPECT_EQ(STACK_RESULT__OK, StackOfVoid__Reset(&stack));
	stack.pFirstItem = NULL;
	EXPECT_EQ(STACK_RESULT__IS_NOT_INITED, StackOfVoid__Reset(&stack));

	StackInit(&stack);
	EXPECT_EQ(STACK_RESULT__OK, StackOfVoid__Reset(&stack));
	stack.sizeMax = 0;
	EXPECT_EQ(STACK_RESULT__IS_NOT_INITED, StackOfVoid__Reset(&stack));
}

TEST(StackOfVoid, IsEmpty) {
	StackOfVoid_t stack;
	StackInit(&stack);
	stack.stackID = 2;
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&stack));
	StackOfVoid__Push(&stack, (StackItem_t)item1);
	EXPECT_EQ(false, StackOfVoid__IsEmpty(&stack));
}

TEST(StackOfVoid, OnePushPop) {
	StackOfVoid_t stack;
	StackInit(&stack);
	stack.stackID = 3;
	StackOfVoid__Reset(&stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&stack));
	StackOfVoid__Push(&stack, (StackItem_t)item1);
	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(checkedItem, item1);
}

TEST(StackOfVoid, TwoPushPop) {
	StackOfVoid_t stack;
	StackInit(&stack);
	stack.stackID = 4;
	StackOfVoid__Reset(&stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&stack));
	StackOfVoid__Push(&stack, (StackItem_t)item1);
	StackOfVoid__Push(&stack, (StackItem_t)item2);

	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(checkedItem, item2);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(checkedItem, item1);
}

TEST(StackOfVoid, ThreePushPop) {
	StackOfVoid_t stack;
	StackInit(&stack);
	stack.stackID = 5;
	StackOfVoid__Reset(&stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&stack));
	StackOfVoid__Push(&stack, (StackItem_t)item1);
	StackOfVoid__Push(&stack, (StackItem_t)item2);
	StackOfVoid__Push(&stack, (StackItem_t)item3);

	EXPECT_EQ(stack.sizeActual, 3);

	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(checkedItem, item3);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(checkedItem, item2);
	EXPECT_EQ(stack.sizeActual, 2);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(checkedItem, item1);
	EXPECT_EQ(stack.sizeActual, 1);
	checkedItem = 5;
	StackResults_t result = StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(STACK_RESULT__IS_EMPTY, result);
	EXPECT_EQ(stack.sizeActual, 0);
	EXPECT_EQ(checkedItem, 5);
}

TEST(StackOfVoid, FourPushPop) {
	StackOfVoid_t stack;
	StackResults_t result;
	StackInit(&stack);
	stack.stackID = 6;
	StackOfVoid__Reset(&stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&stack));
	StackOfVoid__Push(&stack, (StackItem_t)item1);
	StackOfVoid__Push(&stack, (StackItem_t)item2);
	result = StackOfVoid__Push(&stack, (StackItem_t)item3);
	EXPECT_EQ(STACK_RESULT__OK, result);
	result= StackOfVoid__Push(&stack, (StackItem_t)itemOdd);
	EXPECT_EQ(STACK_RESULT__OVERFULL_ERROR, result);
	EXPECT_EQ(stack.sizeActual, 3);

	uint32_t checkedItem = 0;
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(checkedItem, item1);
	EXPECT_EQ(stack.sizeActual, 1);
	checkedItem = 5;
	result = StackOfVoid__Pop((StackItem_t*)&checkedItem, &stack);
	EXPECT_EQ(STACK_RESULT__IS_EMPTY, result);
	EXPECT_EQ(stack.sizeActual, 0);
	EXPECT_EQ(checkedItem, 5);
}

TEST(StackOfVoid, GetByIndex) {
	uint32_t checkedItem = 0;
	StackOfVoid_t stack;
	StackResults_t result;
	StackInit(&stack);
	stack.stackID = 7;
	StackOfVoid__Reset(&stack);
	EXPECT_EQ(true, StackOfVoid__IsEmpty(&stack));
	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &stack, 1);
	EXPECT_EQ(STACK_RESULT__OUT_OF_SCOPE_ERROR, result);

	StackOfVoid__Push(&stack, (StackItem_t)item1);
	StackOfVoid__Push(&stack, (StackItem_t)item2);
	StackOfVoid__Push(&stack, (StackItem_t)item3);
	StackOfVoid__Push(&stack, (StackItem_t)itemOdd);
	EXPECT_EQ(stack.sizeActual, 3);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &stack, 1);
	EXPECT_EQ(STACK_RESULT__OK, result);
	EXPECT_EQ(checkedItem, item1);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &stack, 2);
	EXPECT_EQ(STACK_RESULT__OK, result);
	EXPECT_EQ(checkedItem, item2);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &stack, 3);
	EXPECT_EQ(STACK_RESULT__OK, result);
	EXPECT_EQ(checkedItem, item3);

	result = StackOfVoid__GetByIndex((StackItem_t*)&checkedItem, &stack, 4);
	EXPECT_EQ(STACK_RESULT__OUT_OF_SCOPE_ERROR, result);
}