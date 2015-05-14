//
//  SelectBeaconVC.h
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ESTBeacon.h"

typedef enum : int
{
    ESTScanTypeBluetooth,
    ESTScanTypeBeacon
    
} ESTScanType;

@interface SelectBeaconVC : UITableViewController

- (id)initWithScanType:(ESTScanType)scanType completion:(void (^)(ESTBeacon *))completion;
@property (nonatomic, weak) ESTBeacon *selectedBeacon;

@end
