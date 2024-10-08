#include "FileChooserButton.h"

FileChooserButton::FileChooserButton(){
    filechooserbutton = gtk_button_new_with_label("Create FileChooser ");
}


FileChooserButton::FileChooserButton(const char* title, GtkFileChooserAction action) {
    filechooserbutton = gtk_file_chooser_button_new(title, action);
    g_signal_connect(filechooserbutton, "button-press-event", G_CALLBACK(on_button_press_event), NULL);
    g_signal_connect(filechooserbutton, "button-release-event", G_CALLBACK(on_button_release_event), NULL);
    g_signal_connect(filechooserbutton, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(filechooserbutton, "selection-changed", G_CALLBACK(on_selection_changed), NULL);
}

FileChooserButton::~FileChooserButton() {
    // Libérer les ressources si nécessaire
}

GtkWidget* FileChooserButton::getWidget() const {
    return filechooserbutton;
}

void FileChooserButton::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        FileChooserButtonSdD* move_data = g_new0(FileChooserButtonSdD, 1);
        move_data->widget = widget;
        move_data->offset_x = event->x;
        move_data->offset_y = event->y;
        gtk_widget_set_app_paintable(widget, TRUE);
        g_object_set_data(G_OBJECT(widget), "motion-data", move_data);
    }
}

void FileChooserButton::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        FileChooserButtonSdD* move_data = static_cast<FileChooserButtonSdD*>(g_object_get_data(G_OBJECT(widget), "motion-data"));
        g_free(move_data);
        gtk_widget_set_app_paintable(widget, FALSE);
    }
}

void FileChooserButton::on_button_clicked(GtkWidget* widget, gpointer data) {
    g_print("Button clicked!\n");
}

void FileChooserButton::on_selection_changed(GtkWidget* widget, gpointer data) {
    g_print("Selection changed!\n");
}
