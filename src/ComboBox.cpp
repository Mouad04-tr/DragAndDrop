#include "ComboBox.h"

ComboBox::ComboBox() {
    widget = gtk_button_new_with_label("Create Combo Box");
}

ComboBox::~ComboBox() {
    // Libérer les ressources si nécessaire
}

GtkWidget* ComboBox::getWidget() const {
    return widget;
}

void ComboBox::on_left_combo_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Create the combo box with entry
    GtkWidget* combo = gtk_combo_box_text_new_with_entry();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Option 1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Option 2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Option 3");

    // Create an event box to wrap combo box
    GtkWidget* event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE); // Ensure event box captures events

    // Add the combo box to the event box
    gtk_container_add(GTK_CONTAINER(event_box), combo);

    // Setup for draggable
    ComboSdD* move_data = g_new0(ComboSdD, 1);
    move_data->widget = event_box;

    // Connect the mouse events to allow dragging the event box
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(event_box, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(event_box, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Add the event box (with the combo inside) to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), event_box, 10, 20);
    gtk_widget_show_all(event_box);
}

gboolean ComboBox::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        ComboSdD* move_data = static_cast<ComboSdD*>(data);
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        return TRUE;
    }
    return FALSE;
}

gboolean ComboBox::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        // Do something on button release if needed
        return TRUE;
    }
    return FALSE;
}

gboolean ComboBox::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    ComboSdD* move_data = static_cast<ComboSdD*>(data);
    gint new_x = event->x_root - move_data->offset_x;
    gint new_y = event->y_root - move_data->offset_y;
    gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(move_data->widget)), move_data->widget, new_x, new_y);
    return TRUE;
}
