//
//  RealtimeHRC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_RealtimeHRC_h
#define EmpaLink_RealtimeHRC_h
#include "CommonC.h"

#include "ButterFilterC.h"
#include "float.h"
#include "IBIStruct.h"

typedef struct RealtimeHRStruct_S{
    double lastTimestamp;
    float hrPrevious;
    float maxBvpValue;
    float minBvpValue;
    
    double currentMaxTimestamp;
    double lastMaxTimestamp;
    
    ButterFilterStruct *bf;
    float last_bvp_values[2];
    float last_filtered_values[2];
    
    int nSamples;
}RealtimeHRStruct;


void RealTimeHR_init(RealtimeHRStruct **selfp);
void RealTimeHR_dealloc(RealtimeHRStruct *self);

void RealTimeHR_setBandPass(RealtimeHRStruct *self, float hr, float sf);
IBIStructC RealTimeHR_detectHeartBeat(RealtimeHRStruct *self, float bvpSample, double timestamp);
float RealTimeHR_hrFromBvp(RealtimeHRStruct *self, float bvpSample, double timestamp);


#endif
