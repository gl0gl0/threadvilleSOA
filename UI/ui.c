#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "ui.h"
#include "global.h"

gint boder_width = 20;
gint window_width = 960;
gint window_height = 680;

gint unit = 20;


/* drawThreadville
 * Draws the main scene
 *
 * @return void
 */
 void drawBlock (GtkWidget *widget, gint x, gint y, short int lower, short int upper) {
 	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, x, y, 120, 120);
	// Upper left
	if (upper)
		gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, (x+20), y, 20, 20);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, x, (y+20), 20, 20);
	// Lower left
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, x, (y+80), 20, 20);
	if (lower)
		gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, (x+20), (y+100), 20, 20);
	// Upper right
	if (upper)
		gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, (x+80), y, 20, 20);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, (x+100), (y+20), 20, 20);
	// Lower right
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, (x+100), (y+80), 20, 20);
	if (lower)
		gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, (x+80), (y+100), 20, 20);
 }


/* drawThreadville
 * Draws the main scene
 *
 * @return void
 */
void drawThreadville (GtkWidget *widget) {
	// Background
	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
	
	// Streets
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, boder_width, 0, window_width, window_height);
	//gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, boder_width, 0, window_width, unit); // top
	//gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, boder_width, 0, unit, window_height); // left
	//gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, window_width, 0, unit, window_height); // right
	//gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, boder_width, window_height-20, window_width, unit); // bottom

	// Uptown Blocks - top
	drawBlock (widget, 40, 20, 1, 1);
	drawBlock (widget, 200, 20, 1, 1);
	drawBlock (widget, 360, 20, 1, 1);
	drawBlock (widget, 520, 20, 1, 1);
	drawBlock (widget, 680, 20, 1, 1);
	drawBlock (widget, 840, 20, 1, 1);

	//gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 20, 140, 960, unit);

	// Uptown Blocks - bottom
	drawBlock (widget, 40, 160, 0, 1);
	drawBlock (widget, 200, 160, 0, 1);
	drawBlock (widget, 360, 160, 0, 1);
	drawBlock (widget, 520, 160, 0, 1);
	drawBlock (widget, 680, 160, 0, 1);
	drawBlock (widget, 840, 160, 0, 1);

	//gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 20, 300, 960, 80);
	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, 20, 280, 960, 20);
	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, 20, 380, 960, 20);

	// Downtonw Blocks - top
	drawBlock (widget, 40, 400, 1, 0);
	drawBlock (widget, 200, 400, 1, 0);
	drawBlock (widget, 360, 400, 1, 0);
	drawBlock (widget, 520, 400, 1, 0);
	drawBlock (widget, 680, 400, 1, 0);
	drawBlock (widget, 840, 400, 1, 0);

	//gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 20, 520, 960, unit);

	// Downtonw Blocks - bottom
	drawBlock (widget, 40, 540, 1, 1);
	drawBlock (widget, 200, 540, 1, 1);
	drawBlock (widget, 360, 540, 1, 1);
	drawBlock (widget, 520, 540, 1, 1);
	drawBlock (widget, 680, 540, 1, 1);
	drawBlock (widget, 840, 540, 1, 1);

	// Side borders ** tal vez no se ocupen por la rotonda
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, boder_width, 0, unit, window_height); // left
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, window_width, 0, unit, window_height); // right

	// Bridges
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 170, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 330, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 490, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 650, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, 810, 280, 20, unit*6);
}


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

	drawThreadville(widget);
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
	gtk_drawing_area_size((GtkDrawingArea*) this.drawingArea, 1000, 680);
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
	gtk_window_set_default_size((GtkWindow*) this.mainWindow, 1000, 680);
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