//
//  MacServerApp..cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 8/3/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "MacServerApp.h"

#import "ScreenGrabber.h"
#include "AppleScriptLink.h"

#include "utility/SocketClasses.h"

#include <iostream>
using namespace std;

void MacServerApp::send_image_to_client()
{
    int x, y;
    int w, h;
    
    getWindowPosition(appname, x,y);
    getWindowSize(appname, w,h);
    
    y = [[[NSScreen screens] objectAtIndex:0] frame].size.height - y;
    
    
    NSImage *img = [ScreenGrabber getScreenGrabFromRect:NSMakeRect(x, y, w, h)];
    
    if (img == nil || img == 0 || [img size].height == 0 || [img size].width == 0) {
        NSLog(@"Image has 0 size!");
        return;
    }
    // SAVE IMAGE
    //create a NSBitmapImageRep
    NSBitmapImageRep *bmpImageRep = [[NSBitmapImageRep alloc]initWithData:[img TIFFRepresentation]];
    //add the NSBitmapImage to the representation list of the target
    [img addRepresentation:bmpImageRep];
    
    //get the data from the representation
    NSData *data = [bmpImageRep representationUsingType: NSJPEGFileType
                                             properties: [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:0.0f]
                                                                                     forKey:@"NSImageCompressionFactor"]];
    
    //    NSString *path = [NSString stringWithFormat:@"%s/screensh.bmp", getResourcePath()];
    //
    //    NSLog(@"path: %@", path);
    //
    //    //write the data to a file
    //    bool success = [data writeToFile: path
    //                          atomically: NO];
    //
    cout << (int32_t)[data length] << endl;
    
    // SEND TO CLIENT
    //    data_sock.send_value((int32_t)[data length]);
    //    data_sock.send_to(string((char*)[data bytes], [data length]));
    cmd_sock->send_value((int32_t)[data length]);
    cmd_sock->send(string((char*)[data bytes], [data length]));
    
    
}


// Mouse Events. Following three functions all work the same:
//  Return true if the mouse-event is finished being handled, false otherwise.
bool MacServerApp::receive_mouse_down(DispPoint coord) {
    
    int appX, appY;
    getWindowPosition(appname, appX, appY);
    
    // Left button down at 250x250
    CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown,
                                               CGPointMake(appX + coord.x, appY + coord.y),
                                               kCGMouseButtonLeft
                                               );
    
    CGEventPost(kCGHIDEventTap, event);
    
    // Release the events
    CFRelease(event);
    
    return true;
}
bool MacServerApp::receive_mouse_up(DispPoint coord) {
    
    int appX, appY;
    getWindowPosition(appname, appX, appY);
    
    // Left button up at 250x250
    CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp,
                                               CGPointMake(appX + coord.x, appY + coord.y),
                                               kCGMouseButtonLeft
                                               );
    CGEventPost(kCGHIDEventTap, event);
    
    // Release the events
    CFRelease(event);
    
    
    return true;
}
bool MacServerApp::receive_mouse_motion(DispPoint coord, DispPoint rel_motion) {
    
    int appX, appY;
    getWindowPosition(appname, appX, appY);
    
    CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp,
                                               CGPointMake(appX + coord.x, appY + coord.y),
                                               kCGMouseButtonLeft
                                               );
    CGEventPost(kCGHIDEventTap, event);
    
    // Release the events
    CFRelease(event);
    
    return true;
}

//  up == true, down == false.
bool MacServerApp::receive_mouse_scroll_start(bool up_down) {
    
    return true;
}
bool MacServerApp::receive_mouse_scroll_stop(bool up_down) {
    
    return true;
}




// Key Events. Following two functions all work the same:
//  Return true if the key-event is finished being handled, false otherwise.
bool MacServerApp::receive_key_down(SDL_keysym key) {
    
    cout << "SDLKey: " << key.sym << endl;
    cout << "hardware key: " << key.scancode << endl;
    
    CGEventRef event = CGEventCreateKeyboardEvent(NULL,
                                                  (CGKeyCode) key.scancode, // mac key
                                                  true); // down
    
    CGEventPost(kCGHIDEventTap, event);
    
    // Release the events
    CFRelease(event);
    
    return true;
}

bool MacServerApp::receive_key_up(SDL_keysym key) {
    
    cout << "SDLKey: " << (int)key.sym << endl;
    cout << "hardware key: " << (int)key.scancode << endl;
    
    CGEventRef event = CGEventCreateKeyboardEvent(NULL,
                                                  (CGKeyCode) key.scancode, // mac key
                                                  false); // up
    
    CGEventPost(kCGHIDEventTap, event);
    
    // Release the events
    CFRelease(event);
    
    return true;
}


