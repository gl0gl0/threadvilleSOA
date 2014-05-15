#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "ui.h"

typedef struct _uivars {
	GtkWidget *mainWindow;
	GtkWidget *drawingArea;
} uivars;

uivars this;


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

	gtk_container_add((GtkContainer*) this.mainWindow, this.drawingArea);
}

/* createWindow
 * Creates the main window
 *
 * @return void
 */
void createWindow () {
	this.mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*) this.mainWindow, 1030, 630);
	gtk_window_set_title((GtkWindow*) this.mainWindow, "Threadville");
	gtk_window_set_position((GtkWindow*) this.mainWindow, GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width((GtkContainer*) this.mainWindow, 15);

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