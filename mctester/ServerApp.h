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

class ServerApp : public GUI::View {
public:
    ServerApp(const std::string &appname);
    
private:
    
    std::string appname;
    Socket_Server *serv;
    Socket_Server *cmd_sock;
    UDP_Socket data_sock;
    
    
    // Maybe it would be faster to spawn 4 threads and split the image up
    // to parallellize the data transfer?
    
    Socket_Server *sock0;
    Socket_Server *sock1;
    Socket_Server *sock2;
    Socket_Server *sock3;
//    Socket_Server *sock4;
//    Socket_Server *sock5;

    
    
    
    void send_image_to_client();
    
    void poll_client();

    
    // Receive from client and send to watched app:
    
    // Mouse Events. Following three functions all work the same:
    //  Return true if the mouse-event is finished being handled, false otherwise.
    bool receive_mouse_down(DispPoint coord);
    bool receive_mouse_up(DispPoint coord);
    bool receive_mouse_motion(DispPoint coord, DispPoint rel_motion);
    
    //  up == true, down == false.
    bool receive_mouse_scroll_start(bool up_down);
    bool receive_mouse_scroll_stop(bool up_down);
    
    
    
    
    // Key Events. Following two functions all work the same:
    //  Return true if the key-event is finished being handled, false otherwise.
    bool receive_key_down(SDL_keysym key);
    bool receive_key_up(SDL_keysym key);

};

#endif /* defined(__MultiComputer_Tester__ServerApp__) */
