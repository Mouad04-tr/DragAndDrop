#include "Button.h"

Button::Button(const char* label) {
    widget = gtk_button_new_with_label(label);
}

GtkWidget* Button::getWidget() {
    return widget;
}

void Button::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        SButtonMoveData* move_data = (SButtonMoveData*)data;
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        gdk_window_raise(gtk_widget_get_window(widget));
        gtk_grab_add(widget);
    }
}

gboolean Button::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    SButtonMoveData* move_data = (SButtonMoveData*)data;

    if (event->state & GDK_BUTTON1_MASK) { // Vérifie si le bouton de la souris est toujours enfoncé
        gint new_x = event->x_root - move_data->offset_x;
        gint new_y = event->y_root - move_data->offset_y;

        // Déplace le bouton à la nouvelle position
        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);
    }

    return TRUE; // Évitez d'envoyer l'événement à d'autres gestionnaires
}
void Button::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        gtk_grab_remove(widget);
    }
}

void Button::on_left_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créer un bouton
    Button* button = new Button("Button");
    GtkWidget* normal_button = button->getWidget();
    gtk_container_add(GTK_CONTAINER(fixed), normal_button);

    // Setup for draggable
    SButtonMoveData* move_data = new SButtonMoveData;
    move_data->widget = normal_button;

    // Connect the mouse events to allow dragging the normal button
    g_signal_connect(normal_button, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(normal_button, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(normal_button, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Afficher le bouton normal
    gtk_widget_show_all(normal_button);
}
