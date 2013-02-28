#include "AccelerationManagerImplCocoaTouch.h"

using namespace ci;

@interface CocoaProxy : NSObject <UIAccelerometerDelegate>
{
    AccelerationManagerImplCocoaTouch *mTarget;
}

- (id) initWithTarget:(AccelerationManagerImplCocoaTouch*)target;

@end

@implementation CocoaProxy

- (id) initWithTarget:(AccelerationManagerImplCocoaTouch*)target
{
    if (self = [super init])
    {
        mTarget = target;
        return self;
    }
    
    return nil;
}

- (void) accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration
{
    mTarget->accelerated(Vec3f(acceleration.x, acceleration.y, acceleration.z));
}

@end

AccelerationManagerImplCocoaTouch::AccelerationManagerImplCocoaTouch()
:
mDelegate(NULL),
mLastRawAccel(ci::Vec3f::zero())
{
    mProxy = [[CocoaProxy alloc] initWithTarget:this];
}

AccelerationManagerImplCocoaTouch::~AccelerationManagerImplCocoaTouch()
{
    [mProxy release];
}

void AccelerationManagerImplCocoaTouch::enable(AccelerationDelegate *delegate, float updateFrequency)
{
    mDelegate = delegate;
    
    if (updateFrequency <= 0)
    {
        updateFrequency = 30;
    }
    
    [[UIAccelerometer sharedAccelerometer] setUpdateInterval:(1 / updateFrequency)];
    [[UIAccelerometer sharedAccelerometer] setDelegate:mProxy];
}

void AccelerationManagerImplCocoaTouch::disable()
{
    [[UIAccelerometer sharedAccelerometer] setDelegate:nil];
}

void AccelerationManagerImplCocoaTouch::accelerated(const Vec3f &acceleration)
{
    if (mDelegate)
    {
        mDelegate->accelerated(AccelEvent(acceleration, mLastRawAccel));
    }
    
    mLastRawAccel = acceleration;
}