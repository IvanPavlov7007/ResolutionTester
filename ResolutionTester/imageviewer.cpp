#include <QPainter>
#include <QtWidgets>
#include <cmath>
#include "imageviewer.h"
using namespace std;

ImageViewer::ImageViewer(QWidget *parent)
	: QWidget(parent)
{
	widget_x = 0;
	widget_y = 0;
	splitLineIsChanging = false;
	pos = width() / 2;
}

void ImageViewer::paintEvent(QPaintEvent *event)
{
	QStylePainter painter(this);
	painter.drawPixmap(0, 0,widget_pixmap);
}

void ImageViewer::resizeEvent(QResizeEvent *event)
{
	refreshPixmap();
}

void ImageViewer::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Left:
		scroll(-5,0);
		refreshPixmap();
		break;
	case Qt::Key_Right:
		scroll(5, 0);
		refreshPixmap();
		break;
	case Qt::Key_Down:
		scroll(0, 5);
		refreshPixmap();
		break;
	case Qt::Key_Up:
		scroll(0, -5);
		refreshPixmap();
		break;
	default:
		QWidget::keyPressEvent(event);
	}
}

void ImageViewer::scroll(int x, int y)
{
	if (widget_x + x <= originalPixmap.width() && widget_y + y <= originalPixmap.height() && widget_x + x >= 0 && widget_y + y >= 0)
	{
		widget_x += x;
		widget_y += y;
	}
}

void ImageViewer::refreshPixmap()
{
	widget_pixmap = QPixmap(size());
	QPainter painter(&widget_pixmap);
	painter.initFrom(this);
	painter.setPen(QPen(Qt::black,2));

	painter.fillRect(rect(), Qt::white);
	if (!originalPixmap.isNull())
	{
		int newPos = min(pos, originalPixmap.width() - widget_x);
		int newHeight = min(height(), originalPixmap.height() - widget_y);

		QRect widget_originalRect(0, 0, newPos, newHeight);
		QRect widget_newResolutionRect(newPos, 0, max(0, originalPixmap.width() - newPos - widget_x), newHeight);
		QRect originalRect(widget_x, widget_y, newPos, newHeight);
		QRect newResolutionRect(widget_x + newPos, widget_y, max(widget_x, originalPixmap.width() - newPos - widget_x), newHeight);

		painter.drawPixmap(widget_originalRect, originalPixmap.copy(originalRect));
		painter.drawPixmap(widget_newResolutionRect, newResolutionPixmap.copy(newResolutionRect));
	}
	painter.drawLine(pos, 0, pos, height());
	update();
}

void ImageViewer::setNewResolution(QSize &resSize)
{
	resolution = resSize;
	displayNewResolution();
}

void ImageViewer::displayNewResolution()
{
	newResolutionPixmap = originalPixmap;
	newResolutionPixmap = newResolutionPixmap.scaled(resolution);
	newPixmap = newResolutionPixmap;
	newResolutionPixmap = newResolutionPixmap.scaled(originalPixmap.size());
	refreshPixmap();
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		pos = event->x();
		setCursor(Qt::SplitHCursor);
		refreshPixmap();
		splitLineIsChanging = true;
	}
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x();
	if ((event->buttons() & Qt::LeftButton) && splitLineIsChanging)
	{
		if (x < 0)
		{
			pos = 0;
		}
		else if (x > width())
		{
			pos = width();
		}
		else
		{
			pos = x;
		}

		refreshPixmap();
	}
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton & splitLineIsChanging)
	{
		splitLineIsChanging = false;
		unsetCursor();
	}
}

bool ImageViewer::readFile(const QString &fileName)
{
	QImage file;
	bool b = file.load(fileName);
	resolution = file.size();
	originalPixmap = QPixmap::fromImage(file);
	displayNewResolution();
	return b;
}

bool ImageViewer::writeFile(const QString &fileName)
{
	QImage image = newPixmap.toImage();
	return image.save(fileName);
	
}

QSize ImageViewer::getResolution() const
{
	return resolution;
}