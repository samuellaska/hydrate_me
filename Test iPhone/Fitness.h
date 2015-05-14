//
//  Fitness.h
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol FitnessProtocol <NSObject>

- (void)searchForE3s;

@end

@interface Fitness : UIView

@property (nonatomic, weak) id<FitnessProtocol> delegate;

@end
