#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "ui.h"
#include "global.h"

gint window_width = 1120;
gint window_height = 680;
gint border_width = 80;
gint canvas_width = 960;
gint canvas_height = 680;

gint unit = 20;


/* drawThreadville
 * Draws the main scene
 *
 * @return void
 */
 void drawBlock (GtkWidget *widget, gint x, gint y, short int lower, short int upper) {
 	x = x + border_width;
 	gdk_draw_rectangle(this.pixMap,  widget->style->fg_gc[0], TRUE, x, y, 120, 120);
	// Upper left
	if (upper)
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+20), y, 20, 20);
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, x, (y+20), 20, 20);
	// Lower left
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, x, (y+80), 20, 20);
	if (lower)
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+20), (y+100), 20, 20);
	// Upper right
	if (upper)
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+80), y, 20, 20);
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+100), (y+20), 20, 20);
	// Lower right
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+100), (y+80), 20, 20);
	if (lower)
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+80), (y+100), 20, 20);
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
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, border_width, 0, canvas_width, canvas_height);

	// Uptown Blocks - top
	drawBlock (widget, 20, 20, 1, 1);
	drawBlock (widget, 180, 20, 1, 1);
	drawBlock (widget, 340, 20, 1, 1);
	drawBlock (widget, 500, 20, 1, 1);
	drawBlock (widget, 660, 20, 1, 1);
	drawBlock (widget, 820, 20, 1, 1);

	// Uptown Blocks - bottom
	drawBlock (widget, 20, 160, 0, 1);
	drawBlock (widget, 180, 160, 0, 1);
	drawBlock (widget, 340, 160, 0, 1);
	drawBlock (widget, 500, 160, 0, 1);
	drawBlock (widget, 660, 160, 0, 1);
	drawBlock (widget, 820, 160, 0, 1);

	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, border_width+unit, 280, 920, 20);

	// Central Lines
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+unit, 320, window_width-border_width-unit, 320);
	gdk_draw_line(this.pixMap, widget->style->bg_gc[0], border_width+unit, 340, window_width-border_width-unit, 340);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+unit, 360, window_width-border_width-unit, 360);

	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, border_width+unit, 380, 920, 20);

	// Downtonw Blocks - top
	drawBlock (widget, 20, 400, 1, 0);
	drawBlock (widget, 180, 400, 1, 0);
	drawBlock (widget, 340, 400, 1, 0);
	drawBlock (widget, 500, 400, 1, 0);
	drawBlock (widget, 660, 400, 1, 0);
	drawBlock (widget, 820, 400, 1, 0);

	// Downtonw Blocks - bottom
	drawBlock (widget, 20, 540, 1, 1);
	drawBlock (widget, 180, 540, 1, 1);
	drawBlock (widget, 340, 540, 1, 1);
	drawBlock (widget, 500, 540, 1, 1);
	drawBlock (widget, 660, 540, 1, 1);
	drawBlock (widget, 820, 540, 1, 1);

	// Bridges
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, border_width+150, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, border_width+310, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, border_width+470, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, border_width+630, 280, 20, unit*6);
	gdk_draw_rectangle(this.pixMap, widget->style->black_gc, TRUE, border_width+790, 280, 20, unit*6);

	// Vertical lines
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+160, 20, border_width+160, 280);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+320, 20, border_width+320, 280);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+480, 20, border_width+480, 280);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+640, 20, border_width+640, 280);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+800, 20, border_width+800, 280);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+160, 400, border_width+160, 660);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+320, 400, border_width+320, 660);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+480, 400, border_width+480, 660);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+640, 400, border_width+640, 660);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+800, 400, border_width+800, 660);
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
	gtk_drawing_area_size((GtkDrawingArea*) this.drawingArea, window_width, window_height);
	gtk_widget_modify_bg((GtkWidget*) this.drawingArea, GTK_STATE_NORMAL, &color);
	gdk_color_parse("yellow", &color);
	gtk_widget_modify_fg((GtkWidget*) this.drawingArea, GTK_STATE_NORMAL, &color);

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
	gtk_window_set_default_size((GtkWindow*) this.mainWindow, window_width, window_height);
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