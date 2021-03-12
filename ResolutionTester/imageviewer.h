#pragma once

#include <QWidget>

class ImageViewer : public QWidget
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = 0);
	bool readFile(const QString &fileName);
	bool writeFile(const QString &fileName);
	QSize getResolution() const;
public slots:
	void setNewResolution(QSize &resSize);
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
private:
	void scroll(int x,int y);
	void refreshPixmap();
	void displayNewResolution();
	QSize resolution;
	int widget_x;
	int widget_y;
	QPixmap widget_pixmap;
	QPixmap originalPixmap;
	QPixmap newResolutionPixmap;
	QPixmap newPixmap;
	int pos;
	bool splitLineIsChanging;
};
