#include <DApplication>
#include <DButtonBox>
#include <DLog>
#include <DWidget>
#include <QDBusConnection>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <chrono>

int main(int argc, char *argv[]) {
  Dtk::Widget::DApplication app(argc, argv);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  Dtk::Widget::DApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

  Dtk::Core::DLogManager::registerConsoleAppender();
  Dtk::Core::DLogManager::registerFileAppender();
  Dtk::Core::DLogManager::registerJournalAppender();

  QQmlApplicationEngine engine(":/qml/Main.qml");

  auto session_bus = QDBusConnection::sessionBus();
  auto system_bus = QDBusConnection::systemBus();

  QTimer timer;
  timer.callOnTimeout([] { Dtk::Widget::DApplication::quit(); });
  using namespace std::chrono_literals;
  timer.start(1s);

  return Dtk::Widget::DApplication::exec();
}
