#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "events.h"
#include "global.h"

void gtk_configure_event (GtkWidget *widget, GdkEventConfigure *event) {
	if (this.pixMap)
		g_object_unref(this.pixMap);

	this.pixMap = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);

	gdk_draw_rectangle(this.pixMap, widget->style->white_gc, TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
}