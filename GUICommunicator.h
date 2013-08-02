//
//  GUICommunicator.h
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#ifndef __MultiComputer_Tester__GUICommunicator__
#define __MultiComputer_Tester__GUICommunicator__

#include "gui/GUIImageView.h"

class TCPSocket;

class GUICommunicator : public GUI::ImageView {
public:
    GUICommunicator(GUIImage image, const std::string &appname);
    
    
private:
    
    // Mouse Events. Following three functions all work the same:
    //  Return true if the mouse-event is finished being handled, false otherwise.
    virtual bool handle_mouse_down(DispPoint coord);
    virtual bool handle_mouse_up(DispPoint coord);
    virtual bool handle_mouse_motion(DispPoint coord, DispPoint rel_motion);
    
    //  up == true, down == false.
    virtual bool handle_mouse_scroll_start(bool up_down);
    virtual bool handle_mouse_scroll_stop(bool up_down);
    
    
    
    
    // Key Events. Following two functions all work the same:
    //  Return true if the key-event is finished being handled, false otherwise.
    virtual bool handle_key_down(SDL_keysym key);
    virtual bool handle_key_up(SDL_keysym key);

    std::string appname;
    TCPSocket *sock;
};


#endif /* defined(__MultiComputer_Tester__GUICommunicator__) */
