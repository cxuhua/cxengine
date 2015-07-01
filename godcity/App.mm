//
//  AppDelegate.m
//  cxEngine2D
//
//  Created by xuhua on 5/20/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#include <engine/cxEngine.h>
#import "App.h"
#include "GodCity.h"

using namespace cxengine;

@implementation IOSGate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //must init engine class
    cxEngine::Init(GodCity::Alloc());
    
    return [super application:application didFinishLaunchingWithOptions:launchOptions];
}
@end

@implementation IOSApp


@end


