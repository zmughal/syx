#ifndef SYX_INTERP_H
#define SYX_INTERP_H

#include "syx-types.h"
#include "syx-object.h"

/* Execution state of a Process */

typedef struct SyxExecState SyxExecState;

struct SyxExecState
{
  SyxOop process;
  SyxOop context;
  SyxOop receiver;
  SyxOop *arguments;
  SyxOop *temporaries;
  SyxOop *stack;
  SyxOop *literals;
  syx_uint16 *bytecodes;
  syx_int32 bytecodes_count;
  syx_int32 byteslice;
  syx_int32 ip, sp;

  //! Holds the receiver of a new message
  SyxOop message_receiver;
  //! Holds the arguments of a new message
  SyxOop *message_arguments;
  syx_varsize message_arguments_count;
};

//! Creates a new empty execution state
inline SyxExecState *syx_exec_state_new (void);
void syx_exec_state_fetch (void);
inline void syx_exec_state_save (void);
inline void syx_exec_state_free (void);

/* Primitives */

#define SYX_PRIM_RETURN(object)						\
  syx_interp_stack_push (object);					\
  return TRUE

#define SYX_PRIM_FAIL							\
  syx_interp_enter_context (syx_method_context_new (es->context, method, es->message_receiver, \
						    syx_array_new (es->message_arguments_count, es->message_arguments))); \
  return FALSE

//! The number of primitives
#define SYX_PRIMITIVES_MAX 53

typedef syx_bool (* SyxPrimitiveFunc) (SyxExecState *es, SyxOop method);
#define SYX_FUNC_PRIMITIVE(name)					\
  syx_bool								\
  name (SyxExecState *es, SyxOop method)

typedef struct SyxPrimitiveEntry SyxPrimitiveEntry;

struct SyxPrimitiveEntry {
  syx_symbol name;
  SyxPrimitiveFunc func;
};

//! Returns the entry of a primitive at a given index
inline SyxPrimitiveEntry *syx_primitive_get_entry (syx_int32 index);

//! Returns the index of a primitive having a specific name
syx_int32 syx_primitive_get_index (syx_symbol name);

/* Interpreter */

typedef syx_bool (* SyxInterpreterFunc) (syx_uint16 argument);
#define SYX_FUNC_INTERPRETER(name)		\
  syx_bool					\
  name (syx_uint16 argument)

inline void syx_interp_init (void);
inline void syx_interp_quit (void);

inline syx_bool syx_interp_swap_context (SyxOop context);
inline syx_bool syx_interp_enter_context (SyxOop context);
inline syx_bool syx_interp_leave_context_and_answer (SyxOop return_object, syx_bool use_return_context);

inline void syx_interp_stack_push (SyxOop object);
inline SyxOop syx_interp_stack_pop (void);
inline SyxOop syx_interp_stack_peek (void);
inline syx_bool syx_interp_call_primitive (syx_int16 primitive, SyxOop method);

inline SyxOop syx_interp_get_current_context (void);

/* Process execution */

void syx_process_execute_scheduled (SyxOop process);
void syx_process_execute_blocking (SyxOop process);

/* Interpreter functions */

SYX_FUNC_INTERPRETER (syx_interp_push_instance);
SYX_FUNC_INTERPRETER (syx_interp_push_argument);
SYX_FUNC_INTERPRETER (syx_interp_push_temporary);
SYX_FUNC_INTERPRETER (syx_interp_push_literal);
SYX_FUNC_INTERPRETER (syx_interp_push_constant);
SYX_FUNC_INTERPRETER (syx_interp_push_global);
SYX_FUNC_INTERPRETER (syx_interp_push_array);

SYX_FUNC_INTERPRETER (syx_interp_assign_instance);
SYX_FUNC_INTERPRETER (syx_interp_assign_temporary);

SYX_FUNC_INTERPRETER (syx_interp_mark_arguments);
SYX_FUNC_INTERPRETER (syx_interp_send_message);
SYX_FUNC_INTERPRETER (syx_interp_send_super);
SYX_FUNC_INTERPRETER (syx_interp_send_unary);
SYX_FUNC_INTERPRETER (syx_interp_send_binary);

SYX_FUNC_INTERPRETER (syx_interp_do_special);

#endif /* SYX_INTERP_H */