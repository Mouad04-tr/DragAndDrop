#ifndef UTILS_H
#define UTILS_H

#include <gtk/gtk.h>

void load_css(const char* css_file_path);
GtkWidget* Creer_fenetre(const char* title, int width, int height);
void Ajuster_fenetre(GtkWidget* window, GtkWidget** scrolled_window, GtkWidget** main_box, GtkWidget** right_fixed, GtkWidget** left_box);

#endif // UTILS_H
