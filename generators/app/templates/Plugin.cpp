// Terralib
#include "Plugin.h"
#include <terralib/qt/af/ApplicationController.h>
#include <terralib/qt/af/Utils.h>
#include <terralib/qt/af/events/ApplicationEvents.h>
// QT
#include <QApplication>
#include <QMessageBox>


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

    m_wtssAction = new QAction(this);
    m_wtssAction->setText("Helloworld");
    // m_wtssAction->setIcon(QIcon::fromTheme("chart-time-series"));
    m_wtssAction->setObjectName("Tools.Helloworld");

    m_menu->addAction(m_wtssAction);

    registerActions();
  }
}

void Plugin::shutdown()
{
  if(!m_initialized)
      return;

  m_initialized = false;

  delete m_wtssAction;
  delete m_timeSeriesAction;

  te::qt::af::AppCtrlSingleton::getInstance().removeToolBar("Tools.Helloworld");

  te::qt::af::AppCtrlSingleton::getInstance().removeListener(this);
}

void Plugin::registerActions()
{
  connect(m_wtssAction, SIGNAL(triggered(bool)), this,
          SLOT(onActionActivated(bool)));

  connect(m_timeSeriesAction, SIGNAL(toggled(bool)), this,
          SLOT(onActionQueryToggled()));
}

void Plugin::unregisterActions() {}

void Plugin::onActionActivated(bool)
{
  te::qt::af::evt::NewActionsAvailable e;
  e.m_toolbar = m_wtssToolBar;
  e.m_category = "Helloworld_Toolbar";

  emit triggered(&e);
}

void Plugin::onActionQueryToggled()
{
  if(!m_timeSeriesAction->isChecked())
  {
    m_timeSeriesAction->blockSignals(true);
    m_timeSeriesAction->setChecked(true);
    m_timeSeriesAction->blockSignals(false);
    return;
  }

  QMessageBox::warning(te::qt::af::AppCtrlSingleton::getInstance().getMainWindow(), "ALOWWWWWWWWW", "MEU PLUGIN FUNCIA");

  // m_dialog.reset(new Dialog(te::qt::af::AppCtrlSingleton::getInstance().getMainWindow()));

  // connect(m_dialog.get(), SIGNAL(close()), this, SLOT(onCloseTool()));

  // m_dialog->setModal(false);

  // m_dialog->show();
}

void Plugin::onCloseTool()
{
  m_timeSeriesAction->blockSignals(true);
  m_timeSeriesAction->setChecked(false);
  m_timeSeriesAction->blockSignals(false);

  // m_dialog.reset(nullptr);
}

TERRALIB_PLUGIN_CALL_BACK_IMPL(Plugin)
