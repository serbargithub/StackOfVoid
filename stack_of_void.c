

#include <stdint.h>
#include <stdbool.h>               
#include "stack_of_void.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define VALIDATE_STACK_IS_INITED    \
			if ((stack == NULL) || (stack->pFirstItem == NULL) || (stack->sizeMax == 0)) {\
				return STACK_RESULT__IS_NOT_INITED;\
			}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__Reset(StackOfVoid_t* stack) {
		VALIDATE_STACK_IS_INITED

		*(stack->pFirstItem) = NULL;
		stack->sizeActual = 0;

		return STACK_RESULT__OK;
	}

	//-------------------------------------------------------------------------------------
	bool StackOfVoid__IsEmpty(StackOfVoid_t* stack) {

		return *(stack->pFirstItem) == NULL;
	}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__Push(StackOfVoid_t* stack, StackItem_t itemToPush) {
		VALIDATE_STACK_IS_INITED

		uint32_t position;
		for (position = 0; position < stack->sizeMax; position++) {
			if (*(stack->pFirstItem + position) == NULL) { 
				break; 
			}
		}
		if ((position == stack->sizeMax) && (stack->errorCallback != NULL)) {
			stack->errorCallback(stack->stackID, STACK_RESULT__OVERFULL_ERROR);

			return STACK_RESULT__OVERFULL_ERROR;
		}
		*(stack->pFirstItem + position) = itemToPush;

		if (position < (stack->sizeMax - 1)) {
			*(stack->pFirstItem + position + 1) = NULL;
		}
		stack->sizeActual = position + 1;

		return STACK_RESULT__OK;
	}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__Pop(StackItem_t* pPopedItem, StackOfVoid_t* stack) {
		VALIDATE_STACK_IS_INITED

		uint32_t position;
		for (position = 0; position < stack->sizeMax; position++) {
			if (*(stack->pFirstItem + position) == NULL) {
				break; 
			}
		}
		stack->sizeActual = position;
		if (position == 0) {

			return STACK_RESULT__IS_EMPTY;
		}
		position--;
		*pPopedItem = *(stack->pFirstItem + position);
		*(stack->pFirstItem + position) = NULL;

		return STACK_RESULT__OK;
	}

	//-------------------------------------------------------------------------------------
	StackResults_t StackOfVoid__GetByIndex(StackItem_t *pGottenItem, StackOfVoid_t* stack, uint32_t index) {
		VALIDATE_STACK_IS_INITED
		// the lowest numer of index is start with 1
		if (index == 0) {
			return STACK_RESULT__OUT_OF_SCOPE_ERROR;
		}
		index--;  
		uint32_t position;

		for (position = 0; position < stack->sizeMax; position++) {
			StackItem_t nextItem = *(stack->pFirstItem + position);
			if (nextItem == NULL) {
				break;
			}
		}
		if ((index >= position) && (stack->errorCallback != NULL)) {
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




