/* This file is a part of NXVM project. */

/* Type Definitions */

#ifndef NXVM_VGLOBAL_H
#define NXVM_VGLOBAL_H

#ifdef __cplusplus
/*extern "C" {*/
#endif

#include "stdint.h"

#define VGLOBAL_VAR_WIN32 0
#define VGLOBAL_VAR_LINUX 1

#define TEST_VCPU 0
#define TEST_ECPU 1
#define TEST_BOTH 2

/* COMPLIATION DEFINITIONS ***************************************************/
#define VGLOBAL_SIZE_INTEGER 32
#define VGLOBAL_PLATFORM     VGLOBAL_VAR_WIN32
#if ((VGLOBAL_SIZE_INTEGER == 32) && (VGLOBAL_PLATFORM == VGLOBAL_VAR_WIN32))
#define VGLOBAL_ECPU_MODE  TEST_VCPU
#else
#define VGLOBAL_ECPU_MODE  TEST_VCPU
#endif
/*****************************************************************************/

typedef char     *t_string;
typedef uint8_t   t_nubit1;
typedef uint8_t   t_nubit4;
typedef uint8_t   t_nubit6;
typedef uint8_t   t_nubit8;
typedef int8_t    t_nsbit8;
typedef uint16_t  t_nubit16;
typedef int16_t   t_nsbit16;
typedef uint32_t  t_nubit24;
typedef int32_t   t_nsbit24;
typedef uint32_t  t_nubit32;
typedef int32_t   t_nsbit32;
typedef uint64_t  t_nubit48;
typedef int64_t   t_nsbit48;
typedef uint64_t  t_nubit64;
typedef int64_t   t_nsbit64;
typedef float     t_float32;
typedef double    t_float64;
#if VGLOBAL_SIZE_INTEGER == 64
typedef t_nubit64 t_nubitcc;
typedef t_nsbit64 t_nsbitcc;
#else
typedef t_nubit32 t_nubitcc;
typedef t_nsbit32 t_nsbitcc;
#endif
typedef t_nubit1  t_bool;
typedef t_nubitcc t_vaddrcc;
typedef t_nubitcc t_faddrcc;

#define p_nubit1  (t_nubit1 *)
#define p_nubit4  (t_nubit4 *)
#define p_nubit6  (t_nubit6 *)
#define p_nubit8  (t_nubit8 *)
#define p_nsbit8  (t_nsbit8 *)
#define p_nubit16 (t_nubit16 *)
#define p_nsbit16 (t_nsbit16 *)
#define p_nubit24 (t_nubit24 *)
#define p_nsbit24 (t_nsbit24 *)
#define p_nubit32 (t_nubit32 *)
#define p_nsbit32 (t_nsbit32 *)
#define p_nubit64 (t_nubit64 *)
#define p_nsbit64 (t_nsbit64 *)
#define p_float32 (t_float32 *)
#define p_float64 (t_float64 *)
#define p_nubitcc (t_nubitcc *)
#define p_nsbitcc (t_nsbitcc *)
#define p_bool    (t_bool *)

#define d_nubit1(n)  (*(t_nubit1 *)(n))
#define d_nubit4(n)  (*(t_nubit4 *)(n))
#define d_nubit6(n)  (*(t_nubit6 *)(n))
#define d_nubit8(n)  (*(t_nubit8 *)(n))
#define d_nsbit8(n)  (*(t_nsbit8 *)(n))
#define d_nubit16(n) (*(t_nubit16 *)(n))
#define d_nsbit16(n) (*(t_nsbit16 *)(n))
#define d_nubit24(n) (*(t_nubit24 *)(n))
#define d_nsbit24(n) (*(t_nsbit24 *)(n))
#define d_nubit32(n) (*(t_nubit32 *)(n))
#define d_nsbit32(n) (*(t_nsbit32 *)(n))
#define d_nubit64(n) (*(t_nubit64 *)(n))
#define d_nsbit64(n) (*(t_nsbit64 *)(n))
#define d_float32(n) (*(t_float32 *)(n))
#define d_float64(n) (*(t_float64 *)(n))
#define d_nubitcc(n) (*(t_nubitcc *)(n))
#define d_nsbitcc(n) (*(t_nsbitcc *)(n))
#define d_bool(n)    (*(t_bool *)(n))

#define GetBit(s, f) (!!((s) & (f)))
#define SetBit(d, s) ((d) |= (s))
#define ClrBit(d, s) ((d) &= ~(s))
#define MakeBit(d, s, f)  ((f) ? SetBit((d), (s)) : ClrBit((d), (s)))
#define GetMSB(n, b) (GetBit((n), (1 << ((b) - 1))))
#define GetLSB(n, b) (GetBit((n), 1))
#define Max8  0xff
#define Max16 0xffff
#define Max24 0x00ffffff
#define Max32 0xffffffff
#define Max48 0x0000ffffffffffff
#define Max64 0xffffffffffffffff
#define MSB7  0x40
#define MSB8  0x80
#define MSB15 0x4000
#define MSB16 0x8000
#define MSB31 0x40000000
#define MSB32 0x80000000
#define MSB47 0x0000400000000000
#define MSB48 0x0000800000000000
#define MSB63 0x4000000000000000
#define MSB64 0x8000000000000000
#define GetMax8(n)  ((t_nubit8 )(n) & Max8 )
#define GetMax16(n) ((t_nubit16)(n) & Max16)
#define GetMax24(n) ((t_nubit24)(n) & Max24)
#define GetMax32(n) ((t_nubit32)(n) & Max32)
#define GetMax48(n) ((t_nubit48)(n) & Max48)
#define GetMax64(n) ((t_nubit64)(n) & Max64)
#define GetMSB7(n)  ((t_nubit8 )(n) & MSB7 )
#define GetMSB8(n)  ((t_nubit8 )(n) & MSB8 )
#define GetMSB15(n) ((t_nubit16)(n) & MSB15)
#define GetMSB16(n) ((t_nubit16)(n) & MSB16)
#define GetMSB31(n) ((t_nubit32)(n) & MSB31)
#define GetMSB32(n) ((t_nubit32)(n) & MSB32)
#define GetMSB47(n) ((t_nubit48)(n) & MSB47)
#define GetMSB48(n) ((t_nubit48)(n) & MSB48)
#define GetMSB63(n) ((t_nubit64)(n) & MSB63)
#define GetMSB64(n) ((t_nubit64)(n) & MSB64)
#define GetLSB8(n)  ((t_nubit8 )(n) & 1)
#define GetLSB16(n) ((t_nubit16)(n) & 1)
#define GetLSB32(n) ((t_nubit32)(n) & 1)
#define GetLSB48(n) ((t_nubit48)(n) & 1)
#define GetLSB64(n) ((t_nubit64)(n) & 1)

#define Hex2BCD(x)  ((((x) / 10) << 4) | ((x) % 10))
#define BCD2Hex(x)  (((x) & 0x0f) + ((((x) & 0xf0) >> 4) * 10))

#define ExecFun(faddr) (*(void (*)(void))(faddr))()

#ifdef __cplusplus
/*}_EOCD_*/
#endif

#endif
