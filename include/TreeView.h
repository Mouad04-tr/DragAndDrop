#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <gtk/gtk.h>

class TreeView {
public:
    TreeView();
    GtkWidget* getWidget();

private:
    GtkWidget* treeview;
};

#endif // TREEVIEW_H
