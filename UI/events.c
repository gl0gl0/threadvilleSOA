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

	gboolean is_auto = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(carModeCheck));

	if (is_auto) {
		const gchar *entryText;
		char copy[100];
		const char s[2] = ",";
		char *token;

		entryText = gtk_entry_get_text(GTK_ENTRY(carPathInput));
		g_print("Path: %s \n", (char *)entryText);

		enum CarType carType = gtk_combo_box_get_active (GTK_COMBO_BOX(carTypeCombo));

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
}

void start_simulation_callback_event (GtkWidget *widget, gpointer data) {
	g_print("Start simulation pressed: %s \n", (char *)data);
}
