//
//  Bottle.m
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import "Bottle.h"

#define INCREMENT 50
#define DEFAULT_TRAVEL_BOTTLE 750

@interface Bottle ()
@property (weak, nonatomic) IBOutlet UILabel *minorMajorLabel;
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (nonatomic)  int travelBottle;
@property (weak, nonatomic) IBOutlet UILabel *travelBottleLabel;

@end

@implementation Bottle

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)awakeFromNib {
    if (![[NSUserDefaults standardUserDefaults] valueForKey:@"travelBottle"]) {
        self.travelBottle = DEFAULT_TRAVEL_BOTTLE;
    } else {
        self.travelBottle = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"travelBottle"];
    }
}

- (IBAction)searchForBeacons:(id)sender {
    [self.delegate performLookForBeacons];
}

- (void)updateBeaconData:(ESTBeacon *)beacon {
    self.minorMajorLabel.text = [NSString stringWithFormat:@"Major: %1@, Minor: %2@", beacon.major, beacon.minor];
    self.distanceLabel.text = [NSString stringWithFormat:@"Distance: %@", beacon.distance];
}
- (IBAction)addToBottle:(id)sender {
    self.travelBottle += INCREMENT;
}
- (IBAction)removeFromBottle:(id)sender {
    if (self.travelBottle > 0) {
        self.travelBottle -= INCREMENT;
    }
}

- (void)setTravelBottle:(int)travelBottle {
    _travelBottle = travelBottle;
    self.travelBottleLabel.text = [NSString stringWithFormat:@"%i", travelBottle];
    [[NSUserDefaults standardUserDefaults] setInteger:travelBottle forKey:@"travelBottle"];
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
