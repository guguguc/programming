#include "gui.hpp"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "Caculator");
    CaculatorGui demo;
    app->run(demo);
    return 0;
}
