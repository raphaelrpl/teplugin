// TerraLib

// QT
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include "PluginDialog.h"
#include "ui_PluginDialog.h"

PluginDialog::PluginDialog(QWidget *parent,
      Qt::WindowFlags f)
    : QDialog(parent, f),
      m_ui(new Ui::PluginDialog),
      m_mapDisplay(nullptr)
{
  m_ui->setupUi(this);

  this->setWindowTitle(tr("Web Time Series Services"));
}

PluginDialog::~PluginDialog() = default;

void PluginDialog::setMapDisplay(
    te::qt::widgets::MapDisplay *mapDisplay)
{
  m_mapDisplay = mapDisplay;
}

void PluginDialog::setActionGroup(QActionGroup* actionGroup)
{
  m_actionGroup = actionGroup;
}

void PluginDialog::onPluginButtonClicked()
{

}

void PluginDialog::clearCanvas()
{
  te::qt::widgets::Canvas canvas(m_mapDisplay->getDraftPixmap());

  canvas.clear();

  m_mapDisplay->refresh();
}

void PluginDialog::closeEvent(QCloseEvent * /*e*/)
{
  clearCanvas();

  m_mapDisplay->setCursor(Qt::ArrowCursor);
  m_mapDisplay->setCurrentTool(nullptr, false);

  emit close();
}