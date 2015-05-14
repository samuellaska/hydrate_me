//
//  METManagerC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/18/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_METManagerC_h
#define EmpaLink_METManagerC_h
#include "CommonC.h"

#include <stdlib.h>
#include <time.h>

#include "stdio.h"
#include "string.h"

#if !defined(MIN)
#define MIN(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#endif
#if !defined(MAX)
#define MAX(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })
#endif

#define ACTIVITY_INERTIA 5 //seconds
#define MET_INTERVAL (60) //Seconds

typedef struct METManagerDelegate_D{
    // Delegate object
    void *delegate;
    
    // Callback functions
    void (*didReceiveMET)(void *delegate, float MET, int steps, float temperature, float duration, double timestamp);
}METManagerDelegate;

typedef struct METManagerHRStruct_S{
    float hr;
    double timestamp;
}METManagerHRStruct;

typedef struct METManagerHRArray_S{
    METManagerHRStruct hr[2*MET_INTERVAL*10];
    int n;
}METManagerHRArray;

typedef struct METManagerTemperatureStruct_S{
    float temperature;
    double timestamp;
}METManagerTemperatureStruct;

typedef struct METManagerTemperatureArray_S{
    METManagerTemperatureStruct temperature[2*MET_INTERVAL*10];
    int n;
}METManagerTemperatureArray;

typedef struct METManagerGSRStruct_S{
    float gsr;
    double timestamp;
}METManagerGSRStruct;

typedef struct METManagerACCStruct_S{
    char x;
    char y;
    char z;
    double timestamp;
}METManagerACCStruct;

typedef struct METManagerACCPeaksStruct_S{
    int x;
    int y;
    int z;
    char sum;
}METManagerACCPeaksStruct;

typedef struct METManagerGSRArray_S{
    METManagerGSRStruct gsr[2*MET_INTERVAL*10];
    int n;
}METManagerGSRArray;

typedef struct METManagerACCArray_S{
    METManagerACCStruct acc[2*MET_INTERVAL*60];
    int n;
}METManagerACCArray;

typedef struct METManagerStepStruct_S{
    int type;
    float frequency;
    double timestamp;
}METManagerStepStruct;

typedef struct METManagerStepArray_S{
    METManagerStepStruct step[2*MET_INTERVAL*10];
    int n;
}METManagerStepArray;

typedef struct METManagerStruct_S{
    int lastNSteps;
    double lastMETInterval;
    float currentMET;
    float cumulativeMET;
    char saveDir[256];
    int metFileNeedsHeader;
    int saveToFile;
    
    float lastGoodHR;
    
    METManagerHRArray hrArray;
    METManagerStepArray stepArray;
    METManagerTemperatureArray tempArray;
    METManagerGSRArray gsrArray;
    METManagerACCArray accArray;
    METManagerACCArray accDiffArray;
    
    METManagerACCPeaksStruct accPeaks2;
    METManagerACCPeaksStruct accPeaks4;
    METManagerACCPeaksStruct accPeaks8;
    
    METManagerDelegate delegate;
}METManagerStruct;


void METManager_init(METManagerStruct **selfp, const char *saveDir);
void METManager_dealloc(METManagerStruct *self);

void METManager_flushMETAtTimestamp(METManagerStruct *self, double timestamp);
void METManager_tic(METManagerStruct *self, double timestamp);


void METManager_addGsr(METManagerStruct *self, float gsr, double timestamp);
void METManager_addTemperature(METManagerStruct *self, float temperature, double timestamp);
void METManager_addHr(METManagerStruct *self, float hr, double timestamp);
void METManager_addStep(METManagerStruct *self, int type, float frequency, double timestamp);
void METManager_addACC(METManagerStruct *self, char x, char y, char z, double timestamp);
    
#endif
