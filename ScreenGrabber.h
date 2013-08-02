//
//  ScreenGrabber.h
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ScreenGrabber : NSObject

+(NSImage*)getScreenGrabFromRect:(NSRect)rect;


+(CGImageRef)createScreenShot;

@end
