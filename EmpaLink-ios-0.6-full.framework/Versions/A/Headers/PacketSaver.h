//
//  PacketSaverC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_PacketSaverC_h
#define EmpaLink_PacketSaverC_h
#include "CommonC.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PACKET_SIZE 21
#define BUFF_SIZE (PACKET_SIZE*32)

typedef struct PacketSaverrStruct_S{
    char baseDir[256];
    char deviceID[256];
    char sessionID[256];
    char fileName[256];
    FILE *fOut;
    
    // Buffers
    char **buffers;
    unsigned int n;
    unsigned short int currentBuffer;
}PacketSaverStruct;

void PacketSaver_init(PacketSaverStruct **selfp, const char* baseDir, const char* deviceID, const char* sessionID);
void PacketSaver_dealloc(PacketSaverStruct *self);

void PacketSaver_addPacket(PacketSaverStruct *self, const char* packet);
void PacketSaver_flushAndCloseFile(PacketSaverStruct *self);

#endif
