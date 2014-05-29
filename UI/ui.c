#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <pthread.h>

#include "ui.h"
#include "global.h"

static int currently_drawing = 0;

gint window_width = 1120;
gint window_height = 680;
gint border_width = 80;
gint canvas_width = 960;
gint canvas_height = 680;

gint unit = 20;

struct readThreadParams
{
	 GdkRectangle car;
};


//do_draw will be executed in a separate thread whenever we would like to update
//our animation
void *do_draw(void *ptr){
	printf("Do draw\n");
    //currently_drawing = 1;

    //When dealing with gdkPixmap's, we need to make sure not to
    //access them from outside gtk_main().
    gdk_threads_enter();
    struct readThreadParams *readParams = ptr;
    GdkRectangle car = readParams->car;
	gdk_draw_rectangle(this.pixMap, this.drawingArea->style->white_gc, TRUE, car.x, car.y, car.width, car.height);
    gdk_threads_leave();

    //currently_drawing = 0;

    return NULL;
}


/* drawCar
 * Draws a car
 *
 * @return void
 */
void drawCar (gint x, gint y) {
	GdkRectangle car;

	car.x = x;
	car.y = y;
	car.width = 10;
	car.height = 15;
	gdk_draw_rectangle(this.pixMap, this.drawingArea->style->white_gc, TRUE, car.x, car.y, car.width, car.height);

	gtk_widget_queue_draw_area(this.drawingArea, car.x, car.y, car.width, car.height);
}

/* drawBlock
 * Draws a block with the specified x,y and letter
 *
 * @return void
 */
 void drawBlock (GtkWidget *widget, gint x, gint y, short int lower, short int upper, const gchar* string) {
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

	gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-300-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+50), (y+70), string);
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
	drawBlock (widget, 20, 20, 1, 1, "A");
	drawBlock (widget, 180, 20, 1, 1, "B");
	drawBlock (widget, 340, 20, 1, 1, "C");
	drawBlock (widget, 500, 20, 1, 1, "D");
	drawBlock (widget, 660, 20, 1, 1, "E");
	drawBlock (widget, 820, 20, 1, 1, "F");

	// Uptown Blocks - bottom
	drawBlock (widget, 20, 160, 0, 1, "G");
	drawBlock (widget, 180, 160, 0, 1, "H");
	drawBlock (widget, 340, 160, 0, 1, "I");
	drawBlock (widget, 500, 160, 0, 1, "J");
	drawBlock (widget, 660, 160, 0, 1, "K");
	drawBlock (widget, 820, 160, 0, 1, "L");

	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, border_width+unit, 280, 920, 20);

	// Central Lines
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+unit, 320, window_width-border_width-unit, 320);
	gdk_draw_line(this.pixMap, widget->style->bg_gc[0], border_width+unit, 340, window_width-border_width-unit, 340);
	gdk_draw_line(this.pixMap, widget->style->fg_gc[0], border_width+unit, 360, window_width-border_width-unit, 360);

	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, border_width+unit, 380, 920, 20);

	// Downtonw Blocks - top
	drawBlock (widget, 20, 400, 1, 0, "M");
	drawBlock (widget, 180, 400, 1, 0, "N");
	drawBlock (widget, 340, 400, 1, 0, "O");
	drawBlock (widget, 500, 400, 1, 0, "P");
	drawBlock (widget, 660, 400, 1, 0, "Q");
	drawBlock (widget, 820, 400, 1, 0, "R");

	// Downtonw Blocks - bottom
	drawBlock (widget, 20, 540, 1, 1, "S");
	drawBlock (widget, 180, 540, 1, 1, "T");
	drawBlock (widget, 340, 540, 1, 1, "U");
	drawBlock (widget, 500, 540, 1, 1, "V");
	drawBlock (widget, 660, 540, 1, 1, "W");
	drawBlock (widget, 820, 540, 1, 1, "X");

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

	// Rotondas Y
	gdk_draw_arc(this.pixMap, widget->style->black_gc, TRUE, 0, 280, 120, 120, 0, 360*64);
	gdk_draw_arc(this.pixMap, widget->style->bg_gc[0], TRUE, 20, 300, 80, 80, 0, 360*64);
	gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-300-*-*-*-*-iso8859-1"), widget->style->black_gc, 50, 355, "Y");

	// Rotondas Z
	gdk_draw_arc(this.pixMap, widget->style->black_gc, TRUE, border_width+canvas_width-unit*2, 280, 120, 120, 0, 360*64);
	gdk_draw_arc(this.pixMap, widget->style->bg_gc[0], TRUE, border_width+canvas_width-unit, 300, 80, 80, 0, 360*64);
	gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-300-*-*-*-*-iso8859-1"), widget->style->black_gc, border_width+canvas_width+10, 355, "Z");
}


/* --------------------------- EVENTS --------------------------- */

void gtk_expose_event (GtkWidget *widget, GdkEventExpose *event) {
	gdk_draw_drawable(widget->window, 
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)], 
			this.pixMap, 
			event->area.x, event->area.y,
			event->area.x, event->area.y,
			event->area.width, event->area.height);

	//drawThreadville(widget);
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

gboolean loop (GtkWidget *window) {
	 printf("Loop\n");
	//static gboolean first_execution = TRUE;

	// use a safe function to get the value of currently_drawing
    //int drawing_status = g_atomic_int_get(&currently_drawing);

    //if we are not currently drawing anything, launch a thread to 
    //update our pixmap
    /*if(drawing_status == 0){
        static pthread_t thread_info;
        int  iret;
        if(first_execution != TRUE){
            pthread_join(thread_info, NULL);
        }
        iret = pthread_create( &thread_info, NULL, do_draw, NULL);
    }*/

    //tell our drawing area it is time to draw our animation.
    int width, height;
    gdk_drawable_get_size(this.pixMap, &width, &height);
    gtk_widget_queue_draw_area(this.drawingArea, 0, 0, width, height);

    //first_execution = FALSE;

    return TRUE;

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

    //we can turn off gtk's automatic painting and double buffering routines.
    gtk_widget_set_app_paintable(this.drawingArea, TRUE);
    gtk_widget_set_double_buffered(this.drawingArea, FALSE);

    (void)g_timeout_add(100, (GSourceFunc)loop, this.drawingArea);

    gint y = 220;
    int i = 0;
    for (i; i < 5; ++i)
    {
    	printf("Pthread\n");
	    pthread_t hThread;
	   	struct readThreadParams readParams;
	    readParams.car.x = border_width+5;
	    readParams.car.y = y;
	    readParams.car.width = 10;
		readParams.car.height = 15;
	    int iret = pthread_create (&hThread, NULL, do_draw, &readParams);
	    if (iret) {
	    	pthread_join(hThread, NULL);
	    }
	    y = y - 20;
    }

    gtk_main();

    /*drawCar(border_width+5, 200);
    sleep(2);
    drawCar(border_width+5, 180);
	sleep(2);
    drawCar(border_width+5, 160);
    sleep(2);
    drawCar(border_width+5, 140);
    sleep(2);*/
    //struct readThreadParams readParams2;
    //readParams2.car.x = border_width+5;
    //readParams2.car.y = 140;
    //readParams2.car.width = 10;
	//readParams2.car.height = 15;
    //pthread_t hThread2;
    //pthread_create (&hThread2, NULL, loop, &readParams2);
}