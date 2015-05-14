//
//  firFilterC.c
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/16/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_firFilterC_h
#define EmpaLink_firFilterC_h
#include "CommonC.h"
#include <stdlib.h>
#include "string.h"


typedef struct firFilterStruct_S{
    float *values;
    float *valuesToSum;
    float *coefficients;
    int windowDownsampling;
    int nValues;
    int head;
    
    
}FirFilterStruct;

void FirFilter_init(FirFilterStruct **selfp, int size, float* coefficients, int windowDownsampling);
void FirFilter_dealloc(FirFilterStruct *self);

float FirFilter_filter(FirFilterStruct *self, float sample);
float FirFilter_filterAndSum(FirFilterStruct *self, float sampleToFilter, float sampleToSum);


#endif
