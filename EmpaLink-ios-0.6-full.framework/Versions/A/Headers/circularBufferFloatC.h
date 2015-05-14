//
//  circularBufferFloatC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_circularBufferFloatC_h
#define EmpaLink_circularBufferFloatC_h
#include "CommonC.h"

#include <stdlib.h>
#include <string.h>

typedef enum {
    kCircularBufferCTypeNormal,
    kCircularBufferCTypeNeverAhorse  // The last windowSize values are copied to the beginning of the array so that
} CircularBufferCType;              // the last window of data can always be passed as array to a function.

typedef struct CircularBufferFloatStruct_S{
    float *buffer;
    int windowSize;
    int headID;
    int dimension;
    int size;
    int tailID;
    CircularBufferCType bufferType;
    char baseDir[256];
}CircularBufferFloatStruct;

void CircularBufferFloat_init(CircularBufferFloatStruct **selfp, int dimension, CircularBufferCType bufferType, int windowSize,const char *baseDir);
void CircularBufferFloat_dealloc(CircularBufferFloatStruct *self);

void CircularBufferFloat_pushFloat(CircularBufferFloatStruct *self, float newFloat);
float CircularBufferFloat_valueAtIndex(CircularBufferFloatStruct *self, int index);



#endif
