#include"namespace.h"

void Util::RemoveLayout(QWidget* widget){
    QLayoutItem * item;
    QLayout * sublayout;
    QLayout* layout=widget->layout();
    while ((item = layout->takeAt(0))) {
        if ((sublayout = item->layout()) != nullptr) {/* do the same for sublayout*/}
        else if ((widget = item->widget()) != nullptr) {widget->hide(); delete widget;}
        else {delete item;}
    }

    // then finally
    delete layout;
}
