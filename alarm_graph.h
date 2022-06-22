#include <gtk/gtk.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <time.h>
int start_alarm_app(int    argc, char **argv);
static void Stop (GtkWidget *widget, gpointer   data);
static void wait_5_min (GtkWidget *widget, gpointer   data);
static void activate (GtkApplication *app,gpointer        user_data);
void onstop();
#define MOTION 21
