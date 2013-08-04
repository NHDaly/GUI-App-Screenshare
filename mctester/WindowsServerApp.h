//
//  MacServerApp..h
//  MultiComputer Tester
//
//  Created by Nathan Daly on 8/3/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#ifndef __MultiComputer_Tester__WindowsServerApp___
#define __MultiComputer_Tester__WindowsServerApp___

#include "ServerApp.h"

class WindowsServerApp : public ServerApp {
public:
    WindowsServerApp(const std::string &appname) : ServerApp(appname) { }

private:
    
    virtual void send_image_to_client(); // OS dependent
    
    /*
    // Receive from client and send to watched app:
    
    // Mouse Events. Following three functions all work the same:
    //  Return true if the mouse-event is finished being handled, false otherwise.
    virtual bool receive_mouse_down(DispPoint coord);
    virtual bool receive_mouse_up(DispPoint coord);
    virtual bool receive_mouse_motion(DispPoint coord, DispPoint rel_motion);
    
    //  up == true, down == false.
    virtual bool receive_mouse_scroll_start(bool up_down);
    virtual bool receive_mouse_scroll_stop(bool up_down);
    
    
    // Key Events. Following two functions all work the same:
    //  Return true if the key-event is finished being handled, false otherwise.
    virtual bool receive_key_down(SDL_keysym key);
    virtual bool receive_key_up(SDL_keysym key);
     */

};

#endif /* defined(__MultiComputer_Tester__WindowsServerApp___) */
