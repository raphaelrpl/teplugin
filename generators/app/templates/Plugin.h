#ifndef __TERRALIB_<%= appnameUpper %>_PLUGIN_H
#define __TERRALIB_<%= appnameUpper %>_PLUGIN_H

// TerraLib
#include <terralib/core/plugin/CppPlugin.h>

// QT
#include <QAction>
#include <QMenu>
#include <QObject>
#include <QToolBar>

// STL
#include <memory>
#include <vector>

// wtss.tl
// #include "Dialog.h"

namespace te
{
  namespace qt
  {
    namespace af
    {
      namespace evt
      {
        struct Event;
      }
    }
  }
}

class Plugin : public QObject, public te::core::CppPlugin
{
  Q_OBJECT

  public:

    Plugin(const te::core::PluginInfo& pluginInfo);

    virtual ~Plugin();

    void startup() override;

    void shutdown() override;

  protected:

    void registerActions();

    void unregisterActions();

  Q_SIGNALS:

    void triggered(te::qt::af::evt::Event* e);

  protected:

    QMenu* m_menu;
    QAction* m_wtssAction;
    QAction* m_timeSeriesAction;
    QToolBar* m_wtssToolBar;

  protected slots:

    void onActionActivated(bool);

    void onActionQueryToggled();

    void onCloseTool();

  private:

  // std::unique_ptr<Dialog> m_dialog;

};

#endif  //__TERRALIB_<%= appnameUpper %>_PLUGIN_H
