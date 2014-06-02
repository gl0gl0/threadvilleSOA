#include "global.h"
#include "events.h"
#include "../Threadville.h"

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

	gboolean is_auto = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(carModeCheck));

	if (is_auto) {
		const gchar *entryText;
		int i, j;
		j = 0;
		entryText = gtk_entry_get_text(GTK_ENTRY(carPathInput));
		for (i=0; i<strlen(entryText); i++){
			if (entryText[i] == 44)
				j++;
		}
		j++;

		int color;
		color = gtk_combo_box_get_active (GTK_COMBO_BOX(carTypeCombo)) + 1;

		autos[indiceCarro] = (automovil *) malloc(sizeof(automovil));
		autos[indiceCarro]->color = color;
		if (j < 2)
			autos[indiceCarro]->viajes = 2;
		else
			autos[indiceCarro]->viajes = j;
		autos[indiceCarro]->destino = (int *) malloc(sizeof(int) * autos[indiceCarro]->viajes);
		autos[indiceCarro]->velocidad = color * 19000 + 3000 * (color -1);
		if (j>1){
			const char s[2] = ",";
			char *token;
			token = strtok(entryText, s);
			j = 0;
			while( token != NULL )  {
				autos[indiceCarro]->destino[j] = convertToken(token);
				token = strtok(NULL, s);
			}
			autos[indiceCarro]->posicion = autos[indiceCarro]->destino[0]; 
		}else{
			int r;
			r = rand() % 714;
			autos[indiceCarro]->posicion = autos[indiceCarro]->destino[0] = r;
			r = rand() % 714;
			autos[indiceCarro]->destino[1] = r;
		}
		generarCarro(autos[indiceCarro++]);

		// TODO create car with this specific params
	} else {
		// TODO create car random parameters
	}
}
	

void generate_ambulance_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Generate ambulance pressed: %s \n", (char *)data);

	gboolean is_auto = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ambulanceModeCheck));

	if (is_auto) {
		const gchar *entryText;
		char copy[100];
		const char s[2] = ",";
		char *token;

		entryText = gtk_entry_get_text(GTK_ENTRY(ambulancePathInput));
		g_print("Path: %s \n", (char *)entryText);

		// TODO create ambulance with this specific params
	} else {
		// TODO create ambulance random parameters
	}
}

void red_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(redBusModeCheck));
	if (is_enabled) {
		// Activar bus
		g_print("enabled");
	} else {
		// Desactivar bus
		g_print("disabled");
	}
}

void green_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(greenBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void blue_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blueBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void white_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(whiteBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void gray_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(grayBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void black_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blackBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void lightblue_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lightBlueBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void pink_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pinkBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void orange_bus_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orangeBusModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void all_buses_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(allBusesModeCheck));
	if (is_enabled) {
		gtk_toggle_button_set_active((GtkToggleButton*) redBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) greenBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) blueBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) whiteBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) grayBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) blackBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) lightBlueBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) pinkBusModeCheck, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) orangeBusModeCheck, TRUE);

		// Activar bus
	} else {
		gtk_toggle_button_set_active((GtkToggleButton*) redBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) greenBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) blueBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) whiteBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) grayBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) blackBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) lightBlueBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) pinkBusModeCheck, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) orangeBusModeCheck, FALSE);

		// Desactivar bus
	}
}

void obstacles_checkbox_callback_event (GtkWidget *widget, gpointer data) {
	gboolean is_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(obstaclesModeCheck));
	if (is_enabled) {
		// Activar bus
	} else {
		// Desactivar bus
	}
}

void stop_simulation_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Stop simulation pressed: %s \n", (char *)data);
	simular = 0;
}

void start_simulation_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Start simulation pressed\n");
	simular = 1;
	
	/* BUS ROJO */
	BusRojo = (automovil *) malloc(sizeof(automovil));
	BusRojo->viajes = 13;
	BusRojo->destino = (int*) malloc(sizeof(int) * BusRojo->viajes);
	BusRojo->posicion = BusRojo->destino[0] = 9;
	BusRojo->destino[1] = 93;
	BusRojo->destino[2] = 152;
	BusRojo->destino[3] = 238;
	BusRojo->destino[4] = 694;
	BusRojo->destino[5] = 307;
	BusRojo->destino[6] = 475;
	BusRojo->destino[7] = 368+23;
	BusRojo->destino[8] = 338;
	BusRojo->destino[9] = 244;
	BusRojo->destino[10] = 674;
	BusRojo->destino[11] = 173;
	BusRojo->destino[12] = 9;
	BusRojo->color = 1;
	BusRojo->velocidad = 5 * 19000 + 3000 * (5 - 1);
	BusRojo->destinoActual = 1;
	generarCarro(BusRojo);
	pthread_detach(BusRojo->hilo);
	
	/* BUS VERDE */
	BusVerde = (automovil *) malloc(sizeof(automovil));
	BusVerde->viajes = 7;
	BusVerde->destino = (int*) malloc(sizeof(int) * BusVerde->viajes);
	BusVerde->posicion = BusVerde->destino[0] = 124;
	BusVerde->destino[1] = 228 + 7;
	BusVerde->destino[2] = 694;
	BusVerde->destino[3] = 674;
	BusVerde->destino[4] = 168 + 5;
	BusVerde->destino[5] = 28 + 9;
	BusVerde->destino[6] = 112 + 12;
	BusVerde->color = 3;
	BusVerde->velocidad = 5 * 19000 + 3000 * (5 - 1);
	BusVerde->destinoActual = 1;
	generarCarro(BusVerde);
	pthread_detach(BusVerde->hilo);

	int i;
	for (i=0; i<indiceCarro; i++)
		pthread_detach(autos[i]->hilo);
}
