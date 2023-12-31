/*!\file
*/

#ifndef STACK_FUNC_H_INCLUDED
#define STACK_FUNC_H_INCLUDED

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdarg.h>


    #include "stack_struct.h"
    #include "stack_errors_enum_naming.h"
    #include "errors_enum_naming.h"

    
    static const size_t N_ELEMS_PRINT = 100; ///< Amount of elements will be printed in stack_dump
    
    

    /**
     * Creates(allocates memory) data(massif with numbers which we push and pop from stack).
     *
     * @param [in] *error  Pointer to error. At the end of the program 0 if all is normal, NOT_MEMORY if we have not enough memory, 
     * BAD_POINTER if stk == NULL.
     *
     * @returns Pointer to stack
     */
    Stack* stack_ctor(errors* error);

    /**
     * Puts poison in the data, free data's memory. Puts poison in the pointer to data, in the current_size of data, in the capacity.
     * DO NOT free stk
     * 
     * @param [in] stk Pointer to stack
     *
     * @returns NULL if stack pointer already consists of NULL else it returns BAD_PTR.
     */
    Stack* stack_dtor(Stack* stk);

    /**
     * Puts a new value in the massif data, if it needs then allocates new memory. Adds 1 to the current_size in stack, changes 
     * capacity if we have allocated new memory.
     *
     * @param [in] stk Pointer to stack
     * @param [in] value Value we need to push in stack
     *
     * @returns ALL_OK if all is normal, NOT_MEMORY if we have not enough memory, BAD_STACK_POINTER if stk consists of NULL or 
     * BAD_PTR(which is written in constants), BAD_DATA_POINTER if stk->data consists of NULL or BAD_PTR.
     */
    int stack_push(Stack* stk, elem_type value);

    /**
     * Deletes last value in the massif data if it it needs then allocates new memory. Subs 1 from the current_size in stack, 
     * changes capacity if we have allocated new memory.
     *
     * @param [in] stk Pointer to stack
     * @param [in] error Pointer to error. At the end it consists of the ALL_OK if all is normal, NOT_MEMORY if something
     * went wrong while realloc memory, POP_EMPTY_STK if stk is empty..
     *
     * @returns Elem which has been poped 
     */
    elem_type stack_pop(Stack* stk, int* error);

    /**
     * Returns element which is on the top of the stack.
     *
     * @param [in] stk Pointer to stack
     * @param [in] error Pointer to error. At the end it consists of the ALL_OK if all is normal, NOT_MEMORY if something
     * went wrong while realloc memory, EMPTY_STK if stk is empty.
     *
     * @returns Elem which is on the top of the stk 
     */
    elem_type stack_top(Stack* stk, int* error);


    // /**
    //  * Checks all in stack.
    //  *
    //  * @param [in] stk Pointer to stack
    //  *
    //  * @returns ALL_OK if all is normal, code of the error if something is wrong.
    //  */
    // stack_errors stack_ok(Stack* stk);   //enum stack_errors stack_ok

    /**
     * Checks all in stack.
     *
     * @param [in] stk Pointer to stack
     *
     * @returns ALL_OK(0) if all is normal, mask of stack_errors if something is wrong.
     */
    size_t stack_ok(Stack* stk);   //enum stack_errors stack_ok


     /**
     * Prints all infornation about the stack in file_with_stack_errors.
     *
     * @param [in] stk Pointer to stack
     *
     * @returns ALL_OK if all is normal, BAD_STACK_POINTER if stk consists of NULL or BAD_PTR(which is written in constants), 
     * BAD_FILE_POINTER if stk->file_with_stack_errors consists of NULL.
     * 
     * Prints only N_ELEMS_PRINT (const) in stack
     */
    int stack_dump(Stack* stk, stack_errors reason);


    /**
     * @param [in] stk Pointer to stack
     * @param [in] num Index of element we need in Stack data (numeration from 0)
     * 
     * @returns pointer to element with number num in Stack data (numeration from 0) or NULL if stk or stk-data consists of NULL or 
     * BAD_PTR(elem_type *const, defined in "stack_struct.h"), returns NULL also if num < 0
     */
    elem_type* get_data_elem_pointer(Stack* stk, size_t num);


    /**
     * Allocates new memory, copy previous data to new one, memset 0...0 after previous data in new data, change stk->capacity
     * 
     * @param [in] stk Pointer to stack
     * @param [in] new_capacity  New capacity we want for data
     * 
     * @returns pointer to new memory or NULL if realloc can not allocate new memory
     */
    elem_type* change_capacity(Stack* stk, size_t new_capacity);

    /**
     * Counts massif data hash.
     *
     * @param [in] stk Pointer to stack
     *
     * @returns counted hash value. Returns 0 and reason = BAD_POINER if !stk or !stk->data
     */
    long long stack_hash(Stack* stk, errors* reason);

    /**
     * Parses error and prints in file which can be in va-args or in stderror
     */
    void print_parse_stack_error(stack_errors error, ...); //in va_args file_ptr

   
#endif