#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

// fluid
#include "iconsimageprovider.h"
#include "iconthemeimageprovider.h"

#include "models/playermodel.h"
#include "game.h"
#include "utility"
#include "models/itemmodel.h"
#include "settings.h"
#include "models/chatmodel.h"

/**
 * @mainpage Introduction
 *
 * This is the documentation for the Quickcurver project, a free and open-source implementation of Achtung die Kurve written with Qt.
 *
 * A good starting point for reading this documentation is the Game class.
 */


int main(int argc, char *argv[]) {
	Util::init();
	// threaded render_loop, which is default on non-mesa drivers, breaks drawing
	qputenv("QSG_RENDER_LOOP", "basic");
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QQuickStyle::setStyle(QLatin1String("Material"));
	QApplication app(argc, argv);

	// register QML types here
	qmlRegisterType<Game>("Game", 1, 0, "Game");

	QQmlApplicationEngine engine;
	engine.addImportPath(QLatin1String("qrc:/"));
	engine.addImageProvider(QLatin1String("fluidicons"), new IconsImageProvider());
	engine.addImageProvider(QLatin1String("fluidicontheme"), new IconThemeImageProvider());

	// context properties
	engine.rootContext()->setContextProperty("c_playerModel", &PlayerModel::getSingleton());
	engine.rootContext()->setContextProperty("c_itemModel", &ItemModel::getSingleton());
	engine.rootContext()->setContextProperty("c_chatModel", &ChatModel::getSingleton());
	engine.rootContext()->setContextProperty("c_settings", &Settings::getSingleton());

	engine.load(QUrl(QLatin1String("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty()) {
		return -1;
	}
	return app.exec();
}
