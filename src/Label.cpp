#include<Label.h>


Label::Label() {
    label = gtk_button_new_with_label("label");
}

Label::Label(const char* text) {
    label = gtk_label_new(text);
}

Label::~Label() {}

GtkWidget* Label::getWidget() {
    return label;
}

gboolean Label::on_label_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    Label::LabelMoveData* move_data = static_cast<Label::LabelMoveData*>(data);
    if (event->button == GDK_BUTTON_PRIMARY) {
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
    }
    return TRUE;
}


gboolean Label::on_label_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        gtk_grab_remove(widget);
    }
    return TRUE;
}

gboolean Label::on_label_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    Label::LabelMoveData* move_data = static_cast<Label::LabelMoveData*>(data);
    if (event->state & GDK_BUTTON1_MASK) { // Vérifie si le bouton de la souris est toujours enfoncé
        // Obtenir les nouvelles coordonnées par rapport à la fenêtre parente
        gint new_x, new_y;
        gtk_window_get_position(GTK_WINDOW(gtk_widget_get_toplevel(move_data->widget)), &new_x, &new_y);
        new_x += event->x_root - move_data->offset_x;
        new_y += event->y_root - move_data->offset_y;

        // Déplacer le label à la nouvelle position
        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(move_data->widget)), move_data->widget, new_x, new_y);
    }
    return TRUE; // Éviter d'envoyer l'événement à d'autres gestionnaires
}


void Label::on_left_label_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créer un nouvel événement box pour contenir l'étiquette
    GtkWidget* event_box = gtk_event_box_new();
    // Créer une nouvelle étiquette
    GtkWidget* label = gtk_label_new("Draggable Label");
    // Ajouter l'étiquette à l'événement box
    gtk_container_add(GTK_CONTAINER(event_box), label);
    // Afficher l'étiquette
    gtk_widget_show(label);

    // Créer et configurer la structure de données pour le déplacement de l'événement box
    LabelMoveData* move_data = new LabelMoveData;
    move_data->widget = event_box;

    // Connecter les événements de la souris pour permettre le déplacement de l'événement box
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_label_button_press_event), move_data);
    g_signal_connect(event_box, "motion-notify-event", G_CALLBACK(on_label_motion_notify_event), move_data);

    // Ajouter l'événement box (avec l'étiquette à l'intérieur) au panneau fixe avec une position initiale (10, 10)
    gtk_fixed_put(GTK_FIXED(fixed), event_box, 10, 10);
    // Afficher l'événement box
    gtk_widget_show(event_box);
}


