#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <gtk/gtk.h>

// Structure de donn�es pour stocker les informations de d�placement de la barre de progression
typedef struct {
    GtkWidget* widget; // La barre de progression
    gboolean pressed;  // Indique si le bouton de la souris est enfonc�
    gint offset_x, offset_y; // Les coordonn�es de l'offset lors du clic
} ProgressBarMoveData;

class ProgressBar {
private:
    GtkWidget* progressbar; // La barre de progression

public:
    ProgressBar();
    ProgressBar(double initial_value);
    ~ProgressBar();
    GtkWidget* getWidget() const;

    // Fonctions de gestion des �v�nements
    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);

    // Fonction pour le clic sur la barre de progression
    static void on_left_ProgBar_clicked(GtkWidget* widget, gpointer data);
};

#endif /* PROGRESSBAR_H */
