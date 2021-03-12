#pragma once
#include <QMainWindow>

class QAction;
class ResolutionChanger;
class ImageViewer;

class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
protected:
	void closeEvent(QCloseEvent* event);
private slots:
	void open();
	bool save();
	bool saveAs();
	void changeResolution();
private:
	void createActions();
	void createMenus();
	void createToolBars();
	bool okToContinue();
	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	ImageViewer *viewer;

	QString curFile;
	
	QMenu *fileMenu;
	QMenu *editMenu;

	QToolBar *fileToolBar;
	QToolBar *editToolBar;

	QAction *changeResolutionAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;

};