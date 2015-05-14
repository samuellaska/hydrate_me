//
//  kalmanFilterC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/16/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_kalmanFilterC_h
#define EmpaLink_kalmanFilterC_h
#include "CommonC.h"
#include <stdlib.h>
#include "string.h"


typedef struct kalmanFilterStruct_S{
    int L;
    double sigma;
    double sigma_min;
    double sigma_max;
    double sigma_step;
    float mu;
    float *desiredBuffer;
    float *inputBuffer;
    int samplesToSkip;
    
    float *W;  // state
    float *K;  // kalman gain
    
    float *P_new; //state covariance matrix
    float *P_old; //state covariance matrix
    float *I;
    double *Q;
    float *mp;
    
    float coeff1;
    float coeff2;
    float coeff3;
    
}KalmanFilterStruct;

void KalmanFilter_init(KalmanFilterStruct **selfp, int sigma_kfStepN, int L, double sigma_kf);
void KalmanFilter_dealloc(KalmanFilterStruct *self);

float KalmanFilter_evaluate(KalmanFilterStruct *self, float s, float m);


#endif
