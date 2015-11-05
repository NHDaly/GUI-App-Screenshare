
#include "gui/GUIApp.h"
#include "gui/GUIWindow.h"
#include "gui/GUIImageView.h"
#include "gui/GUIButton.h"
#include "gui/GUITextViews.h"
#include "gui/GUIMsg.h"

#include "ServerAppStartScreen.h"
#include "ClientApp.h"

#include "utility/SocketClasses.h"
#include "utility/NathanUtility.h"


#include <iostream>
using namespace std;
using namespace GUI;

void reset_after_disconnection(const SocketError &);
void display_user_error(const UserError &);

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
        window.attach_subview(new ServerAppStartScreen, DispPoint());
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
: View (600, 400), textbox(new TextBox(250, 20)),
serverStart(create_button(ServerStart(window, this), "Server Start")),
clientStart(create_button(ClientStart(window, this), "Client Start"))
{
    fill_with_color(light_gray_color_c);

#ifdef __APPLE__ // Only allow macs to be servers right now.
    TextView *app_name_label(new TextView(250));
    app_name_label->set_text("Screenshare an app on this computer.");
    app_name_label->set_text_size(12);
    attach_subview(app_name_label, DispPoint(250, 80));
    attach_subview(serverStart, DispPoint(350, 100));
#endif

    TextView *client_label(new TextView(300, 200));
    client_label->set_text("Share an app from a remote server.");
    client_label->set_text_size(12);
    attach_subview(client_label, DispPoint(250, 180));
    attach_subview(clientStart, DispPoint(350, 200));
    
}


int main (int argc, char ** argv) {
    
    initGUI();

    string app = "Game Maker for Mac";

    try {
        App::get()->register_exception_handler<SocketError>(&reset_after_disconnection);
        App::get()->register_exception_handler<UserError>(&display_user_error);
        
        Window win(600, 400);
//        View *view(new GUICommunicator(GUIImage("screensh.bmp"), app));
        
        
        
//        win.attach_subview(new ServerApp(app), DispPoint());
//        win.attach_subview(new ClientApp(), DispPoint());
        win.attach_subview(new StartScreen(win), DispPoint());

        App::get()->set_framerate_cap(40);
        App::get()->run(&win);
    }
    catch (const GUI::Error &e) {
        cout << e.msg << endl;
    }
    
    return 0;
}
 
void reset_after_disconnection(const SocketError &error) {
    Window *win = App::get()->get_window();
    delete win->remove_last_subview();
    View *start = new StartScreen(*win);
    win->attach_subview(start, DispPoint());
    win->resize(start->get_w(), start->get_h());
    
    display_user_error(UserError(error.msg));
}

void display_user_error(const UserError &error) {
    Window *win = App::get()->get_window();
    DispPoint dim = win->get_dim();
    
    TextView *error_view = new TextView(dim.x/2);
    error_view->set_text(error.msg);
    win->attach_subview(error_view, DispPoint(dim.x/3, dim.y - 100));
  
    sleep(4);
    delete win->remove_last_subview();

}





