//
//  ServerApp.cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "ServerApp.h"
#include "sharedConstants.h"
#include "AppleScriptLink.h"

#include "gui/GUIApp.h"
#include "gui/GUIWindow.h"
#include "utility/SocketClasses.h"

#import "ScreenGrabber.h"


#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <Carbon/Carbon.h>

#include <tr1/functional>

using namespace std;
using namespace GUI;
using namespace std::tr1;


ServerApp::ServerApp(const string &appname_)
:View(400,200), serv(new Socket_Server(port_num_k)),
cmd_sock(0), data_sock(port_num_k+1), appname(appname_)
{
    data_sock.bind();
    
    fill_with_color(Gray_Color);

    serv->listen();
    cmd_sock = serv->accept();

    
    // Maybe it would be faster to spawn 4 threads and split the image up
    // to parallellize the data transfer?
    
    //Open all 4 data sockets
//    sock0 = serv->accept();
//    sock1 = serv->accept();
//    sock2 = serv->accept();
//    sock3 = serv->accept();

    
    const int new_w = 200, new_h = 100;
    resize(new_w,new_h);
    App::get()->get_window()->resize(new_w,new_h);

    
    
    App::get()->repeat_on_timer(bind(&ServerApp::send_image_to_client, this), 0);
    App::get()->repeat_on_timer(bind(&ServerApp::poll_client, this), 0);
}


void ServerApp::send_image_to_client()
{
    int x, y;
    int w, h;
    
    getWindowPosition(appname, x,y);
    getWindowSize(appname, w,h);
    
    y = [[[NSScreen screens] objectAtIndex:0] frame].size.height - y;
    
    
    NSImage *img = [ScreenGrabber getScreenGrabFromRect:NSMakeRect(x, y, w, h)];
    
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

void ServerApp::poll_client()
{
    
    Uint8 eventType = 0; // get event from client
    
    short revents;
    if (cmd_sock->poll(POLLIN, revents, 1)) {
        
        cmd_sock->recv_into(&eventType);
        
        switch (eventType) {
                
            case SDL_MOUSEBUTTONDOWN: {
                
                DispPoint coord; // receive from client
                cmd_sock->recv_into(&coord);
                
                coord.x = ntohl(coord.x);
                coord.y = ntohl(coord.y);
                
                receive_mouse_down(coord);
                
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                
                DispPoint coord; // receive from client
                cmd_sock->recv_into(&coord);
                
                coord.x = ntohl(coord.x);
                coord.y = ntohl(coord.y);

                receive_mouse_up(coord);
                
                break;
            }
            case SDL_MOUSEMOTION: {
                
                DispPoint coord, rel; // receive from client
                cmd_sock->recv_into(&coord);
                cmd_sock->recv_into(&rel);
         
                coord.x = ntohl(coord.x);
                coord.y = ntohl(coord.y);

                rel.x = ntohl(rel.x);
                rel.y = ntohl(rel.y);

                receive_mouse_motion(coord, rel);
                
                break;
            }
            case GUI_MOUSESCROLL_START: {
                
                bool up_down; // receive from client
                cmd_sock->recv_into(&up_down);
                
                receive_mouse_scroll_start(up_down);
                
                break;
            }
            case GUI_MOUSESCROLL_STOP: {
                
                bool up_down; // receive from client
                cmd_sock->recv_into(&up_down);
                
                receive_mouse_scroll_stop(up_down);
                
                break;
            }
                
                
            case SDL_KEYDOWN: {
                
                SDL_keysym key; // receive from client
                cmd_sock->recv_into(&key);
                
                receive_key_down(key);
                
                break;
            }
            case SDL_KEYUP: {
                
                SDL_keysym key; // receive from client
                cmd_sock->recv_into(&key);
                
                receive_key_up(key);
                
                break;
            }
                
            default:
                break;
                
        }
    }
    
}

// Mouse Events. Following three functions all work the same:
//  Return true if the mouse-event is finished being handled, false otherwise.
bool ServerApp::receive_mouse_down(DispPoint coord) {
    
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
bool ServerApp::receive_mouse_up(DispPoint coord) {
    
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
bool ServerApp::receive_mouse_motion(DispPoint coord, DispPoint rel_motion) {
    
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
bool ServerApp::receive_mouse_scroll_start(bool up_down) {
    
    return true;
}
bool ServerApp::receive_mouse_scroll_stop(bool up_down) {
    
    return true;
}




// Key Events. Following two functions all work the same:
//  Return true if the key-event is finished being handled, false otherwise.
bool ServerApp::receive_key_down(SDL_keysym key) {
    
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
bool ServerApp::ServerApp::receive_key_up(SDL_keysym key) {
    
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

