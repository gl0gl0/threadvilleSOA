#ifndef EVENTS_H
#define EVENTS_H

void gtk_expose_event (GtkWidget *widget, GdkEventExpose *event);
void gtk_configure_event (GtkWidget *widget, GdkEventConfigure *event);
void generate_car_callback_event (GtkWidget *widget, gpointer data);
void generate_ambulance_callback_event (GtkWidget *widget, gpointer data);

void red_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void green_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void blue_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void white_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void gray_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void black_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void lightblue_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void pink_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void orange_bus_checkbox_callback_event (GtkWidget *widget, gpointer data);
void all_buses_checkbox_callback_event (GtkWidget *widget, gpointer data);
void obstacles_checkbox_callback_event (GtkWidget *widget, gpointer data);

void stop_simulation_callback_event (GtkWidget *widget, gpointer data);
void start_simulation_callback_event (GtkWidget *widget, gpointer data);

#endif