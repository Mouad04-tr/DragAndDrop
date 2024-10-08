#include "ListBox.h"

ListBox::ListBox() {
    list_box = gtk_list_box_new();
}

ListBox::ListBox(const char* label) {
    list_box = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(list_box), gtk_label_new(label));
}

ListBox::~ListBox() {
}

GtkWidget* ListBox::getWidget() const {
    return list_box;
}

gboolean ListBox::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        ListBoxMoveData* move_data = (ListBoxMoveData*)data;
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        move_data->pressed = TRUE; // Marquer comme enfoncé
        gdk_window_raise(gtk_widget_get_window(widget));
        gtk_grab_add(widget);
    }
    return TRUE;
}

gboolean ListBox::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        ListBoxMoveData* move_data = (ListBoxMoveData*)data;
        move_data->pressed = FALSE; // Marquer comme relâché
        gtk_grab_remove(widget);
    }
    return TRUE;
}

gboolean ListBox::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    ListBoxMoveData* move_data = (ListBoxMoveData*)data;

    if (move_data->pressed) { // Si le bouton est enfoncé
        // Déplacer la liste en fonction du mouvement de la souris
        gint new_x = event->x_root - move_data->offset_x;
        gint new_y = event->y_root - move_data->offset_y;

        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);
    }

    return TRUE;
}

void ListBox::on_left_listbox_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Création de la ListBox
    ListBox list_box;
    GtkWidget* list_box_widget = list_box.getWidget();

    // Vérification que list_box_widget est bien une GtkListBox
    if (!GTK_IS_LIST_BOX(list_box_widget)) {
        g_warning("Error: list_box_widget is not a GtkListBox.");
        return;
    }

    // Modifier la taille du ListBox
    gtk_widget_set_size_request(list_box_widget, 300, -1); // Définir la largeur souhaitée à 300 pixels

    // Ajout de quatre éléments à la ListBox
    for (int i = 1; i <= 4; ++i) {
        char item_label[50];
        snprintf(item_label, sizeof(item_label), "Item %d", i);
        GtkWidget* item_label_widget = gtk_label_new(item_label);
        gtk_list_box_insert(GTK_LIST_BOX(list_box_widget), item_label_widget, -1);
    }

    // Ajout de la ListBox au conteneur fixe
    gtk_container_add(GTK_CONTAINER(fixed), list_box_widget);

    // Connexion des signaux pour permettre le glisser-déposer de la ListBox
    ListBoxMoveData* move_data = g_new0(ListBoxMoveData, 1);
    move_data->widget = list_box_widget;

    g_signal_connect(list_box_widget, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(list_box_widget, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(list_box_widget, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Affichage de tous les widgets
    gtk_widget_show_all(list_box_widget);
}

