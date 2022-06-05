#include <gtk/gtk.h>

static void
Stop (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Stop\n");
}
static void
wait_5_min (GtkWidget *widget,
             gpointer   data)
{
  g_print ("wait_5_min\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button2;
  GtkWidget *grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 480);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

 /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);



  button = gtk_button_new_with_label ("stop");
  g_signal_connect (button, "clicked", G_CALLBACK (Stop), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);


   button2 = gtk_button_new_with_label ("5 MINS");
  g_signal_connect (button2, "clicked", G_CALLBACK (wait_5_min), NULL);
  g_signal_connect_swapped (button2, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button2, 0, 1, 2, 1);



  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

