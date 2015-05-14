//
//  kalmanFilterC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/16/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_kalmanFilter_v1C_h
#define EmpaLink_kalmanFilter_v1C_h
#include "CommonC.h"

#include <stdlib.h>


typedef struct kalmanFilter_v1Struct_S{
    int nSamples;
    int windowsLength;
    float sigma;
    float *signalBuffer;
    float *movementBuffer;
    float lastSignalSample;
    float *lastMovementSamples;
    
    float *W;  // state
    float *K;  // kalman gain
    
    float *P_new; //state covariance matrix
    float *P_old; //state covariance matrix
    float *I;
    float *Q;
    float *mp;
    
    int dimensionM;
    int dimensionS;
    
    int headM;
    int headS;
    int tailM;
    int tailS;
    
    float coeff1;
    float coeff2;
    
}kalmanFilter_v1Struct;

void KalmanFilter_v1_init(kalmanFilter_v1Struct **selfp, int numberOfSamples, int windowsLength, float sigma);
void KalmanFilter_v1_dealloc(kalmanFilter_v1Struct *self);

float KalmanFilter_v1_evaluate(kalmanFilter_v1Struct *self, float s, float m);


#endif
