//
//  ClientApp.h
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#ifndef __MultiComputer_Tester__ServerAppStartScreen__
#define __MultiComputer_Tester__ServerAppStartScreen__

#include "gui/GUIView.h"
#include "gui/GUITextViews.h"
#include "gui/GUIButton.h"

class ServerAppStartScreen : public GUI::View {
public:
    ServerAppStartScreen();
    
private:
    
    GUI::TextView *app_to_serve_label;
    GUI::TextBox *app_to_serve_textbox;
    GUI::TextView *host_port_label;
    GUI::TextBox *host_port_textbox;
    GUI::Button *start_button;

    
    void try_to_connect_and_start();
};


#endif /* defined(__MultiComputer_Tester__ServerAppStartScreen__) */
