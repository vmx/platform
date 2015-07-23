/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 *     Copyright 2015 Couchbase, Inc
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#pragma once

/* Macros for handling symbol visibility */


/* EXPORT_SYMBOL
 *
 * Use for symbols which should be exported (externally visible) from a
 * library.
 */
#if (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)) || (defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x550))
#define EXPORT_SYMBOL __global
#elif defined __GNUC__
#define EXPORT_SYMBOL __attribute__ ((visibility("default")))
#elif defined(_MSC_VER)
#define EXPORT_SYMBOL __declspec(dllexport)
#else
#define EXPORT_SYMBOL
#endif

/* IMPORT_SYMBOL
 *
 * Use for symbols which should be imported from a shared library; for example
 * used in the published header for clients of a shared library to use.
 */
#if defined(_MSC_VER)
#define IMPORT_SYMBOL __declspec(dllimport)
#else
#define IMPORT_SYMBOL
#endif

/* PLATFORM_PUBLIC_API
 *
 * Used for functions which are part of the public API of platform.
 * "Inside" platform (i.e. when compiling platform.so) they will export the
 * symbol
 * "Outside" platform (i.e. when compiling code which wants to link to
 * platform.so) they will allow the symbol to be imported from platform.so
 */
#if defined(platform_EXPORTS) || defined(dirutils_EXPORTS)
#define PLATFORM_PUBLIC_API EXPORT_SYMBOL
#else
#define PLATFORM_PUBLIC_API IMPORT_SYMBOL
#endif
