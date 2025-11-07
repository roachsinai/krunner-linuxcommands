#include "linux_commands.h"
#include "config/linux_commands_config.h"

#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
#include <QFileInfo>
#include <QJsonDocument>
#include <QDir>
#include <QDesktopServices>

LinuxCommandsRunner::LinuxCommandsRunner(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);

    setObjectName(QLatin1String("LinuxCommandsRunner"));
    setHasRunOptions(true);
    setIgnoredTypes(Plasma::RunnerContext::Directory |
                    Plasma::RunnerContext::File |
                    Plasma::RunnerContext::NetworkLocation);
    setSpeed(AbstractRunner::SlowSpeed);
    setPriority(HighestPriority);
    setDefaultSyntax(Plasma::RunnerSyntax(QString("lc :q:"), i18n("List linux commands :q:.")));
    url_prefix = "https://wangchujiang.com/linux-command/c";
    reloadConfiguration();
}

LinuxCommandsRunner::~LinuxCommandsRunner()
{
}

void LinuxCommandsRunner::match(Plasma::RunnerContext &context)
{
    QString text = context.query();

    if (!context.isValid() || !fileExists(morphFile(m_jsonLocation))) return;

    if (text.contains(" ")) {
        QJsonObject json = readJson(morphFile(m_jsonLocation));
        QList<Plasma::QueryMatch> matches;
        float relevance = 1;
        QString kw = text.replace("lc ", "", Qt::CaseInsensitive);
        if (kw.size() > 0) {
            foreach(const QString& key, json.keys()) {
                if (key.contains(kw, Qt::CaseInsensitive)) {
                    QJsonObject inner_json = json.value(key).toObject();
                    QString desc = inner_json.value("d").toString();
                    QUrl url(url_prefix + inner_json.value("p").toString() + ".html");
                    QList<QUrl> urls;
                    urls.append(url);
                    relevance -= 0.01;
                    Plasma::QueryMatch match(this);
                    match.setType(Plasma::QueryMatch::HelperMatch);
                    match.setIcon(QIcon::fromTheme("internet-web-browser"));
                    match.setText(key);
                    match.setSubtext(desc);
                    match.setUrls(urls);
                    match.setEnabled(true);
                    match.setRelevance(relevance);
                    matches.append(match);
                }
            }
        }
        if (!matches.isEmpty())
            context.addMatches(matches);
    }
}

void LinuxCommandsRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context);
    QApplication::clipboard()->setText(match.text());
    foreach(const QUrl& url, match.urls()) {
        QDesktopServices::openUrl(url);
    }
}

void LinuxCommandsRunner::reloadConfiguration()
{
    KConfigGroup grp = config();
    m_jsonLocation= grp.readEntry(CONFIG_JSON_LOCATION);
}

bool LinuxCommandsRunner::fileExists(QString& path) {
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile();
}

QJsonObject LinuxCommandsRunner::readJson(QString& path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray rawData = file.readAll();
    file.close();
    return QJsonDocument::fromJson(rawData).object();
}

QString& LinuxCommandsRunner::morphFile(QString& s)
{
    if (s.startsWith ("~/"))
        s.replace (0, 1, QDir::homePath());
    return s;
}

#include "moc_linux_commands.cpp"
