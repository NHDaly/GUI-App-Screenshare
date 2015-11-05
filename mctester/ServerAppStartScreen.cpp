//
//  ClientApp.cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "ServerAppStartScreen.h"
#include "sharedConstants.h"
#include "MacServerApp.h"

#include "utility/SocketClasses.h"

#include "gui/GUIApp.h"
#include "gui/GUIWindow.h"
#include "gui/Compatibility.h"

#include <sstream>

#include TR1_FUNCTIONAL_H

using namespace GUI;
using namespace std;
using namespace std::tr1;
using namespace std::tr1::placeholders;




ServerAppStartScreen::ServerAppStartScreen()
:View(550, 300),
app_to_serve_label(new TextView(300)),
app_to_serve_textbox(new TextBox(get_w()-250, 50)),
host_port_label(new TextView(300)),
host_port_textbox(new TextBox(300, 50)),
start_button(create_button(bind(&ServerAppStartScreen::try_to_connect_and_start, this), "Start Serving"))
{
    app_to_serve_label->set_text("Enter name of App to screenshare:");
    app_to_serve_label->set_text_size(12);

    attach_subview(app_to_serve_label, DispPoint(25, 10));
    attach_subview(app_to_serve_textbox, DispPoint(25, 25));

    host_port_label->set_text("Port of Host Server (probably leave default).");
    host_port_label->set_text_size(12);
    attach_subview(host_port_label, DispPoint(25, 125));
    stringstream ss;
    ss << port_num_k;
    host_port_textbox->set_text(ss.str());
    attach_subview(host_port_textbox, DispPoint(25, 150));
    attach_subview(start_button, DispPoint(get_w()-200, 100));
    
    fill_with_color(light_gray_color_c);

    capture_focus();
    
}

void ServerAppStartScreen::try_to_connect_and_start() {
    App::get()->get_window()->remove_subview(this);
    
    ServerApp *server = 0;
#ifdef __APPLE__
    server = new MacServerApp(app_to_serve_textbox->get_text(),
                              atoi(host_port_textbox->get_text().c_str()));
#else
    //server = new WindowsServerApp(app_to_serve_textbox->get_text());
#endif
    App::get()->get_window()->attach_subview(server, DispPoint());

}

