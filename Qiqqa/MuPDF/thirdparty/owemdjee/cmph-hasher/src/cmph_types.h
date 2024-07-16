#ifndef __CMPH_TYPES_H__
#define __CMPH_TYPES_H__

#include <stdint.h>

typedef char cmph_int8;
typedef unsigned char cmph_uint8;

typedef short cmph_int16;
typedef unsigned short cmph_uint16;

typedef int cmph_int32;
typedef unsigned int cmph_uint32;

  /** \typedef int64_t cmph_int64;
   *  \brief 64-bit integer for a 64-bit architecture.
   */
  typedef int64_t cmph_int64;

  /** \typedef uint64_t cmph_uint64;
   *  \brief Unsigned 64-bit integer for a 64-bit architecture.
   */
  typedef uint64_t cmph_uint64;

typedef enum { CMPH_HASH_JENKINS, CMPH_HASH_DJB2, CMPH_HASH_SDBM,
               CMPH_HASH_FNV, CMPH_HASH_COUNT } CMPH_HASH;
extern const char *cmph_hash_names[];
typedef enum { CMPH_BMZ, CMPH_BMZ8, CMPH_CHM, CMPH_BRZ, CMPH_FCH,
               CMPH_BDZ, CMPH_BDZ_PH,
               CMPH_CHD_PH, CMPH_CHD, CMPH_COUNT } CMPH_ALGO;
extern const char *cmph_names[];

#endif
