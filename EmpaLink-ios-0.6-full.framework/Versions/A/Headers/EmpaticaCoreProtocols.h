//
//  EmpaticaCoreProtocols.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 10/24/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

@protocol EmpaticaDeviceDelegate;
@class EmpaticaDevice;

typedef enum {
    kE2CoreSensorStatusNotOnWrist,
    kE2CoreSensorStatusOnWrist,
    kE2CoreSensorStatusDead
} E2CoreSensorStatus;

typedef enum {
    kE2CoreSensorBVP,
    kE2CoreSensorGSR,
    kE2CoreSensorACC,
    kE2CoreSensorTEMP
} E2CoreSensorType;

typedef enum {
    kCoreBLEStatusNotAvailable,
    kCoreBLEStatusReady,
    kCoreBLEStatusScanning
} Core_BLEStatus;

typedef enum {
    kCoreDeviceStatusDisconnected,
    kCoreDeviceStatusConnecting,
    kCoreDeviceStatusConnected,
    kCoreDeviceStatusDisconnecting
} Core_DeviceStatus;


@protocol Core_EmpaticaDeviceDelegate<NSObject>
- (void)core_didUpdateDeviceStatus:(Core_DeviceStatus)status;
- (void)core_didReceiveBatteryLevel :(float)level withTimestamp:(double)timestamp;

- (void)core_didReceiveIBI:(float)ibi withTimestamp:(double)timestamp;
- (void)core_didReceiveGSR:(float)gsr withTimestamp:(double)timestamp;
- (void)core_didReceiveBVP:(float)bvp withTimestamp:(double)timestamp;
- (void)core_didReceiveTemperature:(float)temp withTimestamp:(double)timestamp;
- (void)core_didReceiveAccelerationX:(char)x y:(char)y z:(char)z withTimestamp:(double)timestamp;

@optional
- (void)core_didReceiveStepOfType:(int)stepType atTimestamp:(double)timestamp;
- (void)core_didReceiveMET:(float)MET andSteps:(int)steps andTemperature:(float)temperature atTimestamp:(double)timestamp forDuration:(float)duration;

@property (nonatomic, readonly,) id<EmpaticaDeviceDelegate> deviceDelegate;

@end

