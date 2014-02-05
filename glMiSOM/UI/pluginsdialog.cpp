//
//
// pluginsdialog.h
//
// LE Viet Man
// 16/09/2011
//
//

#include "pluginsdialog.h"
#include "ui_pluginsdialog.h"

PluginsDialog::PluginsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginsDialog)
{
    ui->setupUi(this);
}

PluginsDialog::~PluginsDialog()
{
    delete ui;
}

void PluginsDialog::addExtractors(QList<ExtractorInterface *> extractors)
{
    this->extractors = extractors;

    addItemsToListPlugins();

    ui->lstPlugins->setCurrentRow(0);
}

void PluginsDialog::on_btnCancel_clicked()
{
    hide();
}

void PluginsDialog::on_btnAdd_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Choose a plugin"),
                                                    QDir::homePath(),
                                                    tr("Plugin file (*.so)"));

    if (!filename.isEmpty())
    {
        QFileInfo fileInfo(filename);

        QString newFile = Util::getPathFilePlugin(fileInfo.fileName());

        QFile::copy(filename, newFile);

        emit addExtractor(newFile);
    }
}

void PluginsDialog::on_btnDelete_clicked()
{
    int ret = QMessageBox::warning(this, "Warning",
                                   QString("Be careful when deleting a plugin because it can make the program"
                                           "not work well or lack of extractors that this plugin undertake."
                                           "Do you still want to delete this plugin ?"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::Yes);

    if (ret == QMessageBox::No) return;

    int currentRow = ui->lstPlugins->currentIndex().row();

    if (currentRow == -1) return;

    ExtractorInterface *ext = extractors[currentRow];
    QString filename = ext->getPluginName();

    if (Util::isDynamicLibrary(filename))
    {
        QDir pluginsDir(QApplication::applicationDirPath());

        if (!pluginsDir.cd("plugins"))
            return;

        pluginsDir.remove(filename);

        extractors.removeAt(currentRow);
        emit deleteExtractor(extractors);

        addItemsToListPlugins();
    }
    else
    {
        QMessageBox::information(this,
                                 tr("Delete"),
                                 tr("Couldn't remove a static plugin."));
    }
}

void PluginsDialog::on_lstPlugins_currentRowChanged(int currentRow)
{
    if (currentRow == -1) return;

    ExtractorInterface *ext = extractors[currentRow];

    ui->lblAbout->setText(ext->about());
}

void PluginsDialog::addItemsToListPlugins()
{
    ui->lstPlugins->clear();
    foreach (ExtractorInterface *ext, extractors)
    {
        ui->lstPlugins->addItem(ext->getFullName());
    }
}
