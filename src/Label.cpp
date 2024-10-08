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
    if (event->state & GDK_BUTTON1_MASK) { // V�rifie si le bouton de la souris est toujours enfonc�
        // Obtenir les nouvelles coordonn�es par rapport � la fen�tre parente
        gint new_x, new_y;
        gtk_window_get_position(GTK_WINDOW(gtk_widget_get_toplevel(move_data->widget)), &new_x, &new_y);
        new_x += event->x_root - move_data->offset_x;
        new_y += event->y_root - move_data->offset_y;

        // D�placer le label � la nouvelle position
        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(move_data->widget)), move_data->widget, new_x, new_y);
    }
    return TRUE; // �viter d'envoyer l'�v�nement � d'autres gestionnaires
}


void Label::on_left_label_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Cr�er un nouvel �v�nement box pour contenir l'�tiquette
    GtkWidget* event_box = gtk_event_box_new();
    // Cr�er une nouvelle �tiquette
    GtkWidget* label = gtk_label_new("Draggable Label");
    // Ajouter l'�tiquette � l'�v�nement box
    gtk_container_add(GTK_CONTAINER(event_box), label);
    // Afficher l'�tiquette
    gtk_widget_show(label);

    // Cr�er et configurer la structure de donn�es pour le d�placement de l'�v�nement box
    LabelMoveData* move_data = new LabelMoveData;
    move_data->widget = event_box;

    // Connecter les �v�nements de la souris pour permettre le d�placement de l'�v�nement box
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_label_button_press_event), move_data);
    g_signal_connect(event_box, "motion-notify-event", G_CALLBACK(on_label_motion_notify_event), move_data);

    // Ajouter l'�v�nement box (avec l'�tiquette � l'int�rieur) au panneau fixe avec une position initiale (10, 10)
    gtk_fixed_put(GTK_FIXED(fixed), event_box, 10, 10);
    // Afficher l'�v�nement box
    gtk_widget_show(event_box);
}


