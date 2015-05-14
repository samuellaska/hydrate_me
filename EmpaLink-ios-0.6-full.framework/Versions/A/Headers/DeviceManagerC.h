//
//  DeviceManagerC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/20/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_DeviceManagerC_h
#define EmpaLink_DeviceManagerC_h
#include "CommonC.h"
#include "SignalHandlerC.h"
#include "RealtimeHRC.h"
#include "IBIManagerC.h"
#include "METManagerC.h"
#include "AccManagerC.h"
#include "kalmanFilterC.h"
#include "kalmanFilterC_v1.h"
#include "AccManagerC.h"
#include "firFilterC.h"
#include "GSRCalibrationData.h"
#include <stdlib.h>

//#define NEW_KALMAN_VERSION
 
/*
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "EmpaticaDeviceManagerCoreC.h"*/

typedef struct DeviceInfoStruct_S{
    char ID[256];
    
    char model[256];
    int hardwareVersion;
    int firmwareVersion;
}DeviceInfoStruct;

typedef enum {
    kE2CoreSensorStatusCNotOnWrist,
    kE2CoreSensorStatusCOnWrist,
    kE2CoreSensorStatusCDead
} E2CoreSensorStatusC;


typedef struct DeviceManagerDelegate_D{
    // Delegate object
    void *delegate;
    
    // Callback functions
    void (*didReceiveMET)(void *delegate, float MET, int steps, float temperature, float duration, double timestamp);
    void (*didReceiveIBI)(void *delegate, float ibi, double timestamp, int validity);
    void (*didReceiveStep)(void *delegate, int stepType, float stepFrequency, double timestamp);
}DeviceManagerDelegate;

typedef struct DeviceManagerStruct_S{
    int nBvp;
    int nGsr;

    E2CoreSensorStatusC tempStatus;
    E2CoreSensorStatusC GSRStatus;
    E2CoreSensorStatusC BVPStatus;
    
    ButterFilterStruct *bf_green;
    ButterFilterStruct *bf_red;
    ButterFilterStruct *bf_gsr;

    FirFilterStruct *fir_green;
    FirFilterStruct *fir_red;
    FirFilterStruct *fir_kalman;
    
#ifdef NEW_KALMAN_VERSION
    KalmanFilterStruct *kf_bvp;
#else
    kalmanFilter_v1Struct *kf_bvp;
#endif
    double bvpTimestamp;
    double gsrTimestamp;
    double accTimestamp;
    double stTimestamp;
    double battTimestamp;
    
    float temperature;
    float batteryLevel;
    
    RealtimeHRStruct *realtimeHr;
    IBIManagerStruct *IBIMgrRealtime;
    
    SignalHandlerStruct *gsr;
    SignalHandlerStruct *gsr_fast;
    SignalHandlerStruct *gsr_slow;
    SignalHandlerStruct *battery;
    SignalHandlerStruct *st;
    SignalHandlerStruct *accX;
    SignalHandlerStruct *accY;
    SignalHandlerStruct *accZ;
    SignalHandlerStruct *bvp;
    SignalHandlerStruct *bvp_red;
    SignalHandlerStruct *bvp_green;
    
    AccManagerStruct *accManager;
    METManagerStruct *METManager;
    
    DeviceInfoStruct deviceInfo;

    // Sessions
    char baseDir[256];
    char sessionDir[256];
    char ibiDir[256];
    
    int sessionID;
    double startSessionTimestamp;
    
    int saveInfoFileToDisk;
    
    int currentRawTemperature;
    
    int temperatureForCurrentTonicEDA;
    int lastTonicEDA;
    int lastConductance;
    
    float deltaZero;
    
    DeviceManagerDelegate delegate;
}DeviceManagerStruct;

void DeviceManager_init(DeviceManagerStruct **selfp, const char *baseDir);
void DeviceManager_dealloc(DeviceManagerStruct *self);

void DeviceManager_initSignalHandlers(DeviceManagerStruct *self, const char *sessionDir, const char *ibiDir, const char *deviceModel);
void DeviceManager_initSignalHandlersForOfflineFolder(DeviceManagerStruct *self, const char *sessionDir, const char *ibiDir, const char *deviceModel, double timestamp);
void DeviceManager_initSignalHandlersForOfflineFromMemoryDump(DeviceManagerStruct *self, const char *sessionDir, const char *ibiDir, const char *deviceModel, double timestamp);

void DeviceManager_setDeviceData(DeviceManagerStruct *self, DeviceInfoStruct *deviceInfo);

void DeviceManager_closeFiles(DeviceManagerStruct *self);
void DeviceManager_saveInfoFile(DeviceManagerStruct *self);


float DeviceManager_temperatureFromRaw(DeviceManagerStruct *self, short int sample);
float DeviceManager_addSampleToSt(DeviceManagerStruct *self, float sample, double sampleRate);
float DeviceManager_addSampleToBattery(DeviceManagerStruct *self, unsigned short int sample, double sampleRate);
float DeviceManager_addSampleToGsr(DeviceManagerStruct *self, unsigned short int gsrFast, unsigned short int gsrSlow, float sampleRate);
float DeviceManager_addSampleToGsrForE3(DeviceManagerStruct *self, unsigned short int gsrFast, unsigned short int gsrSlow, float sampleRate);
float DeviceManager_addSampleToBvp(DeviceManagerStruct *self, int sampleRed, int sampleGreen, float sampleRate);
AccStruct DeviceManager_addSampleToAcc(DeviceManagerStruct *self, AccStruct acc, double sampleRate);

#endif
