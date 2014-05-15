#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "ui.h"

/*void createDrawingArea () {
}*/

/* main
 * Initializes the ui, shows the main window
 *
 * @return void
 */
void displayUI () {
	/* creates the main window */
	GtkWidget *mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*) mainWindow, 400, 468);
	gtk_window_set_title((GtkWindow*) mainWindow, "Inicio");
	gtk_window_set_position((GtkWindow*) mainWindow, GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width((GtkContainer*) mainWindow, 15);

	GtkWidget *drawingArea = gtk_drawing_area_new();
	gtk_drawing_area_size((GtkDrawingArea*) drawingArea, 200, 200);
	GdkColor color;
	gdk_color_parse("green", &color);
	gtk_widget_modify_bg((GtkWidget*) drawingArea, GTK_STATE_NORMAL, &color);
	gtk_container_add((GtkContainer*) mainWindow, drawingArea);

	/* Attach close event to the window */
	gtk_signal_connect((GtkObject*) mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	/* Shows the window */
	gtk_widget_show_all(mainWindow);
}