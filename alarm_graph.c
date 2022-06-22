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
  //pinMode (27, INPUT) ;
 /* if(get_motion() == 0){
    delay(5000);
    pinMode (27, OUTPUT) ;
    delay(5000);
    }
    pinMode (27, INPUT) ;
  
  */
}
static void wait_5_min (GtkWidget *widget, gpointer   data)
{
  g_print ("wait_5_min\n");
}

static void activate (GtkApplication *app,gpointer        user_data)
{
  GtkWidget *window= gtk_application_window_new (app);
  GtkWidget *button= gtk_button_new_with_label ("stop");;
  GtkWidget * main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 25);

  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 480);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

  g_signal_connect (button, "clicked", G_CALLBACK (Stop), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
 


  gtk_box_set_homogeneous (GTK_BOX (main_box), TRUE);
  gtk_container_add (GTK_CONTAINER (window), main_box);
  gtk_container_add (GTK_CONTAINER (main_box), button);



  gtk_widget_show_all (window);
}


int get_motion(){
   wiringPiSetup () ;
  pinMode (MOTION, INPUT) ;
  time_t begintime, starttime,endtime;
  time ( &begintime );
  
  while (difftime(  begintime, starttime) < 120){
    printf("%d \n",difftime(  begintime, starttime));
	time ( &starttime );
	while(digitalRead(MOTION)) {
		delay(100);
	}
	time ( &endtime );
	if(difftime(  endtime, starttime) > 2){
		printf("Detected long motion \n");
    return 1;
	}
	return 0;
  }
  
  
  
  
  }


