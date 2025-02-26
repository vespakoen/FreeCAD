/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   Copyright (c) 2017 Christophe Grellier <cg[at]grellier.fr>            *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef SURFACEGUI_TASKFILLINGEDGE_H
#define SURFACEGUI_TASKFILLINGEDGE_H

#include <Gui/DocumentObserver.h>
#include <Gui/SelectionFilter.h>
#include <Mod/Surface/App/FeatureFilling.h>


class QListWidgetItem;

namespace SurfaceGui
{

class ViewProviderFilling;
class Ui_TaskFillingEdge;

class FillingEdgePanel : public QWidget,
                         public Gui::SelectionObserver,
                         public Gui::DocumentObserver
{
    Q_OBJECT

protected:
    class ShapeSelection;
    enum SelectionMode { None, AppendEdge, RemoveEdge };
    SelectionMode selectionMode;
    Surface::Filling* editedObject;
    bool checkCommand;

private:
    Ui_TaskFillingEdge* ui;
    ViewProviderFilling* vp;

public:
    FillingEdgePanel(ViewProviderFilling* vp, Surface::Filling* obj);
    ~FillingEdgePanel() override;

    void open();
    void checkOpenCommand();
    bool accept();
    bool reject();
    void setEditedObject(Surface::Filling* obj);

protected:
    void changeEvent(QEvent *e) override;
    void onSelectionChanged(const Gui::SelectionChanges& msg) override;
    /** Notifies on undo */
    void slotUndoDocument(const Gui::Document& Doc) override;
    /** Notifies on redo */
    void slotRedoDocument(const Gui::Document& Doc) override;
    /** Notifies when the object is about to be removed. */
    void slotDeletedObject(const Gui::ViewProviderDocumentObject& Obj) override;
    void modifyBoundary(bool);

private Q_SLOTS:
    void on_buttonUnboundEdgeAdd_clicked();
    void on_buttonUnboundEdgeRemove_clicked();
    void on_listUnbound_itemDoubleClicked(QListWidgetItem*);
    void on_buttonUnboundAccept_clicked();
    void on_buttonUnboundIgnore_clicked();
    void onDeleteUnboundEdge();
    void clearSelection();
};

} //namespace SurfaceGui

#endif // SURFACEGUI_TASKFILLINGEDGE_H
