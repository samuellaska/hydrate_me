//
//  IBICircularBufferC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_IBICircularBufferC_h
#define EmpaLink_IBICircularBufferC_h
#include "CommonC.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
//#include <inttypes.h>
#include "ftime.h"
#include "IBIStruct.h"

#define FLUSH_EVERY 30
#define E2_DEVICE_ID 0
#define H7_DEVICE_ID 1
#define A1_DEVICE_ID 2


typedef struct IBICircularBufferStruct_S{
    IBIStructC *buffer;
    int head;
    int tail;
    int lastFlushedTail;
    int invalidBeats;
    int saveIBIToFile;
    float timeInvalid;
    int dimension;
    int dataFromDevice;

    // Timestamp
    double initialTimestamp;

    char filePath[256];
    char filePathSession[256];
    int fileHeaderWritten;
}IBICircularBufferStruct;

void IBICircularBuffer_init(IBICircularBufferStruct **selfp, int dimension, int deviceID);
void IBICircularBuffer_dealloc(IBICircularBufferStruct *self);

void IBICircularBuffer_pushIBI(IBICircularBufferStruct *self, IBIStructC ibi);
void IBICircularBuffer_pushIBIWithValidity(IBICircularBufferStruct *self, float ibi, int v, double timestamp);
void IBICircularBuffer_flushToFile(IBICircularBufferStruct *self);
int IBICircularBuffer_actualDimension(IBICircularBufferStruct *self);
void IBICircularBuffer_shrinkBufferToLastSeconds(IBICircularBufferStruct *self, float s);
int IBICircularBuffer_copyBufferForLombScargle(IBICircularBufferStruct *self, double *x, double *y);
    
#endif
