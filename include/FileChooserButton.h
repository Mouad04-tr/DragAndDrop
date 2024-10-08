#ifndef FILECHOOSERBUTTON_H
#define FILECHOOSERBUTTON_H

#include <gtk/gtk.h>

class FileChooserButton {
public:
    FileChooserButton();
    FileChooserButton(const char* title, GtkFileChooserAction action);
    ~FileChooserButton();
    GtkWidget* getWidget() const;

    // Fonctions de gestion des signaux
    static void on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static void on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static void on_button_clicked(GtkWidget* widget, gpointer data);
    static void on_selection_changed(GtkWidget* widget, gpointer data);

private:
    GtkWidget* filechooserbutton;

    // Structure de données pour stocker les données de mouvement
    typedef struct {
        GtkWidget* widget;
        gint offset_x, offset_y;
    } FileChooserButtonSdD;
};

#endif // FILECHOOSERBUTTON_H
