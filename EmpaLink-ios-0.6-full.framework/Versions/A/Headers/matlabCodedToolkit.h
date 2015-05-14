#ifndef __MATLABCODEDTOOLKIT_H__
#define __MATLABCODEDTOOLKIT_H__
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "matlabCodedToolkit_types.h"
extern void detrendC(const emxArray_real_T *x, int32_T order, emxArray_real_T *y);
extern emxArray_int32_T *emxCreateND_int32_T(int32_T numDimensions, int32_T *size);
extern emxArray_real32_T *emxCreateND_real32_T(int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateND_real_T(int32_T numDimensions, int32_T *size);
extern emxArray_int32_T *emxCreateWrapperND_int32_T(int32_T *data, int32_T numDimensions, int32_T *size);
extern emxArray_real32_T *emxCreateWrapperND_real32_T(real32_T *data, int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(real_T *data, int32_T numDimensions, int32_T *size);
extern emxArray_int32_T *emxCreateWrapper_int32_T(int32_T *data, int32_T rows, int32_T cols);
extern emxArray_real32_T *emxCreateWrapper_real32_T(real32_T *data, int32_T rows, int32_T cols);
extern emxArray_real_T *emxCreateWrapper_real_T(real_T *data, int32_T rows, int32_T cols);
extern emxArray_int32_T *emxCreate_int32_T(int32_T rows, int32_T cols);
extern emxArray_real32_T *emxCreate_real32_T(int32_T rows, int32_T cols);
extern emxArray_real_T *emxCreate_real_T(int32_T rows, int32_T cols);
extern void emxDestroyArray_int32_T(emxArray_int32_T *emxArray);
extern void emxDestroyArray_real32_T(emxArray_real32_T *emxArray);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void locallyWeightedRegression(const emxArray_real32_T *inputVector, const emxArray_int32_T *windowLength, int32_T lastElement, real32_T indexesToDelete, emxArray_real32_T *outputVector);
extern void lombC(emxArray_real_T *x, emxArray_real_T *t, emxArray_real_T *P, emxArray_real_T *f);
extern void matlabCodedToolkit_initialize(void);
extern void matlabCodedToolkit_terminate(void);
extern void polyFilter(const emxArray_real32_T *ibi, emxArray_real32_T *ibiPolyFiltered);
extern real_T trapzC(const emxArray_real_T *x, const emxArray_real_T *y);
#endif
