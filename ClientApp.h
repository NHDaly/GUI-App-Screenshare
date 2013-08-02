//
//  ClientApp.h
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#ifndef __MultiComputer_Tester__ClientApp__
#define __MultiComputer_Tester__ClientApp__

#include "gui/GUIView.h"
#include "gui/GUITextViews.h"
#include "gui/GUIButton.h"

class ClientApp : public GUI::View {
public:
    ClientApp();
    
private:
    
    GUI::TextBox *host_textbox;
    GUI::Button *start_button;

    
    void try_to_connect_and_start();
};


#endif /* defined(__MultiComputer_Tester__ClientApp__) */
