//
//  ClientAppCommunicatorScreen.h
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#ifndef __MultiComputer_Tester__ClientAppCommunicatorScreen__
#define __MultiComputer_Tester__ClientAppCommunicatorScreen__

#include "gui/GUIView.h"

#include "utility/SocketClasses.h"

namespace GUI {
    struct GUITimer_command;
}

class Socket_Client;
class ClientAppCommunicatorScreen : public GUI::View {
public:
    ClientAppCommunicatorScreen(Socket_Client *cmd_sock, UDP_Socket data_sock);
    ~ClientAppCommunicatorScreen();
    
private:
    
    Socket_Client *cmd_sock;
//    UDP_Socket data_sock;
    
    // Get image from server
    
    void poll_server_for_image();
    
    
    // Send events over the network
    
    
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
    
private:
    GUI::GUITimer_command *poll_image_repeater;
};


#endif /* defined(__MultiComputer_Tester__ClientAppCommunicatorScreen__) */
