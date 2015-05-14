//
//  AccManagerC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_AccManagerC_h
#define EmpaLink_AccManagerC_h
#include "CommonC.h"

#include "StepCounterC.h"
#include <stdlib.h>
#include <stdio.h>
#define MEAN_ALPHA 0.05f

typedef struct AccStruct_S{
    char x;
    char y;
    char z;
}AccStruct;

typedef struct AccManagerDelegate_D{
    // Delegate object
    void *delegate;
    
    // Callback functions
    void (*didReceiveStep)(void *delegate, int stepType, float stepFrequency, double timestamp);
}AccManagerDelegate;


typedef struct AccManagerStruct_S{
    StepCounterStruct *stepCounter0;
    StepCounterStruct *stepCounter1;
    StepCounterStruct *stepCounter2;
    StepCounterStruct *stepCounter3;
    
    float meanX;
    float meanY;
    float meanZ;
    
    int wristOrientation;
    double lastStepTimestamp;
    double lastMETFlush;
    
    int nSteps;
    int skippingStep;
    
    AccManagerDelegate delegate;
}AccManagerStruct;

void AccManager_init(AccManagerStruct **selfp);
void AccManager_dealloc(AccManagerStruct *self);

void AccManager_notifyGoodStep(AccManagerStruct *self, int stepType, float stepFrequency, double timestamp);
void AccManager_addAcc(AccManagerStruct *self, int x, int y, int z, double timestamp);
void AccManager_didReceiveStep(void *selfDelegate, int stepType, float stepFrequency, double timestamp);


#endif
