// TextView.cpp

#include "TextView.h"

TextView::TextView() {
    // Create a default button
    m_fixed = gtk_button_new_with_label("Create a TextView");
}

TextView::TextView(GtkWidget* parent) {
    // Create a fixed container
    m_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(parent), m_fixed);

    // Create a left text view button
    GtkWidget* left_button = gtk_button_new_with_label("Left Text View");
    g_signal_connect(left_button, "clicked", G_CALLBACK(on_left_text_view_button_clicked), m_fixed);
    gtk_fixed_put(GTK_FIXED(m_fixed), left_button, 10, 10);
    gtk_widget_show_all(m_fixed);
}


GtkWidget* TextView::getWidget() const {
    return m_fixed;
}

TextView::~TextView() {
    // Free resources
    g_object_unref(m_fixed);
}

gboolean TextView::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        ButtonMoveData* move_data = (ButtonMoveData*)data;

        // Obtenir l'allocation du widget
        GtkAllocation allocation;
        gtk_widget_get_allocation(widget, &allocation);

        move_data->offset_x = event->x_root - allocation.x;
        move_data->offset_y = event->y_root - allocation.y;
        move_data->button_pressed = TRUE; // Indique que le bouton de la souris est enfoncé
        return TRUE; // Évitez d'envoyer l'événement à d'autres gestionnaires
    }
    return FALSE;
}

gboolean TextView::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        ButtonMoveData* move_data = (ButtonMoveData*)data;
        move_data->button_pressed = FALSE; // Indique que le bouton de la souris est relâché
        return TRUE; // Évitez d'envoyer l'événement à d'autres gestionnaires
    }
    return FALSE;
}

gboolean TextView::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    ButtonMoveData* move_data = (ButtonMoveData*)data;

    if (move_data->button_pressed) {
        // Calcule la nouvelle position du bouton en fonction du mouvement de la souris
        gint new_x = event->x_root - move_data->offset_x;
        gint new_y = event->y_root - move_data->offset_y;

        // Déplace le bouton à la nouvelle position
        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);
    }

    return TRUE; // Évitez d'envoyer l'événement à d'autres gestionnaires
}

void TextView::on_left_text_view_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Create a scrolled window
    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window, 200, 100); // Adjust size as necessary

    // Create the text view
    GtkWidget* text_view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Create an event box to wrap the scrolled window for dragging
    GtkWidget* event_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(event_box), scrolled_window);
    gtk_widget_show_all(scrolled_window); // Ensure all widgets inside the event box are visible

    // Setup for draggable
    ButtonMoveData* move_data = g_new0(ButtonMoveData, 1);
    move_data->widget = event_box;

    // Connect the mouse events to allow dragging the event box
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(event_box, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Add the event box (with the scrolled window and text view inside) to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), event_box, 20, 30); // Adjust position as necessary
    gtk_widget_show_all(event_box);
}
