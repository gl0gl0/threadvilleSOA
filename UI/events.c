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
		autos[indiceCarro]->tipo = 0;
		int rviajes;
			rviajes = rand() % 6 + 2;
		if (j < 2)
			autos[indiceCarro]->viajes = rviajes;
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
				autos[indiceCarro]->destino[j++] = convertToken(token);
				token = strtok(NULL, s);
			}
			autos[indiceCarro]->posicion = autos[indiceCarro]->destino[0]; 
		}else{
			int r, lk;
			for (lk=0; lk<rviajes; lk++){ 
				r = rand() % 714;
				autos[indiceCarro]->posicion = autos[indiceCarro]->destino[lk] = r;
			}
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
		NOBUSES=0;
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
		NOBUSES=1;
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
	if (!NOBUSES){
	
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
		BusRojo->destino[11] = 169;
		BusRojo->destino[12] = 9;
		BusRojo->color = 1;
		BusRojo->tipo = 2;
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
		BusVerde->destino[4] = 172;
		BusVerde->destino[5] = 28 + 9;
		BusVerde->destino[6] = 112 + 12;
		BusVerde->color = 3;
		BusVerde->tipo = 2;
		BusVerde->velocidad = 5 * 19000 + 3000 * (5 - 1);
		BusVerde->destinoActual = 1;
		generarCarro(BusVerde);
		pthread_detach(BusVerde->hilo);
		
		/* BUS AZUL */
		BusAzul = (automovil *) malloc(sizeof(automovil));
		BusAzul->viajes = 7;
		BusAzul->destino = (int*) malloc(sizeof(int) * BusAzul->viajes);
		BusAzul->posicion = BusAzul->destino[0] = 310;
		BusAzul->destino[1] = 447;
		BusAzul->destino[2] = 366;
		BusAzul->destino[3] = 241;
		BusAzul->destino[4] = 674;
		BusAzul->destino[5] = 694;
		BusAzul->destino[6] = 310;
		BusAzul->color = 2;
		BusAzul->tipo = 2;
		BusAzul->velocidad = 5 * 19000 + 3000 * (5 - 1);
		BusAzul->destinoActual = 1;
		generarCarro(BusAzul);
		pthread_detach(BusAzul->hilo);

		/* BUS BLANCO */
		BusBlanco = (automovil *) malloc(sizeof(automovil));
		BusBlanco->viajes = 7;
		BusBlanco->destino = (int*) malloc(sizeof(int) * BusBlanco->viajes);
		BusBlanco->posicion = BusBlanco->destino[0] = 202;
		BusBlanco->destino[1] = 274;
		BusBlanco->destino[2] = 363;
		BusBlanco->destino[3] = 256;
		BusBlanco->destino[4] = 185;
		BusBlanco->destino[5] = 65;
		BusBlanco->destino[6] = 202;
		BusBlanco->color = 5;
		BusBlanco->tipo = 2;
		BusBlanco->velocidad = 4 * 19000 + 3000 * (4 - 1);
		BusBlanco->destinoActual = 1;
		generarCarro(BusBlanco);
		pthread_detach(BusBlanco->hilo);

		/* BUS GRIS */
		BusGris = (automovil *) malloc(sizeof(automovil));
		BusGris->viajes = 7;
		BusGris->destino = (int*) malloc(sizeof(int) * BusGris->viajes);
		BusGris->posicion = BusGris->destino[0] = 368+23;
		BusGris->destino[1] = 268;
		BusGris->destino[2] = 196;
		BusGris->destino[3] = 93;
		BusGris->destino[4] = 214;
		BusGris->destino[5] = 286;
		BusGris->destino[6] = 368+23;
		BusGris->color = 10;
		BusGris->tipo = 2;
		BusGris->velocidad = 4 * 19000 + 3000 * (4 - 1);
		BusGris->destinoActual = 1;
		generarCarro(BusGris);
		pthread_detach(BusGris->hilo);

		/* BUS NEGRO */
		BusNegro = (automovil *) malloc(sizeof(automovil));
		BusNegro->viajes = 7;
		BusNegro->destino = (int*) malloc(sizeof(int) * BusNegro->viajes);
		BusNegro->posicion = BusNegro->destino[0] = 208;
		BusNegro->destino[1] = 121;
		BusNegro->destino[2] = 226;
		BusNegro->destino[3] = 295;
		BusNegro->destino[4] = 396+23;
		BusNegro->destino[5] = 280;
		BusNegro->destino[6] = 208;
		BusNegro->color = 4;
		BusNegro->tipo = 2;
		BusNegro->velocidad = 4 * 19000 + 3000 * (4 - 1);
		BusNegro->destinoActual = 1;
		generarCarro(BusNegro);
		pthread_detach(BusNegro->hilo);

		/* BUS ROSA */
		BusRosa = (automovil *) malloc(sizeof(automovil));
		BusRosa->viajes = 5;
		BusRosa->destino = (int*) malloc(sizeof(int) * BusRosa->viajes);
		BusRosa->posicion = BusRosa->destino[0] = 163;
		BusRosa->destino[1] = 26;
		BusRosa->destino[2] = 9;
		BusRosa->destino[3] = 152;
		BusRosa->destino[4] = 163;
		BusRosa->color = 8;
		BusRosa->tipo = 2;
		BusRosa->velocidad = 3 * 19000 + 3000 * (3 - 1);
		BusRosa->destinoActual = 1;
		generarCarro(BusRosa);
		pthread_detach(BusRosa->hilo);

		/* BUS CELESTE */
		BusCeleste = (automovil *) malloc(sizeof(automovil));
		BusCeleste->viajes = 5;
		BusCeleste->destino = (int*) malloc(sizeof(int) * BusCeleste->viajes);
		BusCeleste->posicion = BusCeleste->destino[0] = 338;
		BusCeleste->destino[1] = 321;
		BusCeleste->destino[2] = 464;
		BusCeleste->destino[3] = 475;
		BusCeleste->destino[4] = 338;
		BusCeleste->color = 9;
		BusCeleste->tipo = 2;
		BusCeleste->velocidad = 3 * 19000 + 3000 * (3 - 1);
		BusCeleste->destinoActual = 1;
		generarCarro(BusCeleste);
		pthread_detach(BusCeleste->hilo);

	}

	int i;
	for (i=0; i<indiceCarro; i++)
		pthread_detach(autos[i]->hilo);
}
