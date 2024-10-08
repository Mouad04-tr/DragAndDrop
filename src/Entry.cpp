#include "Entry.h"

Entry::Entry() {
    widget = gtk_button_new_with_label("Create entry");
}

Entry::Entry(const gchar* placeholderText) {
    widget = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widget), placeholderText);
}

Entry::~Entry() {
    // Libérer les ressources si nécessaire
}

GtkWidget* Entry::getWidget() const {
    return widget;
}

const gchar* Entry::getText() const {
    return gtk_entry_get_text(GTK_ENTRY(widget));
}

void Entry::setText(const gchar* text) {
    gtk_entry_set_text(GTK_ENTRY(widget), text);
}

gboolean Entry::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        SEntryMoveData* move_data = static_cast<SEntryMoveData*>(data);
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        gdk_window_raise(gtk_widget_get_window(widget));
        gtk_grab_add(widget);
    }
    return TRUE;
}

gboolean Entry::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    SEntryMoveData* move_data = static_cast<SEntryMoveData*>(data);
    if (event->state & GDK_BUTTON1_MASK) { // Vérifie si le bouton de la souris est toujours enfoncé
        gint new_x = event->x_root - move_data->offset_x;
        gint new_y = event->y_root - move_data->offset_y;
        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);
    }
    return TRUE;
}

void Entry::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        gtk_grab_remove(widget);
    }
}

void Entry::on_left_entry_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créer une entrée
    Entry* entry = new Entry("Placeholder Text");
    GtkWidget* normal_entry = entry->getWidget();
    gtk_container_add(GTK_CONTAINER(fixed), normal_entry);

    // Setup for draggable
    SEntryMoveData* move_data = new SEntryMoveData;
    move_data->widget = normal_entry;

    // Connecter les signaux de déplacement de la nouvelle entrée
    g_signal_connect(normal_entry, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(normal_entry, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);
    g_signal_connect(normal_entry, "button-release-event", G_CALLBACK(on_button_release_event), move_data);

    // Afficher l'entrée normale
    gtk_widget_show_all(normal_entry);
}
