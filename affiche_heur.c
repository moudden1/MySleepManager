#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>

/* Determines if to continue the timer or not */
static gboolean continue_timer = FALSE;

/* Determines if the timer has started */
static gboolean start_timer = FALSE;

/* Display seconds expired */
static int sec_expired = 0;

static void
_quit_cb (GtkWidget *button, gpointer data)
{
    (void)button; (void)data; /*Avoid compiler warnings*/
    gtk_main_quit();
    return;
}


static gboolean
_label_update(gpointer data)
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    //label = gtk_label_new(asctime (timeinfo));
    GtkLabel *label = (GtkLabel*)data;
    char buf[256];
    memset(&buf, 0x0, 256);
    snprintf(buf, 255, "%s",asctime (timeinfo));
    gtk_label_set_label(label, buf);
    return continue_timer;

}

static void
_start_timer ( gpointer data)
{
    GtkWidget *label = data;
    if(!start_timer)
    {
        g_timeout_add_seconds(1, _label_update, label);
        start_timer = TRUE;
        continue_timer = TRUE;
    }
}




int main(void)
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkCssProvider* Provider = gtk_css_provider_new();
    GtkWidget *label;

    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (window), "destroy", 
                    G_CALLBACK (gtk_main_quit),
                    NULL);
    vbox = gtk_box_new (FALSE, 2);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    label = gtk_label_new(asctime (timeinfo));



    gtk_box_pack_start (GTK_BOX(vbox), label, 0, 0, 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 1366, 768);
   gtk_window_set_resizable (GTK_WINDOW(window), FALSE);


    gtk_widget_show_all(window);

    g_timeout_add_seconds(1, _label_update, label);
    continue_timer = TRUE;
    start_timer = TRUE;

    gtk_main();
    _start_timer(label);
    return 0;
}
