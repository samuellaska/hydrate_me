//
//  ButterFilterC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/16/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_ButterFilterC_h
#define EmpaLink_ButterFilterC_h
#include "CommonC.h"

#define VERBOSE 0

#include <stdlib.h>
#include <string.h>
#include "iir.h"


typedef enum {
    kButterFilterModeLowPass  = 0,
    kButterFilterModeBandPass = 1
} ButterFilterModeC;


typedef struct ButterFilterStruct_S{
    double *a;
    double *b;
    double *dpast_x;
    double *dpast_y;
    float *fpast_x;
    float *fpast_y;
    
    int filterMode;// 0=low pass
                   // 1=band pass
    int counter;
    int averageWindow;
    float *signalWindow;
    int signalWindowPos;
    float averageSum;
}ButterFilterStruct;

void ButterFilter_init(ButterFilterStruct **selfp);
void ButterFilter_dealloc(ButterFilterStruct *self);

void ButterFilter_filt(ButterFilterStruct *self, float *x, int n, float *y, int reverse);
float ButterFilter_filtOnline(ButterFilterStruct *self, float sample);
float ButterFilter_filtOnlineDouble(ButterFilterStruct *self, double sample);
void ButterFilter_filtDouble(ButterFilterStruct *self, double *x, int n, double *y, int reverse);
void ButterFilter_filtFiltDouble(ButterFilterStruct *self, double *x, int n, double *y);
void ButterFilter_filtFilt(ButterFilterStruct *self, float *x, int n, float *y);

void ButterFilter_setBandPassFromHr(ButterFilterStruct *self, float hr, float sf);
void ButterFilter_setLowPassNormalizedFrequency(ButterFilterStruct *self, float f, int w);


#endif
