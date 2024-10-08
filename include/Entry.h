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

    // M�thodes statiques pour les callbacks des signaux
    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appel�e lorsqu'un bouton est enfonc�
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);    // Fonction statique appel�e lorsqu'un mouvement de souris est d�tect� sur le bouton
    static void on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);   // Fonction statique appel�e lorsqu'un bouton de la souris est rel�ch�
    static void on_left_entry_button_clicked(GtkWidget* widget, gpointer data);    // Fonction statique appel�e lorsqu'un clic gauche est d�tect� sur le bouton

private:
    GtkWidget* widget;

    // Structure pour les donn�es de d�placement
    struct SEntryMoveData {
        GtkWidget* widget;   // Pointeur vers le widget GTK associ� au bouton
        gdouble offset_x;       // D�calage horizontal lors du d�placement
        gdouble offset_y;       // D�calage vertical lors du d�placement
    };
};

#endif // ENTRY_H
