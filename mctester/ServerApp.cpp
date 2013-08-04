//
//  ServerApp.cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "ServerApp.h"
#include "sharedConstants.h"

#include "gui/GUIApp.h"
#include "gui/GUIWindow.h"
#include "utility/SocketClasses.h"
#include "gui/Compatibility.h"

#include TR1_FUNCTIONAL_H

using namespace std;
using namespace GUI;
using namespace std::tr1;


ServerApp::ServerApp(const string &appname_)
:View(400,200), serv(new Socket_Server(port_num_k)),
cmd_sock(0),
//data_sock(port_num_k+1),
appname(appname_)
{
//    data_sock.bind();
    
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



void ServerApp::poll_client()
{
    
    Uint8 eventType = 0; // get event-type from client
    
    // check for events. if events, receive them.
    short revents;
    if (cmd_sock->poll(POLLIN, revents, 1)) {
        
        cmd_sock->recv_into(&eventType);    // receive an SDL event type
        
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
