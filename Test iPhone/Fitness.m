//
//  Fitness.m
//  HydrateMe
//
//  Created by Samuel Laska on 9/14/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import "Fitness.h"

@interface Fitness ()
@end

@implementation Fitness
- (IBAction)seachPressed:(id)sender {
    [self.delegate searchForE3s];
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
