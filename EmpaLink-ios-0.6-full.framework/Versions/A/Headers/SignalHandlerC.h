//
//  SignalHandlerC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_SignalHandlerC_h
#define EmpaLink_SignalHandlerC_h
#include "CommonC.h"

#define FLUSH_FILE_EVERY 60 // seconds
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#ifdef WIN32
#include <Winsock2.h>
#else
#include <netinet/in.h>
#endif

#include "circularBufferFloatC.h"

typedef struct SignalHandlerStruct_S{
    int bufferLength;
    CircularBufferFloatStruct *signalBuffer;
    char baseDir[256];
    char deviceModel[256];
    char *filename;
    int saveToFile;
    int nSamples;
}SignalHandlerStruct;

void SignalHandler_init(SignalHandlerStruct **selfp, int length, const char* deviceModel, const char* baseDir);
void SignalHandler_dealloc(SignalHandlerStruct *self);

void SignalHandler_flushFileFrom(SignalHandlerStruct *self, int from, int to);
void SignalHandler_addSample(SignalHandlerStruct *self, float sample);
void SignalHandler_closeFile(SignalHandlerStruct *self);
#endif
