#ifndef COMMON_H
#define COMMON_H

typedef unsigned char byte;
typedef char sbyte;

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long  uint64;
typedef char           int8;
typedef short          int16;
typedef int            int32;
typedef long           int64;

#define BIT(x) (1 << (x))

#ifndef __cplusplus
typedef uint8 bool;
#define true  1
#define false 0
#endif

#define ON_RANGE(x, rangemin, rangemax) x >= rangemax && x <= rangemin

#endif // COMMON_H