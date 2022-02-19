

#include <stdint.h>
#include <stdbool.h>               
#include "stack_of_void.h"

#ifdef	__cplusplus
extern "C" {
#endif


	static bool IsStackInited(StackOfVoid_t* stack) {

		return (stack != NULL) && (stack->pFirstItem != NULL) && (stack->sizeMax != 0);
	}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__Reset(StackOfVoid_t* stack) {

		if (IsStackInited(stack) == false) {

			return STACK_RESULT__IS_NOT_INITED;
		}

		*(stack->pFirstItem) = NULL;
		stack->sizeActual = 0;

		return STACK_RESULT__OK;
	}

	//-------------------------------------------------------------------------------------
	bool StackOfVoid__IsEmpty(StackOfVoid_t* stack) {

		return *(stack->pFirstItem) == NULL;
	}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__Push(StackOfVoid_t* stack, StackItem_t pushedItem) {

		if (IsStackInited(stack) == false) {

			return STACK_RESULT__IS_NOT_INITED;
		}
		uint32_t i;

		for (i = 0; i < stack->sizeMax; i++) {

			if (*(stack->pFirstItem + i) == NULL) { break; }
		}
		if ((i == stack->sizeMax) && (stack->errorCallback != NULL)) {

			stack->errorCallback(stack->stackID, STACK_RESULT__OVERFULL_ERROR);
			return STACK_RESULT__OVERFULL_ERROR;
		}
		*(stack->pFirstItem + i) = pushedItem;

		if (i < (stack->sizeMax - 1)) {
			*(stack->pFirstItem + i + 1) = NULL;
		}
		stack->sizeActual = i + 1;

		return STACK_RESULT__OK;
	}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__Pop(StackItem_t* pPopedItem, StackOfVoid_t* stack) {

		if (IsStackInited(stack) == false) {

			return STACK_RESULT__IS_NOT_INITED;
		}
		uint32_t i;

		for (i = 0; i < stack->sizeMax; i++) {
			if (*(stack->pFirstItem + i) == NULL) { break; }
		}
		if (i == 0) {
			stack->sizeActual = 0;
			return STACK_RESULT__IS_EMPTY;
		}
		i--;
		*pPopedItem = *(stack->pFirstItem + i);
		*(stack->pFirstItem + i) = NULL;
		stack->sizeActual = i + 1;

		return STACK_RESULT__OK;
	}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__GetByIndex(StackItem_t *pGottenItem, StackOfVoid_t* stack, uint32_t index) {

		if (IsStackInited(stack) == false) {

			return STACK_RESULT__IS_NOT_INITED;
		}
		if (index == 0)
		{
			return STACK_RESULT__OUT_OF_SCOPE_ERROR;
		}
		index--;
		uint32_t i;

		for (i = 0; i < stack->sizeMax; i++) {

			if (*(stack->pFirstItem + i) == NULL) {
				break;
			}
		}
		if ((index >= i) && (stack->errorCallback != NULL)) {

			stack->errorCallback(stack->stackID, STACK_RESULT__OUT_OF_SCOPE_ERROR);

			return STACK_RESULT__OUT_OF_SCOPE_ERROR;
		}

		*pGottenItem = *(stack->pFirstItem + index);

		return STACK_RESULT__OK;
	}

#ifdef	__cplusplus
}
#endif

/*******************************************************************************
 End of File
 */




