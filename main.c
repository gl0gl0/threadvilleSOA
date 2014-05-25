#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <gtk/gtk.h>

#include "UI/ui.h"

/* main
 * Initializes the program
 * 
 * @param int argc
 * @param char*[] argv
 *
 * @return success/failure
 */
int main(int argc, char *argv[]) {
	//we need to initialize all these functions so that gtk knows
    //to be thread-aware
    if (!g_thread_supported ()){ g_thread_init(NULL); }
    gdk_threads_init();
    gdk_threads_enter();

	gtk_init(&argc, &argv);
	initUI();

	gdk_threads_leave();

    return EXIT_SUCCESS;
}