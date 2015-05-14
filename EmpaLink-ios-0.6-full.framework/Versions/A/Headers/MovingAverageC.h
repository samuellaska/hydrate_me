//
//  MovingAverageC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/16/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_MovingAverageC_h
#define EmpaLink_MovingAverageC_h
#include "CommonC.h"

#define VERBOSE 0

#include <stdlib.h>
#include <string.h>
#include "iir.h"


typedef struct MovingAverageStruct_S{
    int size;
    int head;
    
    float *values;
    
    float sum;
}MovingAverageStruct;

void MovingAverage_init(MovingAverageStruct **selfp, int size);
void MovingAverage_dealloc(MovingAverageStruct *self);

float MovingAverage_filt(MovingAverageStruct *self, float x);

#endif
