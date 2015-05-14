//
//  server.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 7/25/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_server_h
#define EmpaLink_server_h
#include "CommonC.h"
#include "DeviceManagerC.h"
#include "server.h"
#include "PacketHandlerC.h"
#include "EmpaticaDeviceManagerCoreC.h"
#include <errno.h>
#ifdef _WIN64
#elif _WIN32
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

typedef struct SessionInfoStruct_S{
    double startTimestamp;
    double sampleRate;

    DeviceInfoStruct deviceInfo;
}SessionInfoStruct;

int Server_readInfo(const char *folder, SessionInfoStruct *sessionInfo);
void Server_reprocessFolder(const char *sourceFolder, const char *destFolder, SessionInfoStruct *sessionInfo);
int Server_processMemoryDump(const char *sourceFile, const char *destFolder, SessionInfoStruct *sessionInfo);

#endif
