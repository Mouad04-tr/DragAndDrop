#ifndef ENTRY_H
#define ENTRY_H

#include <gtk/gtk.h>

class Entry {
public:
    Entry();
    Entry(const gchar* placeholderText);
    ~Entry();
    GtkWidget* getWidget() const;
    const gchar* getText() const;
    void setText(const gchar* text);

    // Méthodes statiques pour les callbacks des signaux
    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appelée lorsqu'un bouton est enfoncé
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);    // Fonction statique appelée lorsqu'un mouvement de souris est détecté sur le bouton
    static void on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);   // Fonction statique appelée lorsqu'un bouton de la souris est relâché
    static void on_left_entry_button_clicked(GtkWidget* widget, gpointer data);    // Fonction statique appelée lorsqu'un clic gauche est détecté sur le bouton

private:
    GtkWidget* widget;

    // Structure pour les données de déplacement
    struct SEntryMoveData {
        GtkWidget* widget;   // Pointeur vers le widget GTK associé au bouton
        gdouble offset_x;       // Décalage horizontal lors du déplacement
        gdouble offset_y;       // Décalage vertical lors du déplacement
    };
};

#endif // ENTRY_H
