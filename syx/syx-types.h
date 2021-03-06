/* 
   Copyright (c) 2007 Luca Bruno

   This file is part of Smalltalk YX.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell   
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,  
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER    
   DEALINGS IN THE SOFTWARE.
*/

#ifndef SYX_TYPES_H
#define SYX_TYPES_H

#include "syx-config.h"
#include "syx-enums.h"
#include "syx-platform.h"

#include <limits.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <wchar.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SYX_BEGIN_DECLS

/*! \page syx_types Syx Types
  Contains various C data types definition, including SyxOop
*/

#define SYX_IS_POINTER(oop) ((oop) && ((oop) & 3) == SYX_TYPE_POINTER)
#define SYX_IS_SMALL_INTEGER(oop) (((oop) & 1) == SYX_TYPE_SMALL_INTEGER)
#define SYX_IS_CHARACTER(oop) (((oop) & 3) == SYX_TYPE_CHARACTER)

#define SYX_OOP_EQ(oop1, oop2) ((oop1) == (oop2))
#define SYX_OOP_NE(oop1, oop2) ((oop1) != (oop2))

/*! Cast a SyxOop to a native pointer type */
#define SYX_OOP_CAST_POINTER(oop) ((syx_pointer) (oop))
/*! Cast a pointer to a SyxOop */
#define SYX_POINTER_CAST_OOP(ptr) ((SyxOop) (ptr))

/*! TRUE if the number can be embedded */
#define SYX_SMALL_INTEGER_CAN_EMBED(num) ((num) >= (-1 << 30) && (num) < (1 << 30))
/*! TRUE if an overflow occurs when doing the sum of a and b */
#define SYX_SMALL_INTEGER_SUM_OVERFLOW(a,b) (((a ^ b) | (((a ^ (~(a ^ b) & (1 << (sizeof(syx_int32) * CHAR_BIT - 1)))) + b) ^ b)) >= 0)
/*! TRUE if an overflow occurs when doing the difference between a and b */
#define SYX_SMALL_INTEGER_DIFF_OVERFLOW(a,b) (((a ^ b) & (((a ^ ((a ^ b) & (1 << (sizeof(syx_int32) * CHAR_BIT - 1)))) - b) ^ b)) < 0)
/*! TRUE if an overflow occurs when doing division between a and b */
#define SYX_SMALL_INTEGER_DIV_OVERFLOW(a,b) ((b == 0) || ((a == INT_MIN) && (b == -1)))
/*! Force the embedding of an integer */
#define SYX_SMALL_INTEGER_EMBED(num) ((syx_int32)(num) & ~(3 << 30))

#if !defined FALSE || !defined TRUE
#define FALSE 0
#define TRUE 1
#endif

typedef unsigned char syx_bool;

typedef char syx_char;
typedef unsigned char syx_uchar;

typedef wchar_t syx_wchar;


typedef syx_char * syx_string;
typedef const syx_char * syx_symbol;
typedef syx_wchar * syx_wstring;
typedef const syx_wchar * syx_wsymbol;

#ifdef HAVE_STDINT_H
  typedef int8_t syx_int8;
  typedef uint8_t syx_uint8;
  
  typedef int16_t syx_int16;
  typedef uint16_t syx_uint16;
  
  typedef int32_t syx_int32;
  typedef uint32_t syx_uint32;
  
  #ifdef HAVE_INT64_T
    typedef int64_t syx_int64;
    typedef uint64_t syx_uint64;
  #endif
#else
  #ifdef _MSC_VER
    typedef signed char syx_int8;
    typedef unsigned char syx_uint8;
    
    typedef short syx_int16;
    typedef unsigned short syx_uint16;
    /* Note: this might not be true for 64-bit compilers */
    typedef int syx_int32;
    typedef unsigned int syx_uint32;

    typedef _int64 syx_int64;
    typedef unsigned _int64 syx_uint64;
  #else
   #error "don't know how to define types for this compiler"
  #endif
#endif

typedef long syx_nint;
typedef unsigned long syx_unint;

typedef long syx_size;
typedef syx_int32 syx_varsize;

typedef float syx_float;
typedef double syx_double;

typedef void * syx_pointer;

typedef syx_nint SyxOop;

/* Basic instance types */

/*! Expands to syx_true or syx_false depending on the given condition */
#define syx_boolean_new(cond) ((cond) ? syx_true : syx_false)
/*! Create a new SmallInteger */
#define syx_small_integer_new(num) (((SyxOop)(num) << 1) + SYX_TYPE_SMALL_INTEGER)
/*! Create a new Character */
#define syx_character_new(ch) (((SyxOop)(ch) << 2) + SYX_TYPE_CHARACTER)

/*! Retrieve a syx_int32 from a SyxOop */
#define SYX_SMALL_INTEGER(oop) ((syx_int32)(oop) >> 1)
/*! Retrieve a syx_uchar from a SyxOop */
#define SYX_CHARACTER(oop) ((syx_uchar)((oop) >> 2))


/*! TRUE if an overflow occurs when doing b times a */
extern EXPORT syx_bool SYX_SMALL_INTEGER_MUL_OVERFLOW (syx_int32 a, syx_int32 b);
/*! TRUE if an overflow occurs when shifting a on the left by b */
extern EXPORT syx_bool SYX_SMALL_INTEGER_SHIFT_OVERFLOW (syx_int32 a, syx_int32 b);



#define syx_free free


INLINE syx_pointer
syx_malloc (syx_int32 size)
{
  syx_pointer ptr;

  if (!size)
    return NULL;

  ptr = malloc (size);
  if (!ptr)
    {
      puts ("out of memory\n");
      exit (-1);
    }

  return ptr;
}

INLINE syx_pointer
syx_malloc0 (syx_int32 size)
{
  syx_pointer ptr;

  if (!size)
    return NULL;

  ptr = malloc (size);
  if (!ptr)
    {
      puts ("out of memory\n");
      exit (-1);
    }

  memset (ptr, '\0', size);
  return ptr;
}

INLINE syx_pointer
syx_calloc (syx_int32 elements, syx_int32 element_size)
{
  syx_pointer ptr;

  if (!elements || !element_size)
    return NULL;

  ptr = calloc (elements, element_size);
  if (!ptr)
    {
      puts ("out of memory\n");
      exit (-1);
    }

  return ptr;
}

INLINE syx_pointer
syx_realloc (syx_pointer ptr, syx_int32 size)
{
  syx_pointer nptr;

  nptr = realloc (ptr, size);
  if (!nptr)
    {
      puts ("out of memory\n");
      exit (-1);
    }

  return nptr;
}

/*! Return a new allocated memory which is a copy of the given one */
INLINE syx_pointer
syx_memdup (syx_pointer ptr, syx_int32 elements, syx_int32 element_size)
{
  syx_pointer nptr;

  nptr = syx_malloc (element_size * elements);
  memcpy (nptr, ptr, element_size * elements);

  return nptr;
}


INLINE syx_string
syx_strndup (syx_symbol src, syx_size n)
{
  syx_string ret = (syx_string) syx_malloc (n + 1);
  memcpy (ret, src, n);
  ret[n] = '\0';
  return ret;
}

INLINE syx_string
syx_strdup (syx_symbol src)
{
  return syx_strndup (src, strlen (src));
}

SYX_END_DECLS

#endif /* SYX_TYPES_H */
