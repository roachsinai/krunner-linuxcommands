#ifndef LINUX_COMMANDS_H
#define LINUX_COMMANDS_H

#include <KRunner/AbstractRunner>

class LinuxCommandsRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    LinuxCommandsRunner(QObject *parent, const QVariantList &args);
    ~LinuxCommandsRunner();

    void match(Plasma::RunnerContext &) override;
    void run(const Plasma::RunnerContext &, const Plasma::QueryMatch &) override;
    void reloadConfiguration() override;

private:
    QString linux_command_index_path;
    QString url_prefix;
    bool fileExists(QString&);
    QJsonObject readJson(QString&);
    QString& morphFile (QString&);
};

K_EXPORT_PLASMA_RUNNER(linuxcommands, LinuxCommandsRunner)

#endif
