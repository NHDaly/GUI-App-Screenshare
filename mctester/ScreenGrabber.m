//
//  ScreenGrabber.m
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

// --------------- Necessary for screen grabbing, apparently: ---------------
#pragma mark Basic Profiling Tools
// Set to 1 to enable basic profiling. Profiling information is logged to console.
#ifndef PROFILE_WINDOW_GRAB
#define PROFILE_WINDOW_GRAB 0
#endif

#if PROFILE_WINDOW_GRAB
#define StopwatchStart() AbsoluteTime start = UpTime()
#define Profile(img) CFRelease(CGDataProviderCopyData(CGImageGetDataProvider(img)))
#define StopwatchEnd(caption) do { Duration time = AbsoluteDeltaToDuration(UpTime(), start); double timef = time < 0 ? time / -1000000.0 : time / 1000.0; NSLog(@"%s Time Taken: %f seconds", caption, timef); } while(0)
#else
#define StopwatchStart()
#define Profile(img)
#define StopwatchEnd(caption)
#endif
// ---------------------- End screen grabbing pragma ----------------------


#import "ScreenGrabber.h"

@implementation ScreenGrabber

+(NSImage*)getScreenGrabFromRect:(NSRect)rect
{
    float x = rect.origin.x, y = rect.origin.y;
    float w = rect.size.width, h = rect.size.height;
    
    NSBitmapImageRep *bitmapRep = [[NSBitmapImageRep alloc] initWithCGImage:[self createScreenShot]];
    // Create an NSImage and add the bitmap rep to it...
    NSImage *image = [[NSImage alloc] init];
    [image addRepresentation:bitmapRep];
    [bitmapRep release];
    bitmapRep = nil;
    
    //    NSBitmapImageRep *imgRep = [[image representations] objectAtIndex: 0];
    //    NSData *data = [imgRep representationUsingType: NSPNGFileType properties: nil];
    //    bool success = [data writeToFile: @"screensh.png" atomically: NO];
    
    //Get the source image from image
    NSImage *source = image;
    
    //Init target image
    NSImage *target = [[NSImage alloc]initWithSize:NSMakeSize(w,h)];
    
    //start drawing on target
    [target lockFocus];
    //draw the portion of the source image on target image
    [source drawInRect:NSMakeRect(0,0,w,h)
              fromRect:NSMakeRect(x,y-h,w,h)
             operation:NSCompositeCopy
              fraction:1.0];
    //end drawing
    [target unlockFocus];
    
    [source release];
    
    return target;    
}

+(CGImageRef)createScreenShot
{
    // This just invokes the API as you would if you wanted to grab a screen shot. The equivalent using the UI would be to
    // enable all windows, turn off "Fit Image Tightly", and then select all windows in the list.
    StopwatchStart();
    CGImageRef screenShot = CGWindowListCreateImage(CGRectInfinite, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);
    Profile(screenShot);
    StopwatchEnd("Screenshot");
    
    return screenShot;
}

@end
