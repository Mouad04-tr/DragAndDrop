#include "RadioButton.h"

RadioButton::RadioButton() {
    radiobutton = gtk_button_new_with_label("Create a radio button");
}

RadioButton::RadioButton(const char* label) {
    radiobutton = gtk_radio_button_new(NULL);
    gtk_button_set_label(GTK_BUTTON(radiobutton), label);
}

GtkWidget* RadioButton::getWidget() {
    return radiobutton;
}

void RadioButton::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        RadioMoveData* move_data = (RadioMoveData*)data;
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        gdk_window_raise(gtk_widget_get_window(widget));
        gtk_grab_add(widget);
    }
}

void RadioButton::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        gtk_grab_remove(widget);
    }
}

gboolean RadioButton::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    RadioMoveData* move_data = (RadioMoveData*)data;

    // Calcule la nouvelle position du bouton en fonction du mouvement de la souris
    gint new_x = event->x_root - move_data->offset_x;
    gint new_y = event->y_root - move_data->offset_y;

    gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);

    return TRUE; // Évitez d'envoyer l'événement à d'autres gestionnaires
}

void RadioButton::on_left_radio_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créer un bouton radio
    RadioButton radio("Radio Button");
    GtkWidget* radio_button = radio.getWidget();
    gtk_container_add(GTK_CONTAINER(fixed), radio_button);

    // Setup for draggable
    RadioMoveData* move_data = g_new0(RadioMoveData, 1);
    move_data->widget = radio_button;

    // Connect the mouse events to allow dragging the radio button
    g_signal_connect(radio_button, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(radio_button, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(radio_button, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Afficher le bouton radio
    gtk_widget_show_all(radio_button);
}
