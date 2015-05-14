//
//  IBIManagerC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_IBIManagerC_h
#define EmpaLink_IBIManagerC_h
#include "IBICircularBufferC.h"
#include "ButterFilterC.h"
#include "math.h"

#define BAR_DURATION 300
#define HRV_TIME_WINDOW (5*60)

typedef struct IBIManagerDelegate_D{
    // Delegate object
    void *delegate;

    // Callback functions
    void (*didReceiveIBI)(void *delegate, float ibi, double timestamp, int validity);
    void (*didReceiveStressData)(void *delegate, double WBI, int duration, double LF, double HF, float HR, int nBeats, double totalPower, int nSkippedBeats, float timeSkippedBeats, double timestamp);
}IBIManagerDelegate;

typedef struct IBIManagerStruct_S{
    IBICircularBufferStruct *ibiCB;
    IBICircularBufferStruct *ibiCB_filtered;
    int saveIBIToFile;
    int calculateStress;
    int consecutivesGoodBeats;
    int device_id;
    IBIStructC ibiArray[3];
    ButterFilterStruct *butterFilter;
    
    // Timestamp
    double startingTimestamp;
    double incrementalTimestamp;
    
    
    float lastButteredHR;
    float lastDynThreshold;
    double lastHRVCalculation;
    
    IBIManagerDelegate delegate;
}IBIManagerStruct;


void IBIManager_init(IBIManagerStruct **selfa, int device_ID);
void IBIManager_dealloc(IBIManagerStruct *self);
    
int IBIManager_isIbiStructValid(IBIManagerStruct *self, IBIStructC ibi);
int IBIManager_IBIValidity(IBIManagerStruct *self, float ibi);
void IBIManager_addRawIbiStruct(IBIManagerStruct *self, IBIStructC ibi);
void IBIManager_addRawIbi(IBIManagerStruct *self, float ibi);
int IBIManager_addRawIbiWithValidity(IBIManagerStruct *self, float ibi, int validity);
void IBIManager_flushToFile(IBIManagerStruct *self);
void IBIManager_setStartingTimestamp(IBIManagerStruct *self, double timestamp);
#endif
