#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// { red, green, blue, alpha }, values from 0-1
GdkRGBA colour_on = { 0, 1, 0, 1 };
GdkRGBA colour_off = { 0.1, 0.1, 0.1, 1};

// geometry to place the display
const char *__restrict geometry="128x64+1616+0";


GtkWidget *window;
Display *display;
char *       display_name = NULL;
unsigned int display_width, display_height;
Bool state;
Atom capsLock;


int update()
{
    XkbGetNamedIndicator ( display, capsLock, NULL, &state, NULL, NULL );
    if ( state == True )
    {
        gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &colour_on);
    }
    else
    {
        gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &colour_off);
    }
    return True;
}



int main(int argc, char *argv[]) {

    if ( (display = XOpenDisplay(display_name)) == NULL )
    { fprintf(stderr, "%s: couldn't connect to X server %s\n", "foo", "bar");
            exit(EXIT_FAILURE);
    }

    int index;
    int rtrn;
    capsLock = XInternAtom(display, "Caps Lock", False);

    int sx, sy, x, y;
    sx = sy = x = y = 0;
    if ( 4 != sscanf(geometry, "%ix%i+%i+%i", &sx, &sy, &x, &y ) )
    {
            perror ( "geometry can't be parsed" );
            return(1);
    }

        gtk_init(&argc, &argv);
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(window), sx, sy );
        gtk_window_set_decorated(GTK_WINDOW(window), False );
        gtk_widget_show(window);
        gtk_window_move(GTK_WINDOW(window), x, y );
        
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
        
        g_timeout_add(100, update, window);
        update();
        gtk_main();


        return 0;
}
