#include "caculator.hpp"
#include <gtkmm-3.0/gtkmm.h>

static const std::map<guint, char> KEYCODE_MAP = {
    {GDK_KEY_0, '0'},{GDK_KEY_1, '1'}, {GDK_KEY_2, '2'}, {GDK_KEY_3, '3'},
    {GDK_KEY_4, '4'},{GDK_KEY_5, '5'}, {GDK_KEY_6, '6'}, {GDK_KEY_7, '7'},
    {GDK_KEY_8, '8'},{GDK_KEY_9, '9'},
    {GDK_KEY_plus, '+'}, {GDK_KEY_minus, '-'},
    {GDK_KEY_asterisk, '*'}, {GDK_KEY_division, '/'},
    {GDK_KEY_parenleft, '('}, {GDK_KEY_parenright, ')'},
    {GDK_KEY_equal, '='}, {GDK_KEY_Return, '='}
};

class CaculatorGui : public Gtk::Window
{
    constexpr static size_t GRID_SIZE = 17;
    constexpr static size_t ROW_SIZE  = 5;
    constexpr static const char *ALLOWED_KEY = "0123456789-+*/()=";

public:
    CaculatorGui();
    virtual ~CaculatorGui();

private:
    void on_button_clicked(const Glib::ustring &item);
    bool on_key_press_event(GdkEventKey *event) override;
    void add_buttons_in_grid();
    void custom_view();
    void parse_css_load_err(const Glib::RefPtr<const Gtk::CssSection> &section,
                            const Glib::Error &err);

    Gtk::Grid grid;
    Gtk::TextView view;
    Glib::RefPtr<Gtk::TextBuffer> buffer;
    Caculator runner;
    bool clear;
};

inline char get_keyval_char(guint key);
