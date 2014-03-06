//
//  ServerApp.h
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#ifndef __MultiComputer_Tester__ServerApp__
#define __MultiComputer_Tester__ServerApp__

#include "gui/GUIView.h"
#include "gui/GUITextViews.h"
#include "utility/SocketClasses.h"

#include <string>

class Socket_Server;
namespace GUI {
    class GUITimer_command;
}
class ServerApp : public GUI::View {
public:
    ServerApp(const std::string &appname);
    ~ServerApp();
    
protected:
    
    std::string appname;
    Socket_Server *serv;
    Socket_Server *cmd_sock;
//    UDP_Socket data_sock;
    

    
    
    virtual void send_image_to_client() = 0; // OS dependent
    
    // Receive from client and send to watched app:
    
    // Mouse Events. Following three functions all work the same:
    //  Return true if the mouse-event is finished being handled, false otherwise.
    virtual bool receive_mouse_down(DispPoint coord) = 0;
    virtual bool receive_mouse_up(DispPoint coord) = 0;
    virtual bool receive_mouse_motion(DispPoint coord, DispPoint rel_motion) = 0;
    
    //  up == true, down == false.
    virtual bool receive_mouse_scroll_start(bool up_down) = 0;
    virtual bool receive_mouse_scroll_stop(bool up_down) = 0;
    
    
    // Key Events. Following two functions all work the same:
    //  Return true if the key-event is finished being handled, false otherwise.
    virtual bool receive_key_down(SDL_keysym key) = 0;
    virtual bool receive_key_up(SDL_keysym key) = 0;

private:
    
    // template method to poll for, receive, and handle events from client.
    void poll_client();
    
    GUI::GUITimer_command *send_image_repeater;
    GUI::GUITimer_command *poll_client_repeater;
};

#endif /* defined(__MultiComputer_Tester__ServerApp__) */
