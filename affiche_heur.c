#include "affiche_heur.h"
#include "getDataMeteo.h"


int main (int    argc,char **argv){
return start_app(argc,argv);


}

int start_app(int    argc,char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

/* Determines if to continue the timer or not */
static gboolean continue_timer = FALSE;

/* Determines if the timer has started */
static gboolean start_timer = FALSE;

/* Display seconds expired */
static int sec_expired = 0;

static void _quit_cb (GtkWidget *button, gpointer data){
    (void)button; (void)data; /*Avoid compiler warnings*/
    gtk_main_quit();
    return;
}
static gboolean _label1_update(gpointer data){
    GtkLabel *label = (GtkLabel*)data;
    gtk_label_set_label(label, get_current_time());
    return continue_timer;

}
static gboolean _label2_update(gpointer data){
    GtkLabel *label = (GtkLabel*)data;
    gtk_label_set_label(label, getMeteo());
    return continue_timer;

}

static void _start_timer ( gpointer data,gpointer data2){
    GtkWidget *time_label = data;
    GtkWidget *meteo_label = data2;
    if(!start_timer)
    {
        g_timeout_add_seconds(1, _label1_update, time_label);
        g_timeout_add_seconds(10, _label2_update, meteo_label);
        start_timer = TRUE;
        continue_timer = TRUE;
    }
}

char * get_current_time(){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    return asctime (timeinfo);

}
static void activate (GtkApplication *app, gpointer        user_data)
{



  GtkWidget *window = gtk_application_window_new (app);
  GtkWidget *time_label = gtk_label_new(get_current_time());
  printf("%s",getMeteo());
  GtkWidget *meteo_label = gtk_label_new(getMeteo());
  GtkWidget * main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 25);

  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "theme.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_box_set_homogeneous (GTK_BOX (main_box), TRUE);
  gtk_container_add (GTK_CONTAINER (window), main_box);
  gtk_container_add (GTK_CONTAINER (main_box), time_label);
  gtk_container_add (GTK_CONTAINER (main_box), meteo_label);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_default_size(GTK_WINDOW(window), 1366, 768);
  gtk_widget_show_all (window);
   g_timeout_add_seconds(1, _label1_update, time_label);
   g_timeout_add_seconds(10, _label2_update, meteo_label);
    continue_timer = TRUE;
    start_timer = TRUE;

    gtk_main();
    _start_timer(time_label,meteo_label);

}

