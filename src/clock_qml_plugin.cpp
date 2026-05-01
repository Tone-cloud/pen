#include "clock_controller.h"

#include <QtQml/qqml.h>
#include <QtQml/qqmlextensionplugin.h>

class ClockQmlPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override {
        qmlRegisterType<ClockController>(uri, 1, 0, "ClockController");
    }
};

#include "clock_qml_plugin.moc"
