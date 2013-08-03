
#include "SDL/SDL.h"
#include "gui/GUIApp.h"
#include "gui/GUIWindow.h"
#include "gui/GUIImageView.h"
#include "gui/GUIButton.h"
#include "gui/GUITextViews.h"
#include "gui/GUIMsg.h"

#include "ServerApp.h"
#include "ClientApp.h"

#include "utility/SocketClasses.h"


#include <iostream>
using namespace std;
using namespace GUI;

template <typename T>
void printError(const T &e) {
    
//    Msg error_msg(300, 80, e.msg);
//    
//    error_msg.pop_up(1500);

    cout << e.msg << endl;
}

struct StartScreen : public GUI::View {
public:
    
    StartScreen(Window &window);
    
    TextBox *textbox;
    Button *serverStart;
    Button *clientStart;
    
};

struct ServerStart {
    
    ServerStart(Window &win, StartScreen *screen)
    : window(win), start_screen(screen)
    { }
    
    void operator() () {
        window.remove_subview(start_screen);
        window.attach_subview(new ServerApp(start_screen->textbox->get_text()),
                              DispPoint());
    }
    
    Window &window;
    StartScreen *start_screen;
};
struct ClientStart {
    
    ClientStart(Window &win, StartScreen *screen)
    : window(win), start_screen(screen)
    { }
    
    void operator() () {
        window.remove_subview(start_screen);
        window.attach_subview(new ClientApp(), DispPoint());
    }
    
    Window &window;
    StartScreen *start_screen;
};

StartScreen::StartScreen(Window &window)
: View (600, 400), textbox(new TextBox(200, 20)),
serverStart(create_button(ServerStart(window, this), "Server Start")),
clientStart(create_button(ClientStart(window, this), "Client Start"))
{
    fill_with_color(Light_Gray_Color);

#ifdef __APPLE__ // Only allow macs to be servers right now.
    //    attach_subview(textbox, DispPoint(50, 100));
    //    attach_subview(serverStart, DispPoint(300, 100));
#endif

    attach_subview(clientStart, DispPoint(300, 200));
    
}


int main (int argc, char ** argv) {
    
    initGUI();

    string app = "Game Maker for Mac";

    try {
        App::get()->register_exception_handler<SocketError>(&printError<SocketError>);
        
        Window win(600, 400);
//        View *view(new GUICommunicator(GUIImage("screensh.bmp"), app));
        
        
        
//        win.attach_subview(new ServerApp(app), DispPoint());
//        win.attach_subview(new ClientApp(), DispPoint());
        win.attach_subview(new StartScreen(win), DispPoint());

        App::get()->set_framerate_cap(60);
        App::get()->run(&win);
    }
    catch (const GUIError &e) {
        cout << e.msg << endl;
    }
    
    return 0;
}






