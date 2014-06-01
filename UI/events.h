#ifndef EVENTS_H
#define EVENTS_H

void gtk_expose_event (GtkWidget *widget, GdkEventExpose *event);
void gtk_configure_event (GtkWidget *widget, GdkEventConfigure *event);
void generate_car_callback_event (GtkWidget *widget, gpointer data);
void generate_ambulance_callback_event (GtkWidget *widget, gpointer data);
void stop_simulation_callback_event (GtkWidget *widget, gpointer data);
void start_simulation_callback_event (GtkWidget *widget, gpointer data);

#endif