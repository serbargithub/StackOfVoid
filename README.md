# Stack of void module #

	The module ensures a push - pop stack operations for data with void type.
In addition, it provides an random access to stored data. It can be used for various applications like sorting and storing algorithm.
 
The module uses externally allocated memory for stack data, but provide size control and overfilling control.

All functionality is covered by `Google Tests`.

## How to use ##

 Before using it, is necessary allocate memory (static or heap) with  **StackItem_t** type and assign it to Stack container:
 
 
```C
#define STACK_SIZE_MAX  256
StackItem_t stackData[STACK_SIZE_MAX];

StackOfVoid_t stackContainer;

stackContainer.pFirstItem = stackData;
stackContainer.sizeMax = STACK_SIZE_MAX;
stackContainer.errorCallback = CallBackInformer;
stackContainer.stackID = 5;  //there is an example of stack with ID 5

// The module can inform about overfull and out of scope errors by external callback function
// For using the feature, set an call back and set a stack ID to identify callback calling.
// if you not use it, please set callback to NULL

 stackContainer.errorCallback = NULL;
``` 

## Functions of the module ##

> StackResults_t StackOfVoid__Reset (StackOfVoid_t* stack)

Is used every time, when you need erase the stack.
**Return result:** enum with **STACK_RESULT__OK** or an error.

---

> bool StackOfVoid__IsEmpty (StackOfVoid_t* stack)

Is used to check emptiness of the stack. 
**Return value:** _true_ or _false_.

---

> StackResults_t StackOfVoid__Push (StackOfVoid_t* stack, StackItem_t pushedItem)

Push an item to the stack.

**Return result:** enum with **STACK_RESULT__OK** or an error, in addition provides a callback with **STACK_RESULT__OVERFULL_ERROR**.

---

> StackResults_t StackOfVoid__Pop (StackItem_t* pPopedItem, StackOfVoid_t* stack)

Pop an item from the stack.

**Return result:** enum with **STACK_RESULT__OK** or **STACK_RESULT__IS_EMPTY** or an error.

---

> StackResults_t StackOfVoid__GetByIndex (StackItem_t* pGottenItem, StackOfVoid_t* stack, uint32_t index)

provide access to an item from the stack by an index.

**Return result:** enum with **STACK_RESULT__OK** or an error, in addition provides a callback with **STACK_RESULT__OUT_OF_SCOPE_ERROR**.

---