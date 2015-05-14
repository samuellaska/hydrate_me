//
//  IBIStruct.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_IBIStruct_h
#define EmpaLink_IBIStruct_h

typedef struct {  // in milliseconds
    double timestamp;
    float ibi;
    int validity;
} IBIStructC;

#endif
