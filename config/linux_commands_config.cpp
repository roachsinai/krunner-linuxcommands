#include "linux_commands_config.h"
#include "config/linux_commands_config.h"
#include <KSharedConfig>
#include <KPluginFactory>
#include <krunner/abstractrunner.h>
#include <QtDebug>

K_PLUGIN_FACTORY(LinuxCommandsConfigFactory, registerPlugin<LinuxCommandsConfig>("kcm_krunner_linuxcommands");)

LinuxCommandsConfigForm::LinuxCommandsConfigForm(QWidget* parent) : QWidget(parent)
{
    setupUi(this);
}

LinuxCommandsConfig::LinuxCommandsConfig(QWidget* parent, const QVariantList& args) :
        KCModule(parent, args)
{
    m_ui = new LinuxCommandsConfigForm(this);
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_ui, 0, 0);

    connect(m_ui->jsonLocation,SIGNAL(textChanged(QString)),this,SLOT(changed()));

    load();
}

void LinuxCommandsConfig::load()
{
    KCModule::load();

    KSharedConfig::Ptr cfg = KSharedConfig::openConfig(QStringLiteral("krunnerrc"));
    KConfigGroup grp = cfg->group("Runners");
    grp = KConfigGroup(&grp, "Linux Commands");

    m_ui->jsonLocation->setText(grp.readEntry(CONFIG_JSON_LOCATION));

    emit changed(false);
}

void LinuxCommandsConfig::save()
{
    KCModule::save();

    KSharedConfig::Ptr cfg = KSharedConfig::openConfig(QStringLiteral("krunnerrc"));
    KConfigGroup grp = cfg->group("Runners");
    grp = KConfigGroup(&grp, "Linux Commands");

    grp.writeEntry(CONFIG_JSON_LOCATION, m_ui->jsonLocation->text());

    emit changed(false);
}

#include "linux_commands_config.moc"
