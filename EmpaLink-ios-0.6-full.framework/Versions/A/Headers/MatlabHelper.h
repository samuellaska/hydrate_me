//
//  MatlabHelper.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 4/23/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MatlabHelper : NSObject
+ (MatlabHelper *)sharedInstance;

- (void) filterIBIMinMax:(float *)x withLenght:(int *)n;
- (int) windowedIBI:(float *)ibi withArrayLenght:(int)n andWindowLength:(int)wl andWindowNumber:(int)wn toNewArray:(float*)newArray;
- (int) polyFilterIBI:(float*)ibi withArrayLength:(int)n toNewArray:(float*)newArray;

-(double) meanFrequencyForIbi:(double*)ibi withLength:(int)n;
//-(void) frequencyBandsForIBI:(double*)ibi withArrayLength:(int)n LF:(double*)LF HF:(double*)HF TP:(double*)TP WBI:(double*)WBI;


@end
