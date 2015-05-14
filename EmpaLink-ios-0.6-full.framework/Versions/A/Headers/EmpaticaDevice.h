//
//  EmpaticaDevice.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 10/9/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EmpaticaDeviceManagerCoreC.h"
#import "EmpaticaAPICore.h"
#import "EmpaticaLinkBLE.h"
#import "PacketHandlerC.h"
#import "DeviceManagerC.h"
#import "NSString+HexValue.h"
#import "PacketSaver.h"

#import "EmpaticaLinkBLEDefines.h"

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>
#else
#import <IOBluetooth/IOBluetooth.h>
#import <Cocoa/Cocoa.h>
#endif

#import "EmpaticaCoreProtocols.h"
#import "EmpaLinkConfig.h"
#import "IBIManagerC.h"
#import "EmpaticaLinkBLE.h"
#import "ftime.h"
#import "NSString+HexValue.h"

#define WS 32
#define BASE_BVP_SAMPLE_RATE (63.997037)

// Packet type
#define BTLE_PPG 20
#define BTLE_EDA 24
#define BTLE_ACC 28
#define BTLE_ST 32
#define BTLE_BATT 45

id EmpaticaDevice_self;

@interface EmpaticaDevice : NSObject <CBPeripheralDelegate>

@property (nonatomic, assign) Core_DeviceStatus status;
@property (nonatomic, weak) id<Core_EmpaticaDeviceDelegate> delegate;
@property (nonatomic, assign) float heartRate;
@property (nonatomic, assign) float temperature;
@property (nonatomic, strong) NSMutableArray *heartRateArray;
@property (nonatomic, strong) NSMutableArray *timestampArray;
@property (nonatomic, strong) NSMutableArray *validityArray;
@property (nonatomic, assign) float batteryLevel;
@property (nonatomic, strong) CBCharacteristic *commandCharacteristic;
@property (nonatomic, assign) E2CoreSensorStatus tempStatus;
@property (nonatomic, assign) E2CoreSensorStatus GSRStatus;
@property (nonatomic, assign) E2CoreSensorStatus BVPStatus;
@property (nonatomic, assign) DeviceInfoStruct deviceInfo;
@property (nonatomic, assign) BOOL deviceOnWrist;
@property (nonatomic, strong) EmpaticaLinkBLE *empaticaLink;
@property (nonatomic, assign) PacketHandlerStruct *packetHandler;
@property (nonatomic, assign) PacketSaverStruct *packetSaver;
@property (nonatomic, assign) double actualSampleRate;
@property (nonatomic, assign) DeviceManagerStruct *deviceManager;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *version;
@property (nonatomic, strong) CBPeripheral *peripheral;

- (id)initWithPeripheral:(CBPeripheral *)peripheral;
- (void)connectWithDeviceDelegate:(id<Core_EmpaticaDeviceDelegate>)deviceDelegate andConnectionOptions:(NSArray *)connectionOptions;
- (void)disconnect;
- (void)forceDisconnect;
- (void)getAllCharacteristics:(CBPeripheral *)p;
- (void)updateStatus:(Core_DeviceStatus)status;
- (void)addSampleToSt:(short int)sample;

@end
