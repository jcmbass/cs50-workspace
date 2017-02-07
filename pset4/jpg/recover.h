#include <stdint.h>

/**
 * Common Data Types 
 *
 * The data types in this section are essentially aliases for C/C++ 
 * primitive data types.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;

/**
 * recover.h
 *
 * Computer Science 50
 * Problem Set 4
 *
 */

/**
 * JPEGBODY
 *
 * This structure is a block of 512 bytes 
 * that will read each block of the CF.
 *
 */
typedef struct
{
    BYTE block[512];
}JPEGBODY;