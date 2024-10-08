#include "SpinButton.h"

SpinButton::SpinButton() {
    widget = gtk_button_new_with_label("Create Spin Button");
}

SpinButton::~SpinButton() {
    // Libérer les ressources si nécessaire
}

GtkWidget* SpinButton::getWidget() const {
    return widget;
}

void SpinButton::on_left_spin_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Create the spin button
    GtkWidget* spin_button = gtk_spin_button_new_with_range(0, 100, 1);

    // Connect the "change-value" signal to handle changes in value
    GtkAdjustment* adjustment = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(spin_button));
    g_signal_connect(adjustment, "value-changed", G_CALLBACK(on_change_value), NULL);

    // Connect the "clicked" signal of the spin button to handle increment and decrement
    g_signal_connect(spin_button, "clicked", G_CALLBACK(on_spin_button_clicked), adjustment);

    // Create an event box to wrap the spin button
    GtkWidget* event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE); // Ensure event box captures events

    // Add the spin button to the event box
    gtk_container_add(GTK_CONTAINER(event_box), spin_button);

    // Setup for draggable
    SpinSdD* move_data = g_new0(SpinSdD, 1);
    move_data->widget = event_box;

    // Connect the mouse events to allow dragging the event box
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(event_box, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(event_box, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Add the event box (with the spin button inside) to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), event_box, 10, 60);
    gtk_widget_show_all(event_box);
}

gboolean SpinButton::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        SpinSdD* move_data = static_cast<SpinSdD*>(data);
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        return TRUE;
    }
    return FALSE;
}

gboolean SpinButton::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        // Do something on button release if needed
        return TRUE;
    }
    return FALSE;
}

gboolean SpinButton::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    SpinSdD* move_data = static_cast<SpinSdD*>(data);
    gint new_x = event->x_root - move_data->offset_x;
    gint new_y = event->y_root - move_data->offset_y;
    gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(move_data->widget)), move_data->widget, new_x, new_y);
    return TRUE;
}

void SpinButton::on_change_value(GtkAdjustment* adjustment, gpointer data) {
    // Récupérer la nouvelle valeur de l'ajustement
    gdouble new_value = gtk_adjustment_get_value(adjustment);
    // Faire quelque chose avec la nouvelle valeur...
}

void SpinButton::on_spin_button_clicked(GtkWidget* widget, gpointer data) {
    GtkAdjustment* adjustment = GTK_ADJUSTMENT(data);
    // Increment or decrement the value of the adjustment as needed
    // Notez que cette fonction sera appelée chaque fois que l'utilisateur cliquera sur le bouton "+" ou "-"
}
