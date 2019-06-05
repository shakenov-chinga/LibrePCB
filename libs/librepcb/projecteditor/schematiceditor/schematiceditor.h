/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBREPCB_PROJECT_SCHEMATICEDITOR_H
#define LIBREPCB_PROJECT_SCHEMATICEDITOR_H

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include <librepcb/common/graphics/if_graphicsvieweventhandler.h>

#include <QtCore>
#include <QtWidgets>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/
namespace librepcb {

class GraphicsScene;
class GraphicsView;
class GridProperties;
class UndoStackActionGroup;
class ExclusiveActionGroup;

namespace project {

class Project;
class Schematic;

namespace editor {

class ProjectEditor;
class SchematicPagesDock;
class ErcMsgDock;
class SES_FSM;

namespace Ui {
class SchematicEditor;
}

/*******************************************************************************
 *  Class SchematicEditor
 ******************************************************************************/

/**
 * @brief The SchematicEditor class
 */
class SchematicEditor final : public QMainWindow,
                              public IF_GraphicsViewEventHandler {
  Q_OBJECT

public:
  /*>>> from schematic.h <<<*/
  // Types

  /**
   * @brief Z Values of all items in a schematic scene (to define the stacking
   * order)
   *
   * These values are used for QGraphicsItem::setZValue() to define the stacking
   * order of all items in a schematic QGraphicsScene. We use integer values,
   * even if the z-value of QGraphicsItem is a qreal attribute...
   *
   * Low number = background, high number = foreground
   */
  enum ItemZValue {
    ZValue_Default = 0,  ///< this is the default value (behind all other items)
    ZValue_Symbols,      ///< Z value for #project#SI_Symbol items
    ZValue_NetLabels,    ///< Z value for #project#SI_NetLabel items
    ZValue_NetLines,     ///< Z value for #project#SI_NetLine items
    ZValue_HiddenNetPoints,   ///< Z value for hidden #project#SI_NetPoint items
    ZValue_VisibleNetPoints,  ///< Z value for visible #project#SI_NetPoint
                              ///< items
  };
  /*><*/

  // Constructors / Destructor
  explicit SchematicEditor(ProjectEditor& projectEditor, Project& project);
  ~SchematicEditor();

  // Getters
  ProjectEditor& getProjectEditor() const noexcept { return mProjectEditor; }
  Project&       getProject() const noexcept { return mProject; }
  int getActiveSchematicIndex() const noexcept { return mActiveSchematicIndex; }
  Schematic*            getActiveSchematic() const noexcept;
  const GridProperties& getGridProperties() const noexcept {
    return *mGridProperties;
  }

  /*>>> from schematic.h <<<*/
  GraphicsScene&  getGraphicsScene() const noexcept { return *mGraphicsScene; }
  bool            isEmpty() const noexcept;
  QList<SI_Base*> getItemsAtScenePos(const Point& pos) const noexcept;
  QList<SI_NetPoint*>  getNetPointsAtScenePos(const Point& pos) const noexcept;
  QList<SI_NetLine*>   getNetLinesAtScenePos(const Point& pos) const noexcept;
  QList<SI_NetLabel*>  getNetLabelsAtScenePos(const Point& pos) const noexcept;
  QList<SI_SymbolPin*> getPinsAtScenePos(const Point& pos) const noexcept;

  const QIcon&       getIcon() const noexcept { return mIcon; }
  /*><*/

  // Setters
  bool setActiveSchematicIndex(int index) noexcept;

  // General Methods
  void abortAllCommands() noexcept;

  /*>>> from schematic.h <<<*/
  void showInView(GraphicsView& view) noexcept;
  void saveViewSceneRect(const QRectF& rect) noexcept { mViewRect = rect; }
  const QRectF& restoreViewSceneRect() const noexcept { return mViewRect; }
  void          setSelectionRect(const Point& p1, const Point& p2,
                                 bool updateItems) noexcept;
  void          clearSelection() const noexcept;
  void          updateAllNetLabelAnchors() noexcept;
  void          renderToQPainter(QPainter& painter) const noexcept;
  std::unique_ptr<SchematicSelectionQuery> createSelectionQuery() const
      noexcept;
  /*><*/

protected:
  void closeEvent(QCloseEvent* event);

private slots:

  // Actions
  void on_actionClose_Project_triggered();
  void on_actionNew_Schematic_Page_triggered();
  void on_actionGrid_triggered();
  void on_actionPrint_triggered();
  void on_actionPDF_Export_triggered();
  void on_actionAddComp_Resistor_triggered();
  void on_actionAddComp_BipolarCapacitor_triggered();
  void on_actionAddComp_UnipolarCapacitor_triggered();
  void on_actionAddComp_Inductor_triggered();
  void on_actionAddComp_gnd_triggered();
  void on_actionAddComp_vcc_triggered();
  void on_actionProjectProperties_triggered();
  void on_actionUpdateLibrary_triggered();

signals:

  void activeSchematicChanged(int oldIndex, int newIndex);

private:
  // make some methods inaccessible...
  SchematicEditor();
  SchematicEditor(const SchematicEditor& other);
  SchematicEditor& operator=(const SchematicEditor& rhs);

  // Private Methods
  bool graphicsViewEventHandler(QEvent* event);
  void toolActionGroupChangeTriggered(const QVariant& newTool) noexcept;
  void updateIcon() noexcept;

  // General Attributes
  ProjectEditor&                       mProjectEditor;
  Project&                             mProject;
  Ui::SchematicEditor*                 mUi;
  GraphicsView*                        mGraphicsView;
  GridProperties*                      mGridProperties;
  QScopedPointer<UndoStackActionGroup> mUndoStackActionGroup;
  QScopedPointer<ExclusiveActionGroup> mToolsActionGroup;

  /*>>> from schematic.h <<<*/
  QScopedPointer<GraphicsScene>  mGraphicsScene;
  QRectF                         mViewRect;
  QIcon       mIcon;
  /*><*/

  int mActiveSchematicIndex;

  // Docks
  SchematicPagesDock* mPagesDock;
  ErcMsgDock*         mErcMsgDock;

  // Finite State Machine
  SES_FSM* mFsm;
};

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace editor
}  // namespace project
}  // namespace librepcb

#endif  // LIBREPCB_PROJECT_SCHEMATICEDITOR_H
