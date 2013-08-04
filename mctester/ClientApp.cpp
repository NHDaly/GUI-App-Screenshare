//
//  ClientApp.cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "ClientApp.h"
#include "sharedConstants.h"
#include "ClientAppCommunicatorScreen.h"

#include "utility/SocketClasses.h"

#include "gui/GUIApp.h"
#include "gui/GUIWindow.h"
#include "gui/Compatibility.h"

#include TR1_FUNCTIONAL_H

using namespace GUI;
using namespace std;
using namespace std::tr1;
using namespace std::tr1::placeholders;




ClientApp::ClientApp()
:View(400, 200), host_textbox(new TextBox(get_w()-150, 50)),
start_button(create_button(bind(&ClientApp::try_to_connect_and_start, this), "Go"))
{
    attach_subview(host_textbox, DispPoint(25, 25));
    attach_subview(start_button, DispPoint(get_w()-125, 50));
    
    fill_with_color(Light_Gray_Color);

    capture_focus();
    
}

void ClientApp::try_to_connect_and_start() {
    
    UDP_Socket datasock(port_num_k+1);

    Socket_Client *cmdsock = new Socket_Client(host_textbox->get_text(), port_num_k, 10);
    cmdsock->connect();
    
    ClientAppCommunicatorScreen *screen = new ClientAppCommunicatorScreen(cmdsock, datasock);
    
    App::get()->get_window()->remove_subview(this);
    App::get()->get_window()->attach_subview(screen, DispPoint());
    
}

