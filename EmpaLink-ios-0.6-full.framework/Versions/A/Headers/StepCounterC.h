//
//  StepCounterC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_StepCounterC_h
#define EmpaLink_StepCounterC_h
#include "CommonC.h"

#include  <stdlib.h>
#include <stdio.h>
#include "float.h"

#define DEBUG_STEPS false

#if (DEBUG_STEPS)
#warning DEBUG_STEPS
#endif

typedef struct StepCounterDelegate_D{
    // Delegate object
    void *delegate;
    
    // Callback functions
    void (*didReceiveStep)(void *delegate, int stepType, float stepFrequency, double timestamp);
}StepCounterDelegate;

typedef struct StepCounterStruct_S{
    int type;
    float acc[3];
    float maxID;
    float minID;
    float maxVal;
    float minVal;
    double maxTimestamp;
    long int nSamples;
    int consecutiveSteps;

    double past_x[5];
    double past_y[5];
    
    double lastStepTimestamp;
    
    StepCounterDelegate delegate;
}StepCounterStruct;

void StepCounter_init(StepCounterStruct **selfp, int type);
void StepCounter_dealloc(StepCounterStruct *self);

void StepCounter_addAcc( StepCounterStruct *self, int x, int y, int z, double timestamp);

void StepCounter_type(StepCounterStruct *self, int acc, double timestamp);

/*void StepCounter_type0(StepCounterStruct *self, int acc, double timestamp);
void StepCounter_type1(StepCounterStruct *self, int acc, double timestamp);
void StepCounter_type2(StepCounterStruct *self, int acc, double timestamp);*/

float StepCounter_filter(StepCounterStruct *self, float x);

/*float StepCounter_filter0(StepCounterStruct *self, float x);
float StepCounter_filter1(StepCounterStruct *self, float x);
float StepCounter_filter2(StepCounterStruct *self, float x);*/
#endif
