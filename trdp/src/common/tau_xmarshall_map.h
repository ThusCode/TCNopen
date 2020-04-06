/**********************************************************************************************************************/
/**
 * @file            tau_xmarshall_map.h
 *
 * @brief           TRDP utility interface definitions
 *
 * @details         This module provides extra definitions for setup of
 *                   - extended marshalling/unmarshalling
 *
  * @note           Project: TCNOpen TRDP prototype stack
 *
 * @author          Thorsten Schulz
 *
 * @remarks This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 *          If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *          Copyright Bombardier Transportation Inc. or its subsidiaries and others, 2013. All rights reserved.
 *
 * $Id$
 *
 */

#ifndef SRC_COMMON_TAU_XMARSHALL_MAP_H_
#define SRC_COMMON_TAU_XMARSHALL_MAP_H_

#ifndef ALIGNOF
#define ALIGNOF(type)   __alignof__(type)
#endif

/**********************************************************************************************************************/
/**    Provide a uint8 map, see macro below, for xmarshalling. Currently, this has no means to be safely trough runtime.
 */
#define TAU_XTYPE_MAP_SIZE 40

/**********************************************************************************************************************/
/**    Macro to help define the correct sizes and alignments for a specialized type mapping. This obviously has
 *  limitations and should be used sensibly.
 *  Note, that the last three parameters denote the inner types of the time-structures: seconds, ticks and micro-secs.
 *
 *  If you would like xmarshall to behave as std-marshall you would write in your global namespace:
 *
 *  @code TAU_XMARSHALL_MAP(char, bool, char, int16_t, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t,
 *                          uint64_t, float, double, uint32_t, uint16_t, int32_t)
 *
 *  If you had an application that is unaware of fine-grained width-types, e.g., SCADE <=6.4
 *
 *  @code TAU_XMARSHALL_MAP(kcg_char, kcg_bool, kcg_char, kcg_int, kcg_int, kcg_int, kcg_int, kcg_int, kcg_int, kcg_int,
 *                          kcg_int, kcg_int,  kcg_real, kcg_real,  kcg_int, kcg_int, kcg_int);
 *
 *  Some extra considerations on the time-types: On x86_64 Linux, UNIX time is int64_t, on x86 int32_t. struct timeval's
 *  members are both signed. 61375-2-3 is quite unclear on its types. vos_types.h declares all but the tv_usecs as
 *  unsigned types - and I go with that.
 *
 *  You need to pass a reference to @name to session / xmarshall initialization. Currently there is no use-case to have
 *  per-interface maps, so it's the same for all - since the map is rather main-app-specific and there is only one.
 */

#define DEFINE_TAU_XMARSHALL_MAP( constname, bit8, c8, c16, i8, i16, i32, i64, u8, u16, u32, u64, f32, f64, sec, tick, us ) \
	typedef struct { struct { sec s; tick t; } a; } __TAU_XTYPE_TIME48; \
	typedef struct { struct { sec s;   us u; } a; } __TAU_XTYPE_TIME64; \
	static const uint8_t constname[TAU_XTYPE_MAP_SIZE] = { \
		0, sizeof(bit8), sizeof(c8), sizeof(c16), \
		sizeof(i8), sizeof(i16), sizeof(i32), sizeof(i64),  \
		sizeof(u8), sizeof(u16), sizeof(u32), sizeof(u64),  \
		sizeof(f32), sizeof(f64), sizeof(sec), \
		sizeof(__TAU_XTYPE_TIME48), sizeof(__TAU_XTYPE_TIME64), \
		sizeof(tick), sizeof(us), 0, \
		0, ALIGNOF(bit8), ALIGNOF(c8), ALIGNOF(c16), \
		ALIGNOF(i8), ALIGNOF(i16), ALIGNOF(i32), ALIGNOF(i64),  \
		ALIGNOF(u8), ALIGNOF(u16), ALIGNOF(u32), ALIGNOF(u64),  \
		ALIGNOF(f32), ALIGNOF(f64), ALIGNOF(sec), \
		ALIGNOF(__TAU_XTYPE_TIME48), ALIGNOF(__TAU_XTYPE_TIME64), \
		ALIGNOF(tick), ALIGNOF(us), 0, \
	}

#define __TRDP_TIMEDATE48_TICK 17
#define __TRDP_TIMEDATE64_US   18


#endif /* SRC_COMMON_TAU_XMARSHALL_MAP_H_ */