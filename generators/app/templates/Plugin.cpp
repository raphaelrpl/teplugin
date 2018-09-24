// Terralib
#include <terralib/qt/af/ApplicationController.h>
#include <terralib/qt/af/Utils.h>
#include <terralib/qt/af/events/ApplicationEvents.h>
#include <terralib/qt/af/events/MapEvents.h>
#include <terralib/qt/af/BaseApplication.h>
#include <terralib/qt/widgets/canvas/MapDisplay.h>

// QT
#include <QApplication>

//STL
#include <iostream>

#include "Plugin.h"
#include "PluginDialog.h"

Plugin::Plugin(const te::core::PluginInfo& pluginInfo)
    : te::core::CppPlugin(pluginInfo)
{
  te::qt::af::AppCtrlSingleton::getInstance().addListener(this,
                                                          te::qt::af::SENDER);
}

Plugin::~Plugin() = default;

void Plugin::startup()
{
  if(m_initialized)
    return;

  m_initialized = true;

  {
    m_menu = te::qt::af::AppCtrlSingleton::getInstance().getMenu("Plugins");

    m_pluginExampleMenuAction = new QAction(this);
    m_pluginExampleMenuAction->setText("Plugin Example");
    m_pluginExampleMenuAction->setObjectName("Tools.PluginExample");

    m_menu->addAction(m_pluginExampleMenuAction);

    m_pluginExampleToolbarAction = new QAction(this);
    m_pluginExampleToolbarAction->setText("Plugin Example...");
    m_pluginExampleToolbarAction->setObjectName("Tools.PluginExample.Plugin Example");
    m_pluginExampleToolbarAction->setCheckable(true);
    m_pluginExampleToolbarAction->setEnabled(true);

    m_pluginExampleToolBar = new QToolBar("PluginExample Toolbar");
    m_pluginExampleToolBar->addAction(m_pluginExampleToolbarAction);
    m_pluginExampleToolBar->setEnabled(true);

    registerActions();
  }

  std::cout << "Works" << std::endl;
}

void Plugin::shutdown()
{
  if(!m_initialized)
     return;

  m_initialized = false;

  delete m_pluginExampleMenuAction;
  delete m_pluginExampleToolbarAction;
  delete m_pluginExampleToolBar;

  te::qt::af::AppCtrlSingleton::getInstance().removeToolBar("PluginExample Toolbar");

  te::qt::af::AppCtrlSingleton::getInstance().removeListener(this);
}

void Plugin::registerActions()
{
  connect(m_pluginExampleMenuAction, SIGNAL(triggered(bool)), this,
          SLOT(onActionActivated(bool)));
  connect(m_pluginExampleToolbarAction, SIGNAL(toggled(bool)), this,
          SLOT(onActionQueryToggled()));
}

void Plugin::unregisterActions() {}

void Plugin::onActionActivated(bool)
{
  te::qt::af::evt::NewActionsAvailable e;
  e.m_toolbar = m_pluginExampleToolBar;
  e.m_category = "PluginExampleToolbar";

  emit triggered(&e);
}

void Plugin::onActionQueryToggled()
{
  if(!m_pluginExampleToolbarAction->isChecked())
  {
    m_pluginExampleToolbarAction->blockSignals(true);
    m_pluginExampleToolbarAction->setChecked(true);
    m_pluginExampleToolbarAction->blockSignals(false);
    return;
  }

  m_PluginExampleDlg.reset(new PluginDialog(
                te::qt::af::AppCtrlSingleton::getInstance().getMainWindow()));

  te::qt::af::BaseApplication* baseApplication =
      dynamic_cast<te::qt::af::BaseApplication*>(
          te::qt::af::AppCtrlSingleton::getInstance().getMainWindow());

  connect(m_PluginExampleDlg.get(), SIGNAL(close()), this, SLOT(onCloseTool()));

  QActionGroup* mapEditionTools = te::qt::af::AppCtrlSingleton::getInstance().findActionGroup("Map.ToolsGroup");

  m_PluginExampleDlg->setActionGroup(mapEditionTools);

  m_PluginExampleDlg->setMapDisplay(baseApplication->getMapDisplay());

  m_PluginExampleDlg->setModal(false);

  m_PluginExampleDlg->show();
}

void Plugin::onCloseTool()
{
  m_pluginExampleToolbarAction->blockSignals(true);
  m_pluginExampleToolbarAction->setChecked(false);
  m_pluginExampleToolbarAction->blockSignals(false);

  m_PluginExampleDlg.reset(nullptr);
}

TERRALIB_PLUGIN_CALL_BACK_IMPL(Plugin)