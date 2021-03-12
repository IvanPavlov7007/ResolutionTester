#include <QtWidgets>
#include "mainwindow.h"
#include "imageviewer.h"
#include "resolutionchanger.h"

MainWindow :: MainWindow()
{
	viewer = new ImageViewer;
	setCentralWidget(viewer);

	createActions();
	createMenus();
	createToolBars();

	setWindowIcon(QIcon(":/images/icon.png"));

	setMinimumSize(QSize(600, 400));

	curFile = "";
}

void MainWindow::createActions()
{
	changeResolutionAction = new QAction(tr("&Change Resolution"), this);
	changeResolutionAction->setIcon(QIcon(":/images/change.png"));
	changeResolutionAction->setShortcut(tr("Ctrl+C"));
	changeResolutionAction->setStatusTip(tr("Change Resolution of image..."));
	connect(changeResolutionAction, &QAction::triggered, this, &MainWindow::changeResolution);

	openAction = new QAction(tr("&Open"), this);
	openAction->setIcon(QIcon(":/images/open.png"));
	openAction->setShortcut(tr("Ctrl+O"));
	openAction->setStatusTip(tr("Open file..."));
	connect(openAction, &QAction::triggered, this, &MainWindow::open);

	saveAction = new QAction(tr("&Save"), this);
	saveAction->setIcon(QIcon(":/images/save.png"));
	saveAction->setShortcut(tr("Ctrl+S"));
	saveAction->setStatusTip(tr("Save file..."));
	connect(saveAction, &QAction::triggered, this, &MainWindow::save);

	saveAsAction = new QAction(tr("&SaveAs"), this);
	saveAsAction->setIcon(QIcon(":/images/saveAs.png"));
	saveAsAction->setShortcut(tr("Ctrl+W"));
	saveAsAction->setStatusTip(tr("Save file as..."));
	connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(changeResolutionAction);
}


void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(saveAction);
	fileToolBar->addAction(saveAsAction);
	editToolBar = addToolBar(tr("&Edit"));
	editToolBar->addAction(changeResolutionAction);
}

bool MainWindow::okToContinue()
{ 
	int r = QMessageBox::warning(this, tr("ImageViewer"), tr("Do you want to save an image in this resolution?"), QMessageBox::Yes | QMessageBox::Default, QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape); 
	if (r == QMessageBox::Cancel)
		return false;
	else if (r == QMessageBox::Yes)
		return save();
	else
		return true;
}

void MainWindow::open() 
{ 
	if (curFile.isEmpty() || okToContinue()) 
	{ 
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
		{
			if (loadFile(fileName))
				curFile = fileName;
		}
	} 
	viewer->setFocus();
}

bool MainWindow::loadFile(const QString &fileName)
{
	if (!viewer->readFile(fileName))
	{
		return false;
	}
	return true;
}

bool MainWindow::save()
{
		return saveFile(curFile);
		viewer->setFocus();
}

bool MainWindow::saveFile(const QString &fileName)
{
	if (!viewer->writeFile(fileName))
		return false;
	return true;
}

bool MainWindow::saveAs()
{
	if (!curFile.isEmpty())
	{
		QString fileName = QFileDialog::getSaveFileName(this, tr("SaveImage"), tr("Image files.png"));
		if (fileName.isEmpty())
			return false;
		curFile = fileName;
		return saveFile(fileName);
	}
	return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (curFile.isEmpty() || okToContinue())
		event->accept();
	else
		event->ignore();
}

void MainWindow::changeResolution()
{
	QSize res = viewer->getResolution();
	ResolutionChanger changer(this,res.width(),res.height());
	if (changer.exec())
	{
		int height = changer.verticalLineEdit->text().toInt();
		int width = changer.horizontalLineEdit->text().toInt();
		viewer->setNewResolution(QSize(width, height));
	}
}