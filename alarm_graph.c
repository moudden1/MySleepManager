#include "alarm_graph.h"




int start_alarm_app(int    argc, char **argv){

GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}




static void Stop (GtkWidget *widget, gpointer   data)
{
  pinMode (27, INPUT) ;
}
static void wait_5_min (GtkWidget *widget, gpointer   data)
{
  g_print ("wait_5_min\n");
}

static void activate (GtkApplication *app,gpointer        user_data)
{
  GtkWidget *window= gtk_application_window_new (app);
  GtkWidget *button= gtk_button_new_with_label ("stop");;
  GtkWidget *button2= gtk_button_new_with_label ("5 MINS");
  GtkWidget * main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 25);

  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 480);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

  g_signal_connect (button, "clicked", G_CALLBACK (Stop), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  g_signal_connect (button2, "clicked", G_CALLBACK (wait_5_min), NULL);
  g_signal_connect_swapped (button2, "clicked", G_CALLBACK (gtk_widget_destroy), window);


  gtk_box_set_homogeneous (GTK_BOX (main_box), TRUE);
  gtk_container_add (GTK_CONTAINER (window), main_box);
  gtk_container_add (GTK_CONTAINER (main_box), button);
  gtk_container_add (GTK_CONTAINER (main_box), button2);



  gtk_widget_show_all (window);
}



