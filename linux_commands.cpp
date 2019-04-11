#include "linux_commands.h"

#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
#include <QFileInfo>
#include <QJsonDocument>

LinuxCommandsRunner::LinuxCommandsRunner(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);

    setObjectName(QLatin1String("LinuxCommandsRunner"));
    reloadConfiguration();
    setHasRunOptions(true);
    setIgnoredTypes(Plasma::RunnerContext::Directory |
                    Plasma::RunnerContext::File |
                    Plasma::RunnerContext::NetworkLocation);
    setSpeed(AbstractRunner::SlowSpeed);
    setPriority(HighestPriority);
    setDefaultSyntax(Plasma::RunnerSyntax(QString("lc :q:"), i18n("List linux commands :q:.")));
    linux_command_index_path = "/home/roach/data.json";
}

LinuxCommandsRunner::~LinuxCommandsRunner()
{
}

void LinuxCommandsRunner::match(Plasma::RunnerContext &context)
{
    QString text = context.query();

    if (!context.isValid() || !fileExists(linux_command_index_path)) return;

    if (text.contains(" ")) {
        QJsonObject json = readJson(linux_command_index_path);
        QEventLoop loop;
        QList<Plasma::QueryMatch> matches;
        float relevance = 1;
        QString kw = text.replace("lc", "", Qt::CaseInsensitive);
        if (kw.size() > 0) {
            foreach(const QString& key, json.keys()) {
                if (key.contains(kw, Qt::CaseInsensitive)) {
                    relevance -= 0.01;
                    Plasma::QueryMatch match(this);
                    match.setType(Plasma::QueryMatch::InformationalMatch);
                    match.setIcon(QIcon::fromTheme("konversation"));
                    match.setText(key);
                    match.setRelevance(relevance);
                    matches.append(match);
                }
            }
        }
        context.addMatches(matches);
        loop.exec();
    }
}

void LinuxCommandsRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context);
    QApplication::clipboard()->setText(match.text());
}

void LinuxCommandsRunner::reloadConfiguration()
{
    //nothing
}

bool LinuxCommandsRunner::fileExists(QString& path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
QJsonObject LinuxCommandsRunner::readJson(QString& path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray rawData = file.readAll();
    file.close();
    return QJsonDocument::fromJson(rawData).object();
}
#include "moc_linux_commands.cpp"
