#ifndef SAMPLING_ENGINE_ERROR_CODES_H__
#define SAMPLING_ENGINE_ERROR_CODES_H__

#include <stdint.h>

//! Error Code Mask
#define SAMPLING_ENGINE_MASK_ERROR_VALUE             (0x7000000000000000)

//! Is the value an error code?
#define SAMPLING_ENGINE_IS_ERROR_CODE(e) ((e & ((uint32_t)0x8000000000000000)) == ((uint32_t)0x8000000000000000))
//! Retrieve the error code from the value
#define SAMPLING_ENGINE_GET_ERROR_CODE(e) (e & ((uint32_t)(~SAMPLING_ENGINE_MASK_ERROR_VALUE)))
//! Take an error code and apply the masking
#define SAMPLING_ENGINE_MAKE_ERROR_CODE(e) ((int32_t)(((uint32_t)e)|((uint32_t)SAMPLING_ENGINE_MASK_ERROR_VALUE)))
//! Compare a value and error code, return boolean
#define SAMPLING_ENGINE_MATCHES_ERROR_CODE(v, e) (SAMPLING_ENGINE_MAKE_ERROR_CODE(e) == v)
//! Short-cut for validating success
#define SAMPLING_ENGINE_CHECK_SUCCESS(v) (SAMPLING_ENGINE_MATCHES_ERROR_CODE(v, SAMPLING_ENGINE_ERROR_SUCCESS))

#define SAMPLING_ENGINE_ERROR_SUCCESS                (0x0000000000000000) /*!< Success - No Error */
#define SAMPLING_ENGINE_ERROR_BAD_PARAMETER          (0x0000000000000001) /*!< Bad parameter was passed to the function */
#define SAMPLING_ENGINE_ERROR_NOT_INITIALIZED        (0x0000000000000002) /*!< Engine Not initialized */
#define SAMPLING_ENGINE_ERROR_ALREADY_INITIALIZED    (0x0000000000000003) /*!< Engine is already initialized */
#define SAMPLING_ENGINE_ERROR_FILTER_MISMATCH        (0x0000000000000004) /*!< Filter mis-match */
#define SAMPLING_ENGINE_ERROR_MEMORY_ALLOCATION      (0x0000000000000005) /*!< Unable to allocate memory */
#define SAMPLING_ENGINE_ERROR_FILTER_NOT_PRIMED      (0x0000000000000006) /*!< Filter not ready */
#define SAMPLING_ENGINE_ERROR_INVALID_POINTER        (0x0000000000000007) /*!< Invalid pointer (Special case of Bad Parameter) */
#define SAMPLING_ENGINE_ERROR_DEPENDENCY_NOT_FOUND   (0x0000000000000008) /*!< Calculation dependency not found */
#define SAMPLING_ENGINE_ERROR_NO_RECORDS_AVAILABLE   (0x0000000000000009) /*!< No records are currently available */
#define SAMPLING_ENGINE_ERROR_INVALID_STATE          (0x000000000000000A) /*!< System is in an invalid state */

#define SAMPLING_ENGINE_ERROR_MAX                    ( SAMPLING_ENGINE_ERROR_INVALID_STATE + 1) /*!< Maximum Error Value */

#endif //SAMPLING_ENGINE_ERROR_CODES_H__
