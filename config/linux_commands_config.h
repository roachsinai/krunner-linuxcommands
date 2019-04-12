#ifndef LINUX_COMMANDS_CONFIG_H
#define LINUX_COMMANDS_CONFIG_H

#include "ui_linux_commands_config.h"
#include <KCModule>

static const char CONFIG_JSON_LOCATION[] = "~/.data.json";

class LinuxCommandsConfigForm : public QWidget, public Ui::LinuxCommandsConfigUi
{
    Q_OBJECT

public:
    explicit LinuxCommandsConfigForm(QWidget* parent);
};

class LinuxCommandsConfig : public KCModule
{
    Q_OBJECT

public:
    explicit LinuxCommandsConfig(QWidget* parent = 0, const QVariantList& args = QVariantList());

public Q_SLOTS:
    void save() override;
    void load() override;

private:
    LinuxCommandsConfigForm* m_ui;
};

#endif
