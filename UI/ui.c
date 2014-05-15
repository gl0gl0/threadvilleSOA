#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "ui.h"
#include "global.h"

/* --------------------------- EVENTS --------------------------- */

void gtk_expose_event (GtkWidget *widget, GdkEventExpose *event) {
	gdk_draw_drawable(widget->window, 
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)], 
			this.pixMap, 
			event->area.x, event->area.y,
			event->area.x, event->area.y,
			event->area.width, event->area.height);
}

void gtk_configure_event (GtkWidget *widget, GdkEventConfigure *event) {
	if (this.pixMap)
		g_object_unref(this.pixMap);

	this.pixMap = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);

	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, 0, 0, widget->allocation.width, 20);
}



/* --------------------------- METHODS --------------------------- */

/* createDrawingArea
 * Creates the main drawing area
 *
 * @return void
 */
void createDrawingArea () {
	// Background color
	GdkColor color;
	gdk_color_parse("green", &color);

	// Creates drawing area with the specified dimensions and background color
	this.drawingArea = gtk_drawing_area_new();
	gtk_drawing_area_size((GtkDrawingArea*) this.drawingArea, 1000, 600);
	gtk_widget_modify_bg((GtkWidget*) this.drawingArea, GTK_STATE_NORMAL, &color);

	// Attach events to the drawing area
	gtk_signal_connect((GtkObject*) this.drawingArea, "expose_event", G_CALLBACK(gtk_expose_event), NULL);
	gtk_signal_connect((GtkObject*) this.drawingArea, "configure_event", G_CALLBACK(gtk_configure_event), NULL);

	gtk_container_add((GtkContainer*) this.mainWindow, this.drawingArea);
}

/* createWindow
 * Creates the main window
 *
 * @return void
 */
void createWindow () {
	this.mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*) this.mainWindow, 1000, 600);
	gtk_window_set_title((GtkWindow*) this.mainWindow, "Threadville");
	gtk_window_set_position((GtkWindow*) this.mainWindow, GTK_WIN_POS_CENTER_ALWAYS);

	// Attach close event to the window
	gtk_signal_connect((GtkObject*) this.mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

/* display
 * Shows all elements, in order
 *
 * @return void
 */
void display () {
	gtk_widget_show(this.drawingArea);
	gtk_widget_show(this.mainWindow);
}


/* initUI
 * Initializes the UI
 *
 * @return void
 */
void initUI () {
	createWindow ();
	createDrawingArea();
    display();

    gtk_main();
}