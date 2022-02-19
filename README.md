# Stack of void module #

	The module is ensured a push - pop stack operations for data with void type.
In addition it provides an random acces to stored data. It can be used for various 
appliences like sorting and storing algorithm. 
	The module uses externaly allocated memory for stack data, 
but provide size control and overfilling contol.

## How to use ##
 Before using it neccesary allocate memory with  **StackItem_t** type 
 and assign it to Stack container:
 
 
```C
#define STACK_SIZE_MAX  256
```C
StackItem_t stackData[STACK_SIZE_MAX];
```C
StackOfVoid_t stackContainer;
```C
stackContainer.pFirstItem = stackData;
stackContainer.sizeMax = STACK_SIZE_MAX;
stackContainer.errorCallback = CallBackInformer;
stackContainer.stackID = 5;  //there is an example of stack with ID 5
```C
// The module can inform about overfull and out of scope errors by external callback function
// For using the futures set an call back and set a stack ID to identify callback calling.
// if you fo not use it please set callback to NULL
```C
 stackContainer.errorCallback = NULL;
 
``` 
## Functions of the module ##

```C StackResults_t StackOfVoid__Reset(StackOfVoid_t* stack) ```

Is used every time when you need erase created stack.
**Return result:** enum with `STACK_RESULT__OK` or an error.


```C bool StackOfVoid__IsEmpty(StackOfVoid_t* stack) ```

Is used to check emptyness of the stack. 
**Return value:** _true_ or _false_.


```C StackResults_t StackOfVoid__Push(StackOfVoid_t* stack, StackItem_t pushedItem) ```

Pushed an item to the stack.

**Return result:** enum with **STACK_RESULT__OK** or an error, in addition provide call back with **STACK_RESULT__OVERFULL_ERROR**.


```C StackResults_t StackOfVoid__Pop(StackItem_t* pPopedItem, StackOfVoid_t* stack) ```

Pop an item from the stack.

**Return result:** enum with **STACK_RESULT__OK** or **STACK_RESULT__IS_EMPTY** or an error.


```C StackResults_t StackOfVoid__GetByIndex(StackItem_t* pGottenItem, StackOfVoid_t* stack, uint32_t index) ```

provide access to an item from the stack by a sored index.

**Return result:** enum with **STACK_RESULT__OK** or **STACK_RESULT__OUT_OF_SCOPE_ERROR** in addition provide call back with **STACK_RESULT__OUT_OF_SCOPE_ERROR**.