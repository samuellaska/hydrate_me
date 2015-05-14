//
//  FFTAccelerate2.h
//  FFTAccelerate
//
//  Created by Maurizio Garbarino on 12/10/12.
//
//

#import <Foundation/Foundation.h>
#include <Accelerate/Accelerate.h>

#define HR_VARIATION 0.45
#define VERBOSE 0
#define SMOOTH_EVERY 8 //

@interface FFTAccelerate : NSObject

@property (nonatomic, assign) int counter;
@property (nonatomic, assign) int spectrumCounter;
@property (nonatomic, assign) float *hrSpectrum;

//DebugnumSamples
@property (nonatomic, assign) float *accX;
@property (nonatomic, assign) float *accY;
@property (nonatomic, assign) float *accZ;
@property (nonatomic, assign) float *accSum;
@property (nonatomic, assign) float *magnitude;
@property (nonatomic, strong) NSString *currentStatus;

@property (nonatomic, assign)  FFTSetup fftSetup;
@property (nonatomic, assign)  COMPLEX_SPLIT A;

-(void) FFTRealFromTime:(float*)time toFrequency:(float*)frequency withNumberOfSamples:(int) numSamples;
-(void) FFTComplexFromTime:(float*)time toFrequency:(DSPComplex*)frequency withNumberOfSamples:(int) numSamples;
-(void) smoothSpectrum:(float*)s withLength:(int)l andWindowsArray:(int*)windowsArray ofSize:(int)windowsArraySize andIndexToRemove:(int)indexToRemove toArray:(float*)pp;
-(float) getHeartFrequency:(float*)x arraySize:(int)n sampleRate:(float)sampleRate previousHeartFrequency:(float)hrPrevious;
-(float) getHeartFrequency:(float*)x arraySize:(int)n sampleRate:(float)sampleRate;
-(float) hrFromBvp:(float*)bvp size:(int)n discardingFirst:(int)tipDiscarded discardingLast:(int)tailDiscarded sampleFrequency:(float)fs  previousHeartFrequency:(float)hrPrevious;
-(id) initWithNumberOfSamples:(int)numSamples;


-(NSString *)addAccSampleX:(int)x Y:(int)y Z:(int)z;


@end
