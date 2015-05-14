//
//  DailyGoal.h
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol DailyGoalUpdatedProtocol <NSObject>

- (void)updateDailyGoal:(int)goal;

@end

@interface DailyGoal : UIView

@property (nonatomic, weak) id<DailyGoalUpdatedProtocol> delegate;

@end
