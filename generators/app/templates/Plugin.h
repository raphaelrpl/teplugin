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

// Plugin Example
#include "PluginDialog.h"

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

    ~Plugin();

    void startup();

    void shutdown();

  protected:

    void registerActions();

    void unregisterActions();

    Q_SIGNALS:

    void triggered(te::qt::af::evt::Event* e);

  protected:

    QMenu* m_menu;

    QToolBar* m_pluginExampleToolBar;

    QAction* m_pluginExampleMenuAction;

    QAction* m_pluginExampleToolbarAction;

  protected slots:

    void onActionActivated(bool);

    void onActionQueryToggled();

    void onCloseTool();

  private:

    std::unique_ptr<PluginDialog> m_PluginExampleDlg;

};

#endif  //__TERRALIB_<%= appnameUpper %>_PLUGIN_H