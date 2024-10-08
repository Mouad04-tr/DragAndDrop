#include "TreeView.h"

TreeView::TreeView() {
    treeview = gtk_tree_view_new();
}

GtkWidget* TreeView::getWidget() {
    return treeview;
}
