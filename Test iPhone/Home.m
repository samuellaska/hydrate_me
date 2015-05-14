//
//  Home.m
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import "Home.h"

#define DEFAULT_GOAL 2500

@interface Home ()
@property (weak, nonatomic) IBOutlet UILabel *todayLabel;
@property (weak, nonatomic) IBOutlet UILabel *dailyGoalLabel;
@end

@implementation Home

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)awakeFromNib {
    if (![[NSUserDefaults standardUserDefaults] valueForKey:@"dailyGoal"]) {
        self.dailyGoal = DEFAULT_GOAL;
    } else {
        self.dailyGoal = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"dailyGoal"];
    }
    if (![[NSUserDefaults standardUserDefaults] valueForKey:@"today"]) {
        self.today = 0;
    } else {
        self.today = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"today"];
    }
}

- (void)setToday:(int)today {
    _today = today;
    self.todayLabel.text = [NSString stringWithFormat:@"%i", today];
    [[NSUserDefaults standardUserDefaults] setInteger:today forKey:@"today"];
}

- (void)setDailyGoal:(int)dailyGoal {
    _dailyGoal = dailyGoal;
    self.dailyGoalLabel.text = [NSString stringWithFormat:@"Your goal is %iml", _dailyGoal];
}

- (IBAction)drinkCup {
    self.today += 250;
}
- (IBAction)drinkBottle {
    if (![[NSUserDefaults standardUserDefaults] objectForKey:@"travelBottle"]) {
        self.today += 750;
    } else {
        self.today += [[NSUserDefaults standardUserDefaults] integerForKey:@"travelBottle"];
    }
}
- (IBAction)reset:(id)sender {
    self.today = 0;
}

@end
