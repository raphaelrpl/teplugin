#ifndef __TERRALIB_PLUGIN_DIALOG_H
#define __TERRALIB_PLUGIN_DIALOG_H

#include "Config.h"

// TerraLib
#ifndef Q_MOC_RUN
#include <terralib/qt/widgets/canvas/Canvas.h>
#include <terralib/qt/widgets/canvas/MapDisplay.h>
#endif

// QT
#include <QDialog>
#include <QGridLayout>
#include <QObject>
#include <QtGui>
#include <QActionGroup>

// STL
#include <memory>
#include <string>

namespace Ui
{
  class PluginDialog;
}

class PluginDialog : public QDialog
{
  Q_OBJECT

  public:

    PluginDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);

    ~PluginDialog();

    void setMapDisplay(te::qt::widgets::MapDisplay* mapDisplay);

    void setActionGroup(QActionGroup* actionGroup);

  protected slots:

    void onPluginButtonClicked();

  signals:

    void close();

  private:

    void clearCanvas();

    void closeEvent(QCloseEvent* e);

  private:

    std::unique_ptr<Ui::PluginDialog> m_ui;

    te::qt::widgets::MapDisplay* m_mapDisplay;

    QActionGroup* m_actionGroup;
};

#endif  // __TERRALIB_PLUGIN_DIALOG_H