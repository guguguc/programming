#include <stdio.h>
#include <unistd.h>

#include <xcb/xcb.h>

int main()
{
    xcb_connection_t *c;
    xcb_screen_t *screen;
    xcb_window_t win;

    // open the connection to Xserver
    c = xcb_connect(NULL, NULL);
    // get first screen
    screen = xcb_setup_roots_iterator(xcb_get_setup(c)).data;
    // ask for window id
    win = xcb_generate_id(c);
    // create the window
    xcb_create_window(c,
                      XCB_COPY_FROM_PARENT,
                      win,
                      screen->root,
                      0, 0,
                      1000, 1000,
                      10,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      0, NULL);
    // map the window on the screen
    xcb_map_window(c, win);
    xcb_flush(c);
    pause();
    return 0;
}

