#include "global.h"
#include "events.h"

/* --------------------------- EVENTS --------------------------- */

void gtk_expose_event (GtkWidget *widget, GdkEventExpose *event) {
	gdk_draw_drawable(widget->window, 
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)], 
			this.pixMap, 
			event->area.x, event->area.y,
			event->area.x, event->area.y,
			event->area.width, event->area.height);

	drawThreadville(widget);
}

void gtk_configure_event (GtkWidget *widget, GdkEventConfigure *event) {
	if (this.pixMap)
		g_object_unref(this.pixMap);

	this.pixMap = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);
	drawThreadville(widget);
}

void generate_car_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Generate car pressed: %s \n", (char *)data);
}

void generate_ambulance_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Generate ambulance pressed: %s \n", (char *)data);
}

void stop_simulation_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Stop simulation pressed: %s \n", (char *)data);
}

void start_simulation_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Start simulation pressed: %s \n", (char *)data);
}