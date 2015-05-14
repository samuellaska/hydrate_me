//
//  DailyGoal.m
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import "DailyGoal.h"

#define INCREMENT 50
#define DEFAULT_GOAL 2500


@interface DailyGoal ()
@property (weak, nonatomic) IBOutlet UIScrollView *achievementsScroll;
@property (weak, nonatomic) IBOutlet UILabel *dailyGoalLabel;
@property (nonatomic)  int dailyGoal;
@end

@implementation DailyGoal

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }

    return self;
}

- (void)awakeFromNib {
    if (![[NSUserDefaults standardUserDefaults] valueForKey:@"dailyGoal"]) {
        self.dailyGoal = DEFAULT_GOAL;
    } else {
        self.dailyGoal = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"dailyGoal"];
    }
    self.achievementsScroll.contentSize = CGSizeMake(260, 320);
}

- (void)setDailyGoal:(int)dailyGoal {
    _dailyGoal = dailyGoal;
    self.dailyGoalLabel.text = [NSString stringWithFormat:@"%i", _dailyGoal];
    [[NSUserDefaults standardUserDefaults] setInteger:dailyGoal forKey:@"dailyGoal"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    [self.delegate updateDailyGoal:dailyGoal];
}

- (IBAction)addToGoal {
    self.dailyGoal+=INCREMENT;
}
- (IBAction)removeFromGoal:(id)sender {
    if (self.dailyGoal > 0) {
        self.dailyGoal-=INCREMENT;
    }
}

@end
