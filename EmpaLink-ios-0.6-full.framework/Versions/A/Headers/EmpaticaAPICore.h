//
//  EmpaticaAPICore
//  EmpaLink
//
//  Created by Alberto Guarino on 8/6/12.
//  Copyright (c) 2012 Empatica. All rights reserved.
//
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
    #import <CoreBluetooth/CoreBluetooth.h>
    #import <UIKit/UIKit.h>
#else
    #import <IOBluetooth/IOBluetooth.h>
#endif

#import <Foundation/Foundation.h>
#import "EmpaticaLinkBLE.h"
#import "EmpaticaCoreProtocols.h"
#import "EmpaticaDevice.h"
#import "IBIManagerC.h"
#import "EmpaticaDeviceManagerCoreC.h"
#import "SessionManager.h"

#if defined (API_IOS) || defined (API_OSX)
    #import "EmpaticaAPI_Full-0.6.h"
#else
    #import "EmpaticaAPI-0.6.h"
#endif

typedef enum {
    kUsageModeWrong,
    kUsageModeRight
} UsageMode;

typedef enum {
    kKeyModeAPIKeyNotSet,
    kKeyModeWrongAPIKeySet,
    kKeyModeRightAPIKeySet,
    kKeyModeAuthenticationError
} KeyMode;

typedef enum {
    kAuthenticationStatusAuthorized,
    kAuthenticationStatusNotAuthorized,
    kAuthenticationStatusUnknown
} AuthenticationStatus;

// ----------------------------------------
@protocol EmpaticaBLECoreStatusDelegate<NSObject>

- (void)didDiscoverDevicesCore:(NSArray *)devices;
- (void)didUpdateBLEStatusCore:(BLEStatus)status;

@end
// ----------------------------------------

@interface EmpaticaAPICore : NSObject <EmpaticaLinkSessionDelegate>

@property (nonatomic, weak) id<EmpaticaBLECoreStatusDelegate> statusDelegate;

+ (EmpaticaAPICore *)sharedInstance;
- (void)discover;

@property (nonatomic, assign) BOOL appIsInBackground;

- (void)prepareForBackground;
- (void)prepareForResume;

@property (nonatomic, assign) Core_BLEStatus status;

- (void)updateBLEStatus:(Core_BLEStatus)status;
- (void)authenticateWithAPIKey:(NSString *)key andCompletionHandler:(void (^)(BOOL success, NSString *description))handler;
#ifndef VERSION_FOR_DISTRIBUTION
- (void)authenticateWithoutAPIKey;
#endif
- (AuthenticationStatus)authenticationStatus;

@property (nonatomic, strong) EmpaticaLinkBLE *empaticaLink;
@property (nonatomic, assign) BOOL deviceOnWrist;

@property (nonatomic, assign) EmpaticaDeviceManagerCoreStruct *empaticaCore;

- (void)addConnectedDevice:(EmpaticaDevice *)device;
- (void)removeConnectedDevice:(EmpaticaDevice *)device;
- (void)disconnectAllDevices;


@end
