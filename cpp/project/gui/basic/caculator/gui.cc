#include "gui.hpp"
#include <iostream>

CaculatorGui::CaculatorGui(): runner(), clear(false)
{
    // View setting
    view.set_hexpand();
    view.set_vexpand();
    view.set_editable(false);
    buffer = Gtk::TextBuffer::create();
    view.set_buffer(buffer);
    custom_view();
    // Grid setting
    grid.attach(view, 0, 0, ROW_SIZE, 1);
    add_buttons();
    // Window setting
    set_border_width(10);
    add(grid);
    add_events(Gdk::KEY_PRESS_MASK);
    show_all_children();
}

void CaculatorGui::add_buttons()
{
    for (size_t i = ROW_SIZE; i < GRID_SIZE+ROW_SIZE; ++i)
    {
        int col = i % ROW_SIZE, row = i / ROW_SIZE;
        auto bt_name = Glib::ustring(1, ALLOWED_KEY[i-ROW_SIZE]);
        Gtk::Button *bt = Gtk::make_managed<Gtk::Button>(bt_name);
        auto handler = sigc::mem_fun(*this,
                                     &CaculatorGui::on_button_clicked);
        bt->signal_clicked().connect(sigc::bind(handler, bt_name));
        bt->set_hexpand();
        bt->set_vexpand();
        grid.attach(*bt, col, row);
    }
}

void CaculatorGui::custom_view()
{
    std::string path = "../assets/style.css";
    auto css = Gtk::CssProvider::create();
    css->signal_parsing_error().connect(sigc::mem_fun(*this, &CaculatorGui::parse_css_load_err));
    css->load_from_path(path);
    auto screen = Gdk::Screen::get_default();
    auto ctx = view.get_style_context();
    ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void CaculatorGui::on_button_clicked(const Glib::ustring &item)
{
    if (clear)
    {
        buffer->set_text("");
        clear = false;
    }
    buffer->insert(buffer->end(), item);
    if (item == "=")
    {
        auto ans = runner.run(buffer->get_text().raw());
        buffer->insert(buffer->end(), Glib::ustring(std::to_string(ans)));
        clear = true;
    }
}

bool CaculatorGui::on_key_press_event(GdkEventKey *event)
{
    // std::cerr << std::hex << event->keyval << "\n";
    char keyval = get_keyval_char(event->keyval);
    // std::cerr << "key val: " << keyval << "\n";
    if (keyval != '\0')
    {
        on_button_clicked(Glib::ustring(std::string(1, keyval)));
        return true;
    }
    return Gtk::Window::on_key_press_event(event);
}

void CaculatorGui::parse_css_load_err(const Glib::RefPtr<const Gtk::CssSection> &section,
                                      const Glib::Error &err)
{
    std::cout << "error code: " << err.code() << "\n";
    std::cout << err.what() << "\n";
}

CaculatorGui::~CaculatorGui()
{
}

inline char get_keyval_char(guint key)
{
    return KEYCODE_MAP.find(key) == KEYCODE_MAP.end() ? '\0'
                                                      : KEYCODE_MAP.at(key);
}
