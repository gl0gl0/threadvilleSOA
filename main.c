#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <gtk/gtk.h>

#include "ui.h"
#include "main.h"

/* main
 * Initializes the program
 * 
 * @param int argc
 * @param char*[] argv
 *
 * @return success/failure
 */
int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	initUI();

    return EXIT_SUCCESS;
}