//
//  ViewController.h
//  Test iPhone
//
//  Created by Samuel Laska on 9/12/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DailyGoal.h"

@interface ViewController : UIViewController <UIScrollViewDelegate, DailyGoalUpdatedProtocol>

- (void)updateDailyGoal:(int)goal;
@end

