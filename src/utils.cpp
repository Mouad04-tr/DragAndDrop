#include <gtk/gtk.h>
#include "utils.h"

void load_css(const char* css_file_path) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, css_file_path, NULL);
    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

GtkWidget* Creer_fenetre(const char* title, int width, int height) {
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkStyleContext *windowContext = gtk_widget_get_style_context(window);
    gtk_style_context_add_class(windowContext, "window");

    return window;
}

void Ajuster_fenetre(GtkWidget* window, GtkWidget** scrolled_window, GtkWidget** main_box, GtkWidget** right_fixed, GtkWidget** left_box) {
    *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(*scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(window), *scrolled_window);

    *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_container_add(GTK_CONTAINER(*scrolled_window), *main_box);

    *right_fixed = gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(*main_box), *right_fixed, TRUE, TRUE, 0);

    *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_box_pack_start(GTK_BOX(*main_box), *left_box, FALSE, FALSE, 0);
}
