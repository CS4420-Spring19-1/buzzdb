// MACROS

#pragma once

#include <assert.h>
#include <stdexcept>

#include <glog/logging.h>

namespace engine {

//===--------------------------------------------------------------------===//
// attributes
//===--------------------------------------------------------------------===//

#define NEVER_INLINE __attribute__((noinline))
#define ALWAYS_INLINE __attribute__((always_inline))
#define UNUSED_ATTRIBUTE __attribute__((unused))

//===--------------------------------------------------------------------===//
// ALWAYS_ASSERT
//===--------------------------------------------------------------------===//

#ifdef NDEBUG
#define PL_ASSERT(expr) ((void)0)
#else
#define PL_ASSERT(expr) assert((expr))
#endif /* NDEBUG */

#ifdef CHECK_INVARIANTS
#define INVARIANT(expr) PL_ASSERT(expr)
#else
#define INVARIANT(expr) ((void)0)
#endif /* CHECK_INVARIANTS */


const size_t INVALID_KEY = INT32_MAX;
const size_t INVALID_VALUE = INT32_MAX - 1;

const size_t CLEAN_BLOCK = 100;
const size_t DIRTY_BLOCK = 101;

}  // End engine namespace
