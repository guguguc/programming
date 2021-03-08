#include "gui.hpp"
#include <iostream>

CaculatorGui::CaculatorGui(): buffer(Gtk::TextBuffer::create()), runner(), clear(false)
{
    custom_view();
    grid.attach(view, 0, 0, ROW_SIZE, 1);
    add_buttons_in_grid();
    add(grid);
    add_events(Gdk::KEY_PRESS_MASK);
    set_border_width(10);
    show_all_children();
}

void CaculatorGui::custom_view()
{
    view.set_hexpand();
    view.set_vexpand();
    view.set_editable(false);
    view.set_buffer(buffer);
    std::string path = "../assets/style.css";
    auto css = Gtk::CssProvider::create();
    css->signal_parsing_error().connect(sigc::mem_fun(*this, &CaculatorGui::parse_css_load_err));
    css->load_from_path(path);
    auto screen = Gdk::Screen::get_default();
    auto ctx = view.get_style_context();
    ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void CaculatorGui::add_buttons_in_grid()
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
    char keyval = get_keyval_char(event->keyval);
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
