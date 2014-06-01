#include <pthread.h>

#include "global.h"
#include "events.h"
#include "ui.h"
#include "../Threadville.h"

static int currently_drawing = 0;

gint window_width = 1120;
gint window_height = 800;
gint border_width = borderwidth;
gint canvas_width = 960;
gint canvas_height = 680;

gint unit = 20;

/* --------------------------- DRAWING METHODS --------------------------- */

/* drawCar
 * Draws a car
 *
 * @return void
 */
void drawCar (gint x, gint y, gint width, gint height) {
	GdkRectangle car;

	car.x = x;
	car.y = y;
	car.width = width;
	car.height = height;
	gdk_draw_rectangle(this.pixMap, this.drawingArea->style->white_gc, TRUE, car.x, car.y, car.width, car.height);
	gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-50-*-*-*-*-iso8859-1"), this.drawingArea->style->black_gc, (car.x+2), (car.y+10), "A1/5");

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
	if (upper) {
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+20), y, 20, 20);
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+28), (y+16), "1");
	}
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, x, (y+20), 20, 20);
	if (!lower) {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+8), (y+36), "6");
	} else if (!upper) {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+8), (y+36), "1");
	} else {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+8), (y+36), "8");
	}

	// Lower left
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, x, (y+80), 20, 20);
	if (!lower) {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+8), (y+96), "5");
	} else if (!upper) {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+8), (y+96), "6");
	} else {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+8), (y+96), "7");
	}

	if (lower) {
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+20), (y+100), 20, 20);
		if (!upper) {
			gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+28), (y+116), "5");
		} else {
			gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+28), (y+116), "6");
		}
	}
	// Upper right
	if (upper) {
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+80), y, 20, 20);
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+88), (y+16), "2");
	}
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+100), (y+20), 20, 20);
	if (!upper) {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+108), (y+36), "2");
	} else {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+108), (y+36), "3");
	}

	// Lower right
	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+100), (y+80), 20, 20);
	if (!upper) {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+108), (y+96), "3");		
	} else {
		gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+108), (y+96), "4");
	}
	
	if (lower) {
		gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, (x+80), (y+100), 20, 20);
		if (!upper) {
			gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+88), (y+116), "4");
		} else {
			gdk_draw_string(this.pixMap, gdk_font_load("-*-*-bold-r-normal--*-100-*-*-*-*-iso8859-1"), widget->style->black_gc, (x+88), (y+116), "5");
		}
	}

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
	gdk_draw_rectangle(this.pixMap, widget->style->bg_gc[0], TRUE, border_width, 0, canvas_width, canvas_height);

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



/* --------------------------- CONTROL METHODS --------------------------- */

/* createDrawingArea
 * Creates the main drawing area
 *
 * @return void
 */
void createDrawingArea () {
	// Background color
	GdkColor color;
	gdk_color_parse("#458B00", &color);

	// Creates drawing area with the specified dimensions and background color
	this.drawingArea = gtk_drawing_area_new();
	gtk_drawing_area_size((GtkDrawingArea*) this.drawingArea, canvas_width, canvas_height);
	gtk_widget_modify_bg((GtkWidget*) this.drawingArea, GTK_STATE_NORMAL, &color);
	gdk_color_parse("#FFA824", &color);
	gtk_widget_modify_fg((GtkWidget*) this.drawingArea, GTK_STATE_NORMAL, &color);

	// Attach events to the drawing area
	gtk_signal_connect((GtkObject*) this.drawingArea, "expose_event", G_CALLBACK(gtk_expose_event), NULL);
	gtk_signal_connect((GtkObject*) this.drawingArea, "configure_event", G_CALLBACK(gtk_configure_event), NULL);

	gtk_container_add((GtkContainer*) this.vbox, this.drawingArea);
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

	/* Principal vbox */
	this.vbox = gtk_vbox_new(FALSE, 10);
	GtkWidget *valign = gtk_alignment_new(0, 1, 0, 0);
	gtk_container_add((GtkContainer*) this.vbox, valign);
	gtk_container_add((GtkContainer*) this.mainWindow, this.vbox);

	/* Parameters Frame */
	GtkWidget *parametersFrame = gtk_frame_new("Parámetros de Ejecucion");
	gtk_frame_set_shadow_type((GtkFrame*) parametersFrame, GTK_SHADOW_ETCHED_IN);
	GtkWidget *parametersTable = gtk_table_new(3, 8, FALSE);
	gtk_table_set_row_spacings((GtkTable*) parametersTable, 5);
	gtk_table_set_col_spacings((GtkTable*) parametersTable, 5);
	
	//Generate car
	GtkWidget *generateCarBtn = gtk_button_new_with_label("Generar carro");
	gtk_table_attach_defaults((GtkTable*) parametersTable, generateCarBtn, 0,1,0,1);
	gtk_signal_connect(GTK_OBJECT(generateCarBtn), "clicked", GTK_SIGNAL_FUNC(generate_car_callback_event), NULL);
	carPathInput = gtk_entry_new();
	gtk_entry_set_text((GtkEntry*) carPathInput, "e.g., A1, B1, C2, C5");
	gtk_table_attach_defaults((GtkTable*) parametersTable, carPathInput, 1,2,0,1);
	carTypeCombo = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(carTypeCombo), "Rojo");
	gtk_combo_box_append_text(GTK_COMBO_BOX(carTypeCombo), "Azul");
	gtk_combo_box_append_text(GTK_COMBO_BOX(carTypeCombo), "Verde");
	gtk_combo_box_append_text(GTK_COMBO_BOX(carTypeCombo), "Negro");
	gtk_combo_box_append_text(GTK_COMBO_BOX(carTypeCombo), "Blanco");
	gtk_combo_box_append_text(GTK_COMBO_BOX(carTypeCombo), "Amarillo");
	gtk_combo_box_set_active(GTK_COMBO_BOX(carTypeCombo), RED);
	gtk_table_attach_defaults((GtkTable*) parametersTable, carTypeCombo, 2,3,0,1);
	carModeCheck = gtk_check_button_new_with_label("auto");
	gtk_table_attach_defaults((GtkTable*) parametersTable, carModeCheck, 3,4,0,1);
	gtk_toggle_button_set_active((GtkToggleButton*) carModeCheck, TRUE);

	// Generate Ambulance
	GtkWidget *generateAmbulanceBtn = gtk_button_new_with_label("Generar Ambulancia");
	gtk_table_attach_defaults((GtkTable*) parametersTable, generateAmbulanceBtn, 4,5,0,1);
	gtk_signal_connect(GTK_OBJECT(generateAmbulanceBtn), "clicked", GTK_SIGNAL_FUNC(generate_ambulance_callback_event), NULL);
	ambulancePathInput = gtk_entry_new();
	gtk_entry_set_text((GtkEntry*) ambulancePathInput, "e.g., A1, B1, C2, C5");
	gtk_table_attach_defaults((GtkTable*) parametersTable, ambulancePathInput, 5,6,0,1);
	ambulanceModeCheck = gtk_check_button_new_with_label("auto");
	gtk_table_attach_defaults((GtkTable*) parametersTable, ambulanceModeCheck, 6,7,0,1);
	gtk_toggle_button_set_active((GtkToggleButton*) ambulanceModeCheck, TRUE);

	// Buses
	redBusModeCheck = gtk_check_button_new_with_label("Bus Rojo");
	gtk_table_attach_defaults((GtkTable*) parametersTable, redBusModeCheck, 0,1,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) redBusModeCheck, TRUE);
	greenBusModeCheck = gtk_check_button_new_with_label("Bus Verde");
	gtk_table_attach_defaults((GtkTable*) parametersTable, greenBusModeCheck, 1,2,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) greenBusModeCheck, TRUE);
	blueBusModeCheck = gtk_check_button_new_with_label("Bus Azul");
	gtk_table_attach_defaults((GtkTable*) parametersTable, blueBusModeCheck, 2,3,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) blueBusModeCheck, TRUE);
	whiteBusModeCheck = gtk_check_button_new_with_label("Bus Blanco");
	gtk_table_attach_defaults((GtkTable*) parametersTable, whiteBusModeCheck, 3,4,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) whiteBusModeCheck, TRUE);
	grayBusModeCheck = gtk_check_button_new_with_label("Bus Gris");
	gtk_table_attach_defaults((GtkTable*) parametersTable, grayBusModeCheck, 4,5,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) grayBusModeCheck, TRUE);
	blackBusModeCheck = gtk_check_button_new_with_label("Bus Negro");
	gtk_table_attach_defaults((GtkTable*) parametersTable, blackBusModeCheck, 5,6,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) blackBusModeCheck, TRUE);
	lightBlueBusModeCheck = gtk_check_button_new_with_label("Bus Celeste");
	gtk_table_attach_defaults((GtkTable*) parametersTable, lightBlueBusModeCheck, 6,7,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) lightBlueBusModeCheck, TRUE);
	pinkBusModeCheck = gtk_check_button_new_with_label("Bus Rosa");
	gtk_table_attach_defaults((GtkTable*) parametersTable, pinkBusModeCheck, 7,8,1,2);
	gtk_toggle_button_set_active((GtkToggleButton*) pinkBusModeCheck, TRUE);

	orangeBusModeCheck = gtk_check_button_new_with_label("Bus Naranja");
	gtk_table_attach_defaults((GtkTable*) parametersTable, orangeBusModeCheck, 0,1,2,3);
	gtk_toggle_button_set_active((GtkToggleButton*) orangeBusModeCheck, TRUE);
	allBusesModeCheck = gtk_check_button_new_with_label("Todos los Buses");
	gtk_table_attach_defaults((GtkTable*) parametersTable, allBusesModeCheck, 1,2,2,3);
	gtk_toggle_button_set_active((GtkToggleButton*) allBusesModeCheck, TRUE);
	obstaclesModeCheck = gtk_check_button_new_with_label("Obstaculos");
	gtk_table_attach_defaults((GtkTable*) parametersTable, obstaclesModeCheck, 2,3,2,3);
	gtk_toggle_button_set_active((GtkToggleButton*) obstaclesModeCheck, TRUE);

	// Start/Finish
	GtkWidget *stopBtn = gtk_button_new_with_label("Terminar");
	gtk_table_attach_defaults((GtkTable*) parametersTable, stopBtn, 6,7,2,3);
	gtk_signal_connect(GTK_OBJECT(stopBtn), "clicked", GTK_SIGNAL_FUNC(stop_simulation_callback_event), NULL);
	GtkWidget *startBtn = gtk_button_new_with_label("Simular");
	gtk_table_attach_defaults((GtkTable*) parametersTable, startBtn, 7,8,2,3);
	gtk_signal_connect(GTK_OBJECT(startBtn), "clicked", GTK_SIGNAL_FUNC(start_simulation_callback_event), NULL);
	
	gtk_container_add((GtkContainer*) parametersFrame, parametersTable);
	gtk_box_pack_start((GtkBox*) this.vbox, parametersFrame, FALSE, FALSE, 0);

	// Attach close event to the window
	gtk_signal_connect((GtkObject*) this.mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

gboolean loop (GtkWidget *window) {
	 //printf("Loop\n");

    int width, height;
    gdk_drawable_get_size(this.pixMap, &width, &height);
    gtk_widget_queue_draw_area(this.drawingArea, 0, 0, width, height);

    return TRUE;

}

/* display
 * Shows all elements, in order
 *
 * @return void
 */
void display () {
	gtk_widget_show(this.drawingArea);
	gtk_widget_show_all(this.mainWindow);
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

    (void)g_timeout_add(30, (GSourceFunc)loop, this.drawingArea);
    
    int i;
	for (i=0; i<N; i++)
		Threadville[i] = 0;
	init();
	srand(time(NULL));
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);

	for (i=0; i<M; i++){
		autos[i] = (automovil *) malloc(sizeof(automovil));
		autos[i]->color = i;
		generarCarro(autos[i]);
	}
	for (i=0; i<M; i++)
		pthread_detach(autos[i]->hilo);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&lock);
	printf("\n");

    gtk_main();
}
