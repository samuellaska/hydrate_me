//
//  SessionManager.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 2/19/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
    #import <UIKit/UIKit.h>
#endif
#import "AFNetworking.h"
#import <Foundation/Foundation.h>
#import "ZipFile.h"
#import "ZipException.h"
#import "FileInZipInfo.h"
#import "ZipWriteStream.h"
#import "ZipReadStream.h"
#import "EmpaLinkConfig.h"
#import "EmpaLinkUtils.h"

#define UPLOAD_DEBUG NO

typedef enum {
    kE2CoreSessionEventSessionStarted,
    kE2CoreSessionEventSessionFinished,
    kE2CoreSessionEventUploadProgressUpdate,
    kE2CoreSessionEventUploadError,
    kE2CoreSessionEventErrorUnauthorizedUser
} Core_SessionEvent;

typedef enum {
    kApiModeApiKey,
    kApiModeUserAccount
} ApiMode;

@protocol SessionManagerStatusDelegate<NSObject>
- (void)core_didUpdateSessionStatus:(Core_SessionEvent)event progress:(float)progress;
@end

@interface SessionManager : NSObject

@property (nonatomic, weak) id<SessionManagerStatusDelegate> statusDelegate;

@property (nonatomic, assign) int totalSessionsToUpload;
@property (nonatomic, assign) int sessionsUploaded;
@property (nonatomic, assign) float zippingProgress;
@property (nonatomic, assign) long long int totalBytesToUpload;
@property (nonatomic, assign) long long int bytesUploaded;
@property (nonatomic, assign) BOOL isUploading;
@property (nonatomic, assign) BOOL isZipping;
@property (nonatomic, assign) BOOL isCheckingForAuthentication;

//@property (nonatomic, assign) double currentSessionDuration; // DEV
@property (nonatomic, copy) NSString *currentSessionId;

+ (void)harvestAndUpload;
+ (void)setStatusDelegate:(id<SessionManagerStatusDelegate>)delegate;
+ (void)setApiMode:(ApiMode)apiMode;
+ (ApiMode)apiMode;

@end
