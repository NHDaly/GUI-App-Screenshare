//
//  ClientAppCommunicatorScreen.cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "ClientAppCommunicatorScreen.h"

#include "sharedConstants.h"

#include "utility/SocketClasses.h"

#include "gui/GUIApp.h"
#include "gui/GUIWindow.h"
#include "Compatibility.h"

#include TR1_FUNCTIONAL_H
#include <iostream>
using namespace GUI;
using namespace std;
using namespace std::tr1;


//ClientAppCommunicatorScreen::ClientAppCommunicatorScreen(Socket_Client *sock_)
ClientAppCommunicatorScreen::ClientAppCommunicatorScreen(Socket_Client *cmd_sock_, UDP_Socket data_sock_)
:View(1,1), cmd_sock(cmd_sock_)
//, data_sock(data_sock_)
{
    capture_focus();
    
    App::get()->repeat_on_timer(bind(&ClientAppCommunicatorScreen::poll_server_for_image,
                                     this),
                                0);
}


void ClientAppCommunicatorScreen::poll_server_for_image() {
    
    // Read image from socket
    int32_t img_buf_size;
    cmd_sock->recv_into(&img_buf_size);
//    data_sock.recv_into(&img_buf_size);
    cout << img_buf_size << endl;
    
    string buffer = cmd_sock->recv_all(img_buf_size);
//    string buffer = data_sock.recv_from(img_buf_size);

    // Create SDL_surface from image
    void *data = (void*)buffer.c_str();
    
//    SDL_Surface *surface = SDL_LoadBMP_RW(SDL_RWFromMem(data, img_buf_size), 1);
    SDL_RWops * data_rw_op = SDL_RWFromMem(data, img_buf_size);
    SDL_Surface *surface = IMG_LoadJPG_RW(data_rw_op);
    SDL_FreeRW(data_rw_op);


    // Create GUIImage and draw onto (and resize) window
    GUIImage image(surface);
    
    int new_w = image.getw();
    int new_h = image.geth();
    
    if (new_w != get_w() || new_h != get_h()) {
        resize(new_w, new_h);
        
        App::get()->get_window()->resize(new_w, new_h);
    }
    draw_onto_self(image, DispPoint());

}



// Mouse Events. Following three functions all work the same:
//  Return true if the mouse-event is finished being handled, false otherwise.
bool ClientAppCommunicatorScreen::handle_mouse_down(DispPoint coord) {
    
    // send mouse down
    cmd_sock->send_value(SDL_MOUSEBUTTONDOWN);
    
    // send coord
    cmd_sock->send_value(coord);
    
    return true;
}
bool ClientAppCommunicatorScreen::handle_mouse_up(DispPoint coord) {
    
    // send mouse down
    cmd_sock->send_value(SDL_MOUSEBUTTONUP);
    
    // send coord
    cmd_sock->send_value(coord);

    return true;
}
bool ClientAppCommunicatorScreen::handle_mouse_motion(DispPoint coord, DispPoint rel_motion) {
    
//    // send mouse down
//    cmd_sock->send_value(SDL_MOUSEMOTION);
//    
//    // send coord
//    cmd_sock->send_value(coord);
//
//    cmd_sock->send_value(rel_motion);

    return true;
}

//  up == true, down == false.
bool ClientAppCommunicatorScreen::handle_mouse_scroll_start(bool up_down) {
    
    // send mouse down
    cmd_sock->send_value(GUI_MOUSESCROLL_START);
    
    // send coord
    cmd_sock->send_value(up_down);

    return true;
}
bool ClientAppCommunicatorScreen::handle_mouse_scroll_stop(bool up_down) {
    
    // send mouse down
    cmd_sock->send_value(GUI_MOUSESCROLL_STOP);
    
    // send coord
    cmd_sock->send_value(up_down);

    return true;
}




// Key Events. Following two functions all work the same:
//  Return true if the key-event is finished being handled, false otherwise.
bool ClientAppCommunicatorScreen::handle_key_down(SDL_keysym key) {
    
    // send mouse down
    cmd_sock->send_value(SDL_KEYDOWN);
    
    // send coord
    cmd_sock->send_value(key);

    return true;
}
bool ClientAppCommunicatorScreen::handle_key_up(SDL_keysym key) {
    
    // send mouse down
    cmd_sock->send_value(SDL_KEYUP);
    
    // send coord
    cmd_sock->send_value(key);
    
    return true;
}
