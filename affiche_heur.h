#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h> 



int start_app(int    argc,char **argv);
char * get_current_time();
static void _start_timer ( gpointer data,gpointer data2);
static gboolean _label_update(gpointer data);
static void _quit_cb (GtkWidget *button, gpointer data);
static void activate (GtkApplication *app, gpointer        user_data);

