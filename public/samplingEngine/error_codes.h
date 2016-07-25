#ifndef SAMPLING_ENGINE_ERROR_CODES_H__
#define SAMPLING_ENGINE_ERROR_CODES_H__

#include <stdint.h>

#define SAMPLING_ENGINE_MASK_ERROR_VALUE             (0x7000000000000000)

#define SAMPLING_ENGINE_IS_ERROR_CODE(e) ((e & ((uint32_t)0x8000000000000000)) == ((uint32_t)0x8000000000000000))
#define SAMPLING_ENGINE_GET_ERROR_CODE(e) (e & ((uint32_t)(~SAMPLING_ENGINE_MASK_ERROR_VALUE)))
#define SAMPLING_ENGINE_MAKE_ERROR_CODE(e) ((int32_t)(((uint32_t)e)|((uint32_t)SAMPLING_ENGINE_MASK_ERROR_VALUE)))
#define SAMPLING_ENGINE_MATCHES_ERROR_CODE(v, e) (SAMPLING_ENGINE_MAKE_ERROR_CODE(e) == v)
#define SAMPLING_ENGINE_CHECK_SUCCESS(v) (SAMPLING_ENGINE_MATCHES_ERROR_CODE(v, SAMPLING_ENGINE_ERROR_SUCCESS))

#define SAMPLING_ENGINE_ERROR_SUCCESS                (0x0000000000000000)
#define SAMPLING_ENGINE_ERROR_BAD_PARAMETER          (0x0000000000000001)
#define SAMPLING_ENGINE_ERROR_NOT_INITIALIZED        (0x0000000000000002)
#define SAMPLING_ENGINE_ERROR_ALREADY_INITIALIZED    (0x0000000000000003)
#define SAMPLING_ENGINE_ERROR_FILTER_MISMATCH        (0x0000000000000004)
#define SAMPLING_ENGINE_ERROR_MEMORY_ALLOCATION      (0x0000000000000005)
#define SAMPLING_ENGINE_ERROR_FILTER_NOT_PRIMED      (0x0000000000000006)
#define SAMPLING_ENGINE_ERROR_INVALID_POINTER        (0x0000000000000007)
#define SAMPLING_ENGINE_ERROR_DEPENDENCY_NOT_FOUND   (0x0000000000000008)
#define SAMPLING_ENGINE_ERROR_NO_RECORDS_AVAILABLE   (0x0000000000000009)
#define SAMPLING_ENGINE_ERROR_INVALID_STATE          (0x0000000000000010)

#endif //SAMPLING_ENGINE_ERROR_CODES_H__
