#include "CheckButton.h"
#include "CheckButton.h"

CheckButton::CheckButton() {
    checkbutton = gtk_button_new_with_label("Create a checkBoxButton"); // Utiliser gtk_check_button_new pour créer un bouton de case à cocher
}

CheckButton::CheckButton(const char* label) {
    checkbutton = gtk_check_button_new_with_label(label); // Utiliser gtk_check_button_new_with_label pour créer un bouton de case à cocher avec un libellé
}

GtkWidget* CheckButton::getWidget() {
    return checkbutton;
}

CheckButton::~CheckButton() {
}



void CheckButton::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        CheckButtonMoveData* move_data = (CheckButtonMoveData*)data;
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        gdk_window_raise(gtk_widget_get_window(widget));
        gtk_grab_add(widget);
    }
}


gboolean CheckButton::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        gtk_grab_remove(widget);
    }
}

gboolean CheckButton::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    CheckButtonMoveData* move_data = (CheckButtonMoveData*)data;

    // Calcule la nouvelle position du bouton en fonction du mouvement de la souris
    gint new_x = event->x_root - move_data->offset_x;
    gint new_y = event->y_root - move_data->offset_y;

    gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);

    return TRUE; // Évitez d'envoyer l'événement à d'autres gestionnaires
}

void CheckButton::on_left_check_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créer un bouton de case à cocher avec un libellé approprié
    CheckButton check("Check Button");
    GtkWidget* check_button = check.getWidget(); // Utilise le constructeur qui crée un bouton de case à cocher
    gtk_container_add(GTK_CONTAINER(fixed), check_button); // Ajoute le bouton de case à cocher dans le conteneur

    // Setup for draggable
    CheckButtonMoveData* move_data = g_new0(CheckButtonMoveData, 1);
    move_data->widget = check_button;

    // Connect the mouse events to allow dragging the check button
    g_signal_connect(check_button, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(check_button, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(check_button, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Afficher le bouton de case à cocher
    gtk_widget_show_all(check_button);
}
