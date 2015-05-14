//
//  Bottle.h
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ESTBeacon.h"

@protocol BottleBeaconProtokol <NSObject>

- (void)performLookForBeacons;

@end

@interface Bottle : UIView

@property (nonatomic, weak) id<BottleBeaconProtokol> delegate;

- (void)updateBeaconData:(ESTBeacon *)beacon;

@end
