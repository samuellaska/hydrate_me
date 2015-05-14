//
//  MatlabHelperC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 8/5/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_MatlabHelperC_h
#define EmpaLink_MatlabHelperC_h
#include "CommonC.h"

#define DETREND_CONSTANT 0
#define DETREND_LINEAR   1

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "matlabCodedToolkit.h"
#include "matlabCodedToolkit_types.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

typedef struct MatlabHelperStruct_S{

}MatlabHelperStruct;

void MatlabHelper_init(MatlabHelperStruct **selfp);
void MatlabHelper_dealloc(MatlabHelperStruct *self);

    
    
double MatlabHelper_meanFrequency(double *ibi, int n);
void MatlabHelper_hamming(int n, double *w);
void MatlabHelper_frequencyBands(double *ibi, int n, double *LF, double *HF, double *TP, double *WBI);

double MatlabHelper_std(double data[], int n);

#endif
