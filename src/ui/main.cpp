#include "main.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QTranslator translator;

    if (translator.load(QLocale(), "observer_ui", "_", ":/i18n"))
        QCoreApplication::installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
