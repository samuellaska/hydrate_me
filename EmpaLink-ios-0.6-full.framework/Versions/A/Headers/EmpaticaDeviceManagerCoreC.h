//
//  E2DeviceManagerCoreC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_EmpaticaDeviceManagerCoreC_h
#define EmpaLink_EmpaticaDeviceManagerCoreC_h
#include "CommonC.h"

#include "SignalHandlerC.h"
//#include "kalmanFilterC.h"
#include "ButterFilterC.h"
#include "RealtimeHRC.h"
#include "IBIManagerC.h"
#include "AccManagerC.h"
#include "METManagerC.h"
#include "float.h"
#include <errno.h>

typedef struct EmpaticaDeviceManagerCoreDelegate_D{
    // Delegate object
    void *delegate;
    
    // Callback functions
    void (*didReceiveMET)(void *delegate, float MET, int steps, float temperature, float duration, double timestamp);
    void (*didReceiveIBI)(void *delegate, float ibi, double timestamp, int validity);
    void (*didReceiveStep)(void *delegate, int stepType, float stepFrequency, double timestamp);
}EmpaticaDeviceManagerCoreDelegate;





typedef struct EmpaticaDeviceManagerCoreStruct_S{
    EmpaticaDeviceManagerCoreDelegate delegate;
    
}EmpaticaDeviceManagerCoreStruct;

void EmpaticaDeviceManagerCore_init(EmpaticaDeviceManagerCoreStruct **selfp, const char *baseDir);
void EmpaticaDeviceManagerCore_dealloc(EmpaticaDeviceManagerCoreStruct *self);

void EmpaticaDeviceManagerCore_initSignalHandlers(EmpaticaDeviceManagerCoreStruct *self, const char *sessionDir, const char *ibiDir, const char *deviceModel);
void EmpaticaDeviceManagerCore_initSignalHandlersForOfflineFromMemoryDump(EmpaticaDeviceManagerCoreStruct *self, const char *sessionDir, const char *ibiDir, const char *deviceModel, double timestamp);
void EmpaticaDeviceManagerCore_initSignalHandlersForOfflineFolder(EmpaticaDeviceManagerCoreStruct *self, const char *sessionDir, const char *ibiDir, const char *deviceModel, double timestamp);

float EmpaticaDeviceManagerCore_addSampleToBvp(EmpaticaDeviceManagerCoreStruct *self, int sampleRed, int sampleGreen, float sampleRate);
float EmpaticaDeviceManagerCore_addSampleToGsr(EmpaticaDeviceManagerCoreStruct *self, unsigned short int gsrFast, unsigned short int gsrSlow, float sampleRate);
float EmpaticaDeviceManagerCore_addSampleToGsrForE3(EmpaticaDeviceManagerCoreStruct *self, unsigned short int gsrFast, unsigned short int gsrSlow, float sampleRate);

float EmpaticaDeviceManagerCore_addSampleToBattery(EmpaticaDeviceManagerCoreStruct *self, unsigned short int sample, double sampleRate);

AccStruct EmpaticaDeviceManagerCore_addSampleToAcc(EmpaticaDeviceManagerCoreStruct *self, AccStruct acc, double sampleRate);

float EmpaticaDeviceManagerCore_temperatureFromRaw(EmpaticaDeviceManagerCoreStruct *self, short int sample);
float EmpaticaDeviceManagerCore_addSampleToSt(EmpaticaDeviceManagerCoreStruct *self, float sample, double sampleRate);
//void EmpaticaDeviceManagerCore_setDeviceData(EmpaticaDeviceManagerCoreStruct *self, DeviceInfoStruct *deviceInfo);
    
void EmpaticaDeviceManagerCore_setTimestamp(EmpaticaDeviceManagerCoreStruct *self, double timestamp);
void EmpaticaDeviceManagerCore_saveInfoFile(EmpaticaDeviceManagerCoreStruct *self);

//float EmpaticaDeviceManagerCore_computeBvpSampleWithNewAlgorithmFromHolyMatlabwith(EmpaticaDeviceManagerCoreStruct *self, float sampleRed, float sampleGreen, double timestamp);
//void EmpaticaDeviceManagerCore_closeFiles(EmpaticaDeviceManagerCoreStruct *self);    // set active session duration

void EmpaticaDeviceManagerCore_didReceiveIBI(void *delegate, float ibi, double timestamp, int validity);
void EmpaticaDeviceManagerCore_didReceiveMET(void *delegate, float MET, int steps, float temperature, float duration, double timestamp);
void EmpaticaDeviceManagerCore_didReceiveStep(void *delegate, int stepType, float stepFrequency, double timestamp);

#endif
