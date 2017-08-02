#ifndef CnetEditorWidget_H
#define CnetEditorWidget_H


#include <QWidget>

class QAction;
class QBoxLayout;
class QGroupBox;
template< typename T > class QList;
class QMenu;
class QScrollArea;
class QSplitter;
class QString;
class QToolBar;

namespace Isis {
  class AbstractTableModel;
  class AbstractTreeItem;
  class ControlNet;
  class ControlPoint;
  class FilterWidget;
  class ImageImageTreeModel;
  class ImagePointTreeModel;
  class MeasureTableModel;
  class PointMeasureTreeModel;
  class PointTableModel;
  class TableView;
  class TreeView;

  /**
  * This widget provides full editing, filtering and viewing capabilities for
  * the raw data in a control network. The raw data is, for example, chooser
  * name or cube serial number. The display is all textual. Please use
  * the widget accessors to appropriately place the various ancillary sections
  * of the editor.
  *
  * @author ????-??-?? Eric Hyer
  *
  * @internal
  *   @history 2015-10-07 Ian Humphrey - Icons updated and no longer embedded (in order
  *                           to not violate licensing terms). Fixes #1041.
  *   @history 2017-05-18 Tracie Sucharski - Added a signal to indicate the control point chosen
  *                           from either the point table or the measure table.  If the point was
  *                           chosen from the measure table, the serial number of the measure is
  *                           also passed.  This was added for IPCE, for the interaction with other
  *                           views.
  *   @history 2017-07-25 Summer Stapleton - Removed the CnetViz namespace. Fixes #5054.
  */
  class CnetEditorWidget : public QWidget {
      Q_OBJECT

    public:
      enum View {
        PointView,
        ImageView,
        ConnectionView
      };


    public:
      CnetEditorWidget(ControlNet *, QString);
      virtual ~CnetEditorWidget();
      void readSettings();
      void writeSettings();

      QWidget *pointTreeView();
      QWidget *serialTreeView();
      QWidget *connectionTreeView();
      QWidget *pointFilterWidget();
      QWidget *serialFilterWidget();
      QWidget *connectionFilterWidget();

      AbstractTableModel *measureTableModel();
      AbstractTableModel *pointTableModel();

      QMap< QAction *, QList< QString > > menuActions();
      QMap< QString, QList< QAction * > > toolBarActions();

      ControlNet *filteredNetwork() const;

      bool measureTableSortingEnabled() const;
      int measureTableSortLimit() const;
      bool pointTableSortingEnabled() const;
      int pointTableSortLimit() const;

      void setMeasureTableSortingEnabled(bool enabled);
      void setMeasureTableSortLimit(int limit);
      void setPointTableSortingEnabled(bool enabled);
      void setPointTableSortLimit(int limit);


    public slots:
      void configSorting();
      void setTablesFrozen(bool);
      void rebuildModels();


    signals:
      void cnetModified();

      void editControlPoint(ControlPoint *controlPoint, QString serialNumber);


    private:
      void nullify();
      QBoxLayout *createMainLayout();
      void createActions();
      void createPointTreeView();
      void createSerialTreeView();
      void createConnectionTreeView();
      void createFilterArea();
      void createPointTableView();
      void createMeasureTableView();
      void upgradeVersion();
      void handleTableFilterCountsChanged(int visibleRows, int totalRows,
          QGroupBox *box, QString initialText);


    private slots:
      void rebuildModels(QList< AbstractTreeItem * > itemsToDelete);

      void pointColToggled();
      void measureColToggled();

      void handlePointTableFilterCountsChanged(int visibleRows, int totalRows);
      void handleMeasureTableFilterCountsChanged(int visibleRows,
          int totalRows);


    private: // data
      bool m_updatingSelection;
      ControlNet *m_controlNet;
      QString *m_workingVersion;
      static const QString VERSION;


    private: // widgets
      TreeView *m_pointTreeView;
      TreeView *m_imageTreeView;
      TreeView *m_connectionTreeView;

      TableView *m_pointTableView;
      TableView *m_measureTableView;

      QGroupBox *m_pointTableBox;
      QGroupBox *m_measureTableBox;

      QScrollArea *m_filterArea;

      QWidget *m_pointFilterWidget;
      QWidget *m_serialFilterWidget;
      QWidget *m_connectionFilterWidget;

      PointMeasureTreeModel *m_pointModel;
      ImagePointTreeModel *m_imageModel;
      ImageImageTreeModel *m_connectionModel;

      PointTableModel *m_pointTableModel;
      MeasureTableModel *m_measureTableModel;

      QSplitter *m_mainSplitter;

      QMap< QAction *, QList< QString > > * m_menuActions;
      QMap< QString, QList< QAction * > > * m_toolBarActions;

      QString *m_settingsPath;
  };
}

#endif

