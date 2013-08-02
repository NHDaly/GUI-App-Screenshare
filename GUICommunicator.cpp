//
//  GUICommunicator.cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "GUICommunicator.h"
#include "gui/GUIImage.h"

#include "AppleScriptLink.h"

#include "utility/SocketClasses.h"

#include <iostream>
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include <Carbon/Carbon.h>

using namespace GUI;
using namespace std;

GUICommunicator::GUICommunicator(GUIImage image, const string &appname_)
:ImageView(image), sock(0), appname(appname_)
{
    capture_focus();
}

// Mouse Events. Following three functions all work the same:
//  Return true if the mouse-event is finished being handled, false otherwise.
bool GUICommunicator::handle_mouse_down(DispPoint coord) {
    
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
bool GUICommunicator::handle_mouse_up(DispPoint coord) {
    
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
bool GUICommunicator::handle_mouse_motion(DispPoint coord, DispPoint rel_motion) {
    
    int appX, appY;
    getWindowPosition(appname, appX, appY);

//    CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp,
//                                               CGPointMake(appX + coord.x, appY + coord.y),
//                                               kCGMouseButtonLeft
//                                               );
//    CGEventPost(kCGHIDEventTap, event);
//
//    // Release the events
//    CFRelease(event);

    return true;
}

//  up == true, down == false.
bool GUICommunicator::handle_mouse_scroll_start(bool up_down) {
    
    return true;
}
bool GUICommunicator::handle_mouse_scroll_stop(bool up_down) {
    
    return true;
}




// Key Events. Following two functions all work the same:
//  Return true if the key-event is finished being handled, false otherwise.
bool GUICommunicator::handle_key_down(SDL_keysym key) {
    
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
bool GUICommunicator::GUICommunicator::handle_key_up(SDL_keysym key) {
    
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
