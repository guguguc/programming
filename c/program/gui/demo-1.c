
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

#include <xcb/xcb.h>

#include <X11/Xlib.h>

double get_time()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (double)ts.tv_nsec;
}

int main()
{
    xcb_connection_t *c;
    xcb_atom_t *atoms;
    xcb_intern_atom_cookie_t *cs;
    char **names;
    int count, i;
    double start, end, diff;


    // Xlib
    Display *disp;
    Atom *atoms_x;
    double diff_x;

    // connect to x sever
    c = xcb_connect(NULL, NULL);
    assert(xcb_connection_has_error(c) == 0);

    count = 500;
    atoms = (xcb_atom_t*)malloc(count * sizeof(atoms));
    names = (char**) malloc(count * sizeof(char*));

    // init names
    for (i = 0; i < count; ++i) {
        char buf[100];
        sprintf(buf, "NAME%d", i);
        names[i] = strdup(buf);
    }

    // bad use
    start = get_time();
    for (i = 0; i < count; ++i)
        atoms[i] = xcb_intern_atom_reply(c,
                                         xcb_intern_atom(c, 0, strlen(names[i]), names[i]),
                                         NULL)->atom;
    end = get_time();
    diff = end - start;
    printf("bad use time : %2fms\n", diff/1e6);

    // good use
    start = get_time();
    cs = (xcb_intern_atom_cookie_t*)malloc(count * sizeof(xcb_intern_atom_cookie_t));
    for (i = 0; i < count; ++i)
        cs[i] = xcb_intern_atom(c, 0, strlen(names[i]), names[i]);
    for (i = 0; i < count; ++i) {
        xcb_intern_atom_reply_t *r;
        r = xcb_intern_atom_reply(c, cs[i], 0);
        if (r)
            atoms[i] = r->atom;
        free(r);
    }
    end = get_time();
    printf("good use time : %2fms\n", (end-start)/(1e6));
    printf("ratio         : %f\n", diff / (end-start));

    free(atoms);
    free(cs);

    xcb_disconnect(c);
    for (i = 0; i < count; ++i)
        free(names[i]);
    free(names);
    return 0;
}
