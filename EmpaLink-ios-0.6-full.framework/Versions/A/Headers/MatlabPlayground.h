//
//  MatlabPlayground.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 4/17/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MatlabPlayground : NSObject
+ (MatlabPlayground *)sharedInstance;

- (void) filterIBIMinMax:(float *)x withLenght:(int *)n;
- (int) windowedIBI:(float *)ibi withArrayLenght:(int)n andWindowLength:(int)wl andWindowNumber:(int)wn toNewArray:(float*)newArray;
- (int) polyFilterIBI:(float*)ibi withArrayLength:(int)n toNewArray:(float*)newArray;

-(float) meanFrequencyForIbi:(float*)ibi withLength:(int)n;
@end
