
#ifndef STACK_OF_VOID_H
#define	STACK_OF_VOID_H

#ifdef	__cplusplus
extern "C" {
#endif

	typedef enum {
		STACK_RESULT_OK = 1,
		STACK_EMPTY = 0,
		STACK_IS_NOT_INITED = -1,
		STACK_IS_FULL_ERROR = -2,
		STACK_OUT_OF_SCOPE_ERROR = -3
	}StackResults_t;

	typedef void* StackItem_t;
	typedef void (*STACK_ERROR_CALLBACK)(uint32_t stackID, StackResults_t result);

	typedef struct {
		StackItem_t* pFirstItem;
		uint32_t sizeMax;
		uint32_t sizeActual;
		uint32_t stackID;
		STACK_ERROR_CALLBACK errorCallback;
	}StackOfVoid_t;

	StackResults_t StackOfVoid__Reset(StackOfVoid_t* stack);
	bool StackOfVoid__IsEmpty(StackOfVoid_t* stack);
	StackResults_t StackOfVoid__Push(StackOfVoid_t* stack, StackItem_t pushedItem);
	StackResults_t StackOfVoid__Pop(StackItem_t* pPopedItem, StackOfVoid_t* stack);
	StackResults_t StackOfVoid__GetByIndex(StackItem_t* pGottenItem, StackOfVoid_t* stack, uint32_t index);


#ifdef	__cplusplus
}
#endif

#endif	/* STACK_OF_VOID_H */

