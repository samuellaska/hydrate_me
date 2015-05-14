//
//  EmpaticaLinkBLE.h
//  EmpaticaTracker
//
//  Created by Alberto Guarino on 8/6/12.
//  Copyright (c) 2012 Empatica. All rights reserved.
//

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#import <CoreBluetooth/CoreBluetooth.h>
#else
#import <IOBluetooth/IOBluetooth.h>
#endif


#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import "PacketHandlerC.h"
#import "EmpaticaLinkBLEDefines.h"
#import "EmpaLinkConfig.h"
#import "EmpaticaLinkBLEDefines.h"
#import "DeviceLabelsHandler.h"


/*
 1 stream selezione.
 2 stream selezione e mem selezione
 3 stream selezione e mem totale
 */
typedef enum {
    kconnectionTypeStreamingSelection,
    kconnectionTypeStreamingAndMemorySelection,
    kconnectionTypeStreamingAndMemoryFull,
    kconnectionTypeJustUpdateTimestamp
} ConnectionType;

@class EmpaticaLinkBLE;

@protocol EmpaticaLinkBLEDelegate <NSObject>
@optional

- (id<EmpaticaLinkBLEDelegate>)refreshDelegate:(EmpaticaLinkBLE *)superDelegate;
- (void)startStreaming;
- (void)addSampleToBvpRed:( int)sampleRed andGreen:( int)sampleGreen;

// GSR
- (void)addSampleToGsrFast:(unsigned short int)gsrFast andSlow:(unsigned short int)gsrSlow;
- (void)addSampleToGsrForE3Fast:(unsigned short int)gsrFast andSlow:(unsigned short int)gsrSlow;

// ACC
- (void)addSampleToAccX:(char)x accY:(char)y accZ:(char)z;

// Skin temperature
- (void)addSampleToSt:(short int)sample;

// Battery
- (void)addSampleToBattery:(unsigned short int)sample;
- (void)updateBattery:(float)batteryLevel;

// Device name
- (void)setDeviceInfo:(DeviceInfoStruct)deviceInfo;

@end

@protocol EmpaticaLinkSessionDelegate <NSObject>
@optional
- (void)sessionDidEndOnRequest:(BOOL)endOnRequest;
@end

@interface EmpaticaLinkBLE: NSObject <CBCentralManagerDelegate, CBPeripheralDelegate>
-(void)setDeviceInfo:(DeviceInfoStruct)deviceInfo;

@property (nonatomic, strong) CBCentralManager *CM;
@property (nonatomic, strong) NSMutableArray *devices;
@property (nonatomic, assign) ConnectionType connectionType;

- (int)controlSetup:(int)s;
- (int)findBLEPeripherals:(int)timeout;
- (void)connectPeripheral:(CBPeripheral *)peripheral;
- (void)disconnectPeripheral:(CBPeripheral *)peripheral;

+ (EmpaticaLinkBLE *)sharedInstance;

@property (nonatomic, assign) Boolean disconnectionRequested;
@property (nonatomic, weak) id delegate;
@property (nonatomic, weak) id sessionDelegate;
@property (nonatomic, assign) int reconnections;

@property (nonatomic, assign) DeviceInfoStruct deviceInfo;

@end