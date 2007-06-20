#ifndef SYX_ENUMS_H
#define SYX_ENUMS_H

//! The type of SyxOop contained in SyxOop::c::type
typedef enum
  {
    //! This means SyxOop indexes an object into the syx memory
    SYX_TYPE_POINTER,
    SYX_TYPE_SMALL_INTEGER,
    SYX_TYPE_CHARACTER,
    SYX_TYPE_SMALL_FLOAT,
  } SyxType;

//! Indexes of known instance variables
/*!
  Each known class has default instance variables used by the VM that are mandatory.
  These indexes are used to facilitate the access these variables and are contained in SyxObject::data
*/
typedef enum
  {
    SYX_DATA_OBJECT_ALL,

    SYX_DATA_CLASS_NAME = SYX_DATA_OBJECT_ALL,
    SYX_DATA_CLASS_SUPERCLASS,
    SYX_DATA_CLASS_INSTANCE_VARIABLES,
    SYX_DATA_CLASS_INSTANCE_SIZE,
    SYX_DATA_CLASS_METHODS,
    SYX_DATA_CLASS_ALL,

    SYX_DATA_METACLASS_INSTANCE_CLASS = SYX_DATA_CLASS_ALL,
    SYX_DATA_METACLASS_ALL,

    SYX_DATA_SYMBOL_ALL = SYX_DATA_OBJECT_ALL,

    SYX_DATA_STRING_ALL = SYX_DATA_OBJECT_ALL,
    
    SYX_DATA_LINK_KEY = SYX_DATA_OBJECT_ALL,
    SYX_DATA_LINK_VALUE,
    SYX_DATA_LINK_NEXT_LINK,
    SYX_DATA_LINK_ALL,

    SYX_DATA_DICTIONARY_HASH_TABLE = SYX_DATA_OBJECT_ALL,
    SYX_DATA_DICTIONARY_ALL,

    SYX_DATA_METHOD_SELECTOR = SYX_DATA_OBJECT_ALL,
    SYX_DATA_METHOD_BYTECODES,
    SYX_DATA_METHOD_LITERALS,
    SYX_DATA_METHOD_ARGUMENTS_COUNT,
    SYX_DATA_METHOD_TEMPORARIES_COUNT,
    SYX_DATA_METHOD_STACK_SIZE,
    SYX_DATA_METHOD_PRIMITIVE,
    SYX_DATA_METHOD_ALL,

    SYX_DATA_BLOCK_ARGUMENTS_TOP=SYX_DATA_METHOD_ALL,
    SYX_DATA_BLOCK_ALL,

    SYX_DATA_BLOCK_CLOSURE_BLOCK = SYX_DATA_OBJECT_ALL,
    SYX_DATA_BLOCK_CLOSURE_DEFINED_CONTEXT,
    SYX_DATA_BLOCK_CLOSURE_ALL,

    SYX_DATA_PROCESS_CONTEXT = SYX_DATA_OBJECT_ALL,
    SYX_DATA_PROCESS_SUSPENDED,
    SYX_DATA_PROCESS_RETURNED_OBJECT,
    SYX_DATA_PROCESS_NEXT,
    SYX_DATA_PROCESS_SCHEDULED,
    SYX_DATA_PROCESS_ALL,

    SYX_DATA_SEMAPHORE_SIGNALS = SYX_DATA_OBJECT_ALL,
    SYX_DATA_SEMAPHORE_ALL,

    SYX_DATA_METHOD_CONTEXT_PARENT = SYX_DATA_OBJECT_ALL,
    SYX_DATA_METHOD_CONTEXT_METHOD,
    SYX_DATA_METHOD_CONTEXT_STACK,
    SYX_DATA_METHOD_CONTEXT_SP,
    SYX_DATA_METHOD_CONTEXT_IP,
    SYX_DATA_METHOD_CONTEXT_RECEIVER,
    SYX_DATA_METHOD_CONTEXT_ARGUMENTS,
    SYX_DATA_METHOD_CONTEXT_TEMPORARIES,
    SYX_DATA_METHOD_CONTEXT_RETURN_CONTEXT,
    SYX_DATA_METHOD_CONTEXT_ALL,

    SYX_DATA_BLOCK_CONTEXT_OUTER_CONTEXT = SYX_DATA_METHOD_CONTEXT_ALL,
    SYX_DATA_BLOCK_CONTEXT_HANDLED_EXCEPTION,
    SYX_DATA_BLOCK_CONTEXT_HANDLER_BLOCK,
    SYX_DATA_BLOCK_CONTEXT_ALL,

    SYX_DATA_PROCESSOR_SCHEDULER_BYTESLICE = SYX_DATA_OBJECT_ALL,
    SYX_DATA_PROCESSOR_SCHEDULER_FIRST_PROCESS,
    SYX_DATA_PROCESSOR_SCHEDULER_ACTIVE_PROCESS,
    SYX_DATA_PROCESSOR_SCHEDULER_ALL,

  } SyxVariables;

//! The type of the token in SyxToken::type
typedef enum
  {
    SYX_TOKEN_END,
    SYX_TOKEN_INT_CONST,
    SYX_TOKEN_CHAR_CONST,
    SYX_TOKEN_FLOAT_CONST,
    SYX_TOKEN_DOUBLE_CONST,
    SYX_TOKEN_CLOSING,
    SYX_TOKEN_ARRAY_BEGIN,

    SYX_TOKEN_STRING_ENTRY,
    SYX_TOKEN_NAME_CONST,
    SYX_TOKEN_NAME_COLON,
    SYX_TOKEN_SYM_CONST,
    SYX_TOKEN_STR_CONST,
    SYX_TOKEN_BINARY,
  } SyxTokenType;

//! List of commands of a bytecode in SyxBytecode::code
typedef enum
  {
    SYX_BYTECODE_PUSH_INSTANCE,
    SYX_BYTECODE_PUSH_ARGUMENT,
    SYX_BYTECODE_PUSH_TEMPORARY,
    SYX_BYTECODE_PUSH_LITERAL,
    SYX_BYTECODE_PUSH_CONSTANT,
    SYX_BYTECODE_PUSH_GLOBAL,
    SYX_BYTECODE_PUSH_ARRAY,
    
    SYX_BYTECODE_ASSIGN_INSTANCE,
    SYX_BYTECODE_ASSIGN_TEMPORARY,
    
    SYX_BYTECODE_MARK_ARGUMENTS,
    SYX_BYTECODE_SEND_MESSAGE,
    SYX_BYTECODE_SEND_SUPER,
    SYX_BYTECODE_SEND_UNARY,
    SYX_BYTECODE_SEND_BINARY,

    SYX_BYTECODE_DO_SPECIAL,
  
    SYX_BYTECODE_EXTENDED = 0x1F
  } SyxBytecodeCommand;

//! Special commands performed by the command SYX_BYTECODE_DO_SPECIAL
typedef enum
  {
    SYX_BYTECODE_POP_TOP,
    SYX_BYTECODE_SELF_RETURN,
    SYX_BYTECODE_STACK_RETURN,
    SYX_BYTECODE_DUPLICATE,
    SYX_BYTECODE_BRANCH,
    SYX_BYTECODE_BRANCH_IF_TRUE,
    SYX_BYTECODE_BRANCH_IF_FALSE,
    SYX_BYTECODE_SET_DEFINED_CONTEXT,
  } SyxBytecodeSpecial;

//! Constants pushed by SYX_BYTECODE_PUSH_CONSTANT
typedef enum
  {
    SYX_BYTECODE_CONST_NIL,
    SYX_BYTECODE_CONST_TRUE,
    SYX_BYTECODE_CONST_FALSE,

    //! This constant is resolved at runtime by the interpreter
    SYX_BYTECODE_CONST_CONTEXT,
  } SyxBytecodeConstant;


//! Type of signals emitted in the Smalltalk environment
/*!
  Each type is relative to a class defined in syx-error.c
*/
typedef enum
  {
    SYX_ERROR_INTERP,
    SYX_ERROR_NOT_UNDERSTOOD,
    SYX_ERROR_NOT_FOUND,
  } SyxSignalInternal;

#endif /* SYX_ENUMS_H */
