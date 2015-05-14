//
//  ViewController.m
//  Test iPhone
//
//  Created by Samuel Laska on 9/12/14.
//  Copyright (c) 2014 SamuelLaska. All rights reserved.
//

#import "ViewController.h"
#import <EmpaLink-ios-0.6-full/EmpaticaAPI-0.6.h>
#import "SOMotionDetector.h"
#import "Home.h"
#import "Fitness.h"
#import "Bottle.h"
#import "ESTBeacon.h"
#import "ESTBeaconManager.h"
#import "SelectBeaconVC.h"

#define kFilteringFactor    0.1
float accelZ;
int spikeZCount = 0;

#define SHAKE_MIN 0.13f;
#define SHAKE_MAX 0.25f;

@interface ViewController () <EmpaticaDelegate, EmpaticaDeviceDelegate, SOMotionDetectorDelegate, ESTBeaconManagerDelegate, BottleBeaconProtokol, FitnessProtocol>
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UILabel *gsrLabel;
@property (weak, nonatomic) IBOutlet UILabel *bvpLabel;
@property (weak, nonatomic) IBOutlet UILabel *tmpLabel;
@property (weak, nonatomic) IBOutlet UILabel *accLabel;
@property (weak, nonatomic) IBOutlet UILabel *ibiLabel;
@property (weak, nonatomic) IBOutlet UILabel *btrLabel;
@property (weak, nonatomic) IBOutlet UILabel *waterLabel;

@property float latestGSR;
@property float latestBVP;
@property float latestTemp;
@property char latestX;
@property char latestY;
@property char latestZ;
@property float latestIBI;
@property float latestBattery;
@property int shakeNumber;

@property BOOL histeresisExcited;
@property CMAcceleration lastAcceleration;

@property double lastShakeTime;
@property double lastKnockTime;

@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (weak, nonatomic) IBOutlet UIPageControl *pageControl;
@property (weak, nonatomic) Home *homeView;
@property (weak, nonatomic) DailyGoal *dailyGoalView;
@property (weak, nonatomic) Bottle *bottleView;
@property (weak, nonatomic) Fitness *fitnessView;

@property (nonatomic, strong) ESTBeacon         *beacon;
@property (nonatomic, strong) ESTBeaconManager  *beaconManager;
@property (nonatomic, strong) ESTBeaconRegion   *beaconRegion;
@property (weak, nonatomic) IBOutlet UIButton *beaconIcon;
@property (weak, nonatomic) IBOutlet UIButton *empaticaIcon;

@end

@implementation ViewController
- (IBAction)scrollToFitness:(id)sender {
    [self.scrollView setContentOffset:
     CGPointMake(320*4, 0) animated:YES];
}
- (IBAction)scrollToBottle:(id)sender {
    [self.scrollView setContentOffset:
     CGPointMake(320*3, 0) animated:YES];
}
            
- (void)viewDidLoad {
    [super viewDidLoad];
    [self setNeedsStatusBarAppearanceUpdate];
    [NSTimer scheduledTimerWithTimeInterval:2.0
                                     target:self
                                   selector:@selector(globalUpdate:)
                                   userInfo:nil
                                    repeats:YES];
    [SOMotionDetector sharedInstance].delegate = self;
    [[SOMotionDetector sharedInstance] startDetection];
    
    self.scrollView.delegate = self;
    self.scrollView.contentSize = CGSizeMake(320 * 5, 568);
    
    self.homeView = [[[NSBundle mainBundle]
                                    loadNibNamed:@"Home"
                                    owner:self options:nil]
                                   firstObject];
    [self.scrollView addSubview:self.homeView];
    
    self.dailyGoalView = [[[NSBundle mainBundle]
                     loadNibNamed:@"DailyGoal"
                     owner:self options:nil]
                    firstObject];
    self.dailyGoalView.frame = CGRectMake(320, 0, 320, 568);
    self.dailyGoalView.delegate = self;
    [self.scrollView addSubview:self.dailyGoalView];
    
    UIView *notifications = [[[NSBundle mainBundle]
                           loadNibNamed:@"Notifications"
                           owner:self options:nil]
                          firstObject];
    notifications.frame = CGRectMake(320*2, 0, 320, 568);
    [self.scrollView addSubview:notifications];
    
    self.bottleView = [[[NSBundle mainBundle]
                           loadNibNamed:@"Bottle"
                           owner:self options:nil]
                          firstObject];
    self.bottleView.frame = CGRectMake(320*3, 0, 320, 568);
    self.bottleView.delegate = self;
    [self.scrollView addSubview:self.bottleView];
    
    self.fitnessView = [[[NSBundle mainBundle]
                        loadNibNamed:@"Fitness"
                        owner:self options:nil]
                       firstObject];
    self.fitnessView.frame = CGRectMake(320*4, 0, 320, 568);
    self.fitnessView.delegate = self;
    [self.scrollView addSubview:self.fitnessView];
}

- (void)updateDailyGoal:(int)goal {
    self.homeView.dailyGoal = goal;
    
}

- (void)scrollViewDidScroll:(UIScrollView *)sender {
    // Update the page when more than 50% of the previous/next page is visible
    CGFloat pageWidth = self.scrollView.frame.size.width;
    int page = floor((self.scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    self.pageControl.currentPage = page;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self globalUpdate:nil];
}

- (void)motionDetector:(SOMotionDetector *)motionDetector accelerationChanged:(CMAcceleration)acceleration
{
    if (self.lastAcceleration.x || self.lastAcceleration.y || self.lastAcceleration.z) {
        if (!self.histeresisExcited && L0AccelerationIsShaking(self.lastAcceleration, acceleration, 0.7)) {
            float timeframe = [NSDate timeIntervalSinceReferenceDate] - self.lastShakeTime;
            NSLog(@"%f", timeframe);
            if (timeframe < 0.26 && timeframe > 0.10 && [NSDate timeIntervalSinceReferenceDate] - self.lastKnockTime > 1) {
                self.lastKnockTime = [NSDate timeIntervalSinceReferenceDate];
                self.homeView.today += 250;
                int goal = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"dailyGoal"];
                
                UILocalNotification* localNotification = [[UILocalNotification alloc] init];
                localNotification.fireDate = [NSDate dateWithTimeIntervalSinceNow:0];
                if (goal > self.homeView.today) {
                    localNotification.alertBody = [NSString stringWithFormat:@"Yes! Another cup of water, \nonly %iml remaining", goal-self.homeView.today];
                    localNotification.soundName = @"cup.wav";
                } else {
                    localNotification.alertBody = @"Daily goal was finished :), \nyour body loves you for that :)";
                    localNotification.soundName = @"bell.wav";
                }
                
                localNotification.timeZone = [NSTimeZone defaultTimeZone];
                [[UIApplication sharedApplication] scheduleLocalNotification:localNotification];

            }
            
            self.histeresisExcited = YES;
            self.lastShakeTime = [NSDate timeIntervalSinceReferenceDate];
        }
        else if (self.histeresisExcited && !L0AccelerationIsShaking(self.lastAcceleration, acceleration, 0.1)) {
            self.histeresisExcited = NO;
        }
        
    }
    self.lastAcceleration = acceleration;

}

static BOOL L0AccelerationIsShaking(CMAcceleration last, CMAcceleration current, double threshold) {
    double
    deltaX = fabs(last.x - current.x),
    deltaY = fabs(last.y - current.y),
    deltaZ = fabs(last.z - current.z);
    
    return
    (deltaZ > threshold && deltaY < threshold && deltaX < threshold);
//    return
//    (deltaX > threshold && deltaY > threshold) ||
//    (deltaX > threshold && deltaZ > threshold) ||
//    (deltaY > threshold && deltaZ > threshold);
}

- (void)globalUpdate:(NSTimer *)timer {
    self.gsrLabel.text = [NSString stringWithFormat:@"GSR: %f", self.latestGSR];
    self.bvpLabel.text = [NSString stringWithFormat:@"BVP: %f", self.latestBVP];
    self.tmpLabel.text = [NSString stringWithFormat:@"Temp: %f", self.latestTemp];
    self.accLabel.text = [NSString stringWithFormat:@"ACC: %1i,%2i,%3i", self.latestX, self.latestY, self.latestY];
    self.ibiLabel.text = [NSString stringWithFormat:@"IBI: %f", self.latestIBI];
    self.btrLabel.text = [NSString stringWithFormat:@"Battery: %f", self.latestBattery];    
    self.waterLabel.text = [NSString stringWithFormat:@"%i", self.shakeNumber];
}

- (void)searchForE3s {
    [self ScanForDevicesButtonPressed:nil];
}

- (IBAction)ScanForDevicesButtonPressed:(id)sender {
    [EmpaticaAPI discoverDevicesWithDelegate:self];
}

// UGLY FUNCTIONS

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)didDiscoverDevices:(NSArray *)devices {
    if (devices.count > 0) {
        // Connecting to first available device
        EmpaticaDeviceManager *firstDevice = [devices objectAtIndex:0];
        [firstDevice connectWithDeviceDelegate:self];
        [self.empaticaIcon setImage:[UIImage imageNamed:@"empaticaOn"] forState:UIControlStateNormal];
    } else {
        NSLog(@"No device found in range");
    }
}

- (void)didReceiveGSR:(float)gsr withTimestamp:(double)timestamp fromDevice:(EmpaticaDeviceManager *)device {
    self.latestGSR = gsr;
}

- (void)didReceiveBVP:(float)bvp withTimestamp:(double)timestamp fromDevice:(EmpaticaDeviceManager *)device {
    self.latestBVP = bvp;
}
- (void)didReceiveTemperature:(float)temp withTimestamp:(double)timestamp fromDevice:(EmpaticaDeviceManager *)device {
    self.latestTemp = temp;
    
}
- (void)didReceiveAccelerationX:(char)x y:(char)y z:(char)z withTimestamp:(double)timestamp fromDevice:(EmpaticaDeviceManager *)device {
    self.latestX = x;
    self.latestY = y;
    self.latestZ = z;
}
- (void)didReceiveIBI:(float)ibi withTimestamp:(double)timestamp fromDevice:(EmpaticaDeviceManager *)device {
    self.latestIBI = ibi;
    
}
- (void)didReceiveBatteryLevel:(float)level withTimestamp:(double)timestamp fromDevice:(EmpaticaDeviceManager *)device {
    self.latestBattery = level;
}

- (void)didUpdateBLEStatus:(BLEStatus)status {
    return;
}

- (void)didUpdateDeviceStatus:(DeviceStatus)status forDevice:(EmpaticaDeviceManager *)device {
    switch (status) {
        case kDeviceStatusDisconnected:
        case kDeviceStatusDisconnecting:
            self.statusLabel.textColor = [UIColor redColor];
            self.statusLabel.text = @"Disconnected";
            break;
        case kDeviceStatusConnected:
            self.statusLabel.textColor = [UIColor greenColor];
            self.statusLabel.text = @"Connected";
            break;
        case kDeviceStatusConnecting:
            NSLog(@"kBLEStatusScanning");
            self.statusLabel.textColor = [UIColor orangeColor];
            self.statusLabel.text = @"Scanning";
            break;
        case kDeviceStatusFailedToConnect:
        default:
            NSLog(@"kDeviceStatusFailedToConnect");
            break;
    }
}

-(UIStatusBarStyle)preferredStatusBarStyle{
    return UIStatusBarStyleLightContent;
}

- (IBAction)unwindToBaseViewController:(UIStoryboardSegue *)unwindSegue
{
    SelectBeaconVC *sbvc = unwindSegue.sourceViewController;
    if ([sbvc.selectedBeacon isKindOfClass:[ESTBeacon class]]) {
        NSLog(@"Beacon");
        self.beacon = (ESTBeacon *)sbvc.selectedBeacon;
        [self startLookoutForBeacon];
        [self.bottleView updateBeaconData:self.beacon];
        [self.beaconIcon setImage:[UIImage imageNamed:@"bleOn"] forState:UIControlStateNormal];
    }
}

- (void)startLookoutForBeacon {

    self.beaconManager = [[ESTBeaconManager alloc] init];
    self.beaconManager.delegate = self;
    
    CLLocationManager *locationManager = [[CLLocationManager alloc] init];
    for (CLRegion *region in locationManager.monitoredRegions) {
        [locationManager stopMonitoringForRegion:region];
    }

    self.beaconRegion = [[ESTBeaconRegion alloc] initWithProximityUUID:self.beacon.proximityUUID
                                                             major:[self.beacon.major unsignedIntValue]
                                                             minor:[self.beacon.minor unsignedIntValue]
                                                        identifier:@"HydrateBeaconRegion"];
    self.beaconRegion.notifyOnEntry = YES;
    self.beaconRegion.notifyOnExit = YES;

    [self.beaconManager startMonitoringForRegion:self.beaconRegion];
}

- (void)performLookForBeacons {
    [self performSegueWithIdentifier:@"selectBeacon" sender:self];
}

- (void)beaconManager:(ESTBeaconManager *)manager didEnterRegion:(ESTBeaconRegion *)region
{
    UILocalNotification *notification = [UILocalNotification new];
    notification.alertBody = @"Enter region notification";
    
    [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
}

- (void)beaconManager:(ESTBeaconManager *)manager didExitRegion:(ESTBeaconRegion *)region
{
    UILocalNotification *notification = [UILocalNotification new];
    notification.alertBody = @"Enter region notification";
    [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
}

@end
