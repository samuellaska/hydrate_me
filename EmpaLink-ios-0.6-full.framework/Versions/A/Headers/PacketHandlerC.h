//
//  PacketHandlerC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/20/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_PacketHandlerC_h
#define EmpaLink_PacketHandlerC_h
#include "CommonC.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "DeviceManagerC.h"

typedef struct PacketHandlerDelegate_D{
    // Delegate object
    void *delegate;
    
    // Callback functions
    void (*addSampleToBvp)(void *delegate, int sampleRed, int sampleGreen);
    void (*addSampleToGsrForE3)(void *delegate, unsigned short int gsrFast, unsigned short int gsrSlow);
    void (*addSampleToAcc)(void *delegate, char x, char y, char z);
    void (*addSampleToBattery)(void *delegate, unsigned short int sample);
    void (*addSampleToSt)(void *delegate, short int sample);
}PacketHandlerDelegate;

typedef enum {
    kPacketHandlerPacketTypeBVP,
    kPacketHandlerPacketTypeGSR,
    kPacketHandlerPacketTypeAcc,
    kPacketHandlerPacketTypeTemperature,
    kPacketHandlerPacketTypeBattery,
} PacketHandlerPacketType;

typedef struct PacketHandlerStruct_S{
    unsigned char bvp_flow_cnt;
    unsigned char gsr_flow_cnt;
    unsigned char acc_flow_cnt;
    unsigned char batt_flow_cnt;
    
    int cumRed;
    int cumGreen;
    
    int nBvp;
    int nGsr;
    int nAcc;
    int nTemp;
    int nBatt;
    
    DeviceInfoStruct deviceInfo;
    
    PacketHandlerDelegate delegate;
}PacketHandlerStruct;

void PacketHandler_init(PacketHandlerStruct **selfp);
void PacketHandler_dealloc(PacketHandlerStruct *self);


void PacketHandler_resetCounters(PacketHandlerStruct *selfp);
void PacketHandler_handlePacket(PacketHandlerStruct *self, char *packet, PacketHandlerPacketType packetType );
void PacketHandler_setDeviceInfo(PacketHandlerStruct *self, DeviceInfoStruct *deviceInfo);
#endif
