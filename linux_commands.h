#ifndef LINUX_COMMANDS_H
#define LINUX_COMMANDS_H

#include <KRunner/AbstractRunner>

class LinuxCommandsRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    LinuxCommandsRunner(QObject *parent, const QVariantList &args);
    ~LinuxCommandsRunner();

    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
    void createRunOptions(QWidget *widget) override;
    void reloadConfiguration() override;

private:
    QString linux_command_index_path;
    bool fileExists(QString& path);
    QJsonObject readJson(QString& path);
};

K_EXPORT_PLASMA_RUNNER(linuxcommands, LinuxCommandsRunner)

#endif
