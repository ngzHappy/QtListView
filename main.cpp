#include "ItemWidgetView.hpp"

#include "mainwindow.h"
#include <QApplication>

#include <QListView>
#include <QStringListModel>
 

#include <QApplication>
#include <QStringListModel>
#include <QPainter>
#include <QImage>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QEventLoop>
#include <QDebug>
#include <QTimer>




class XWidget : public AbstractItemWidget {

	QColor backGroundColor;
	QString stringData;
	QImage backGroundImage;
	QPushButton * button;
	bool isFirstPainted = false;
	QObject * objectManager = 0;
	bool isEnterEvent = false;

public:

	~XWidget() {
		delete objectManager;
	}

	XWidget(QWidget * p) : AbstractItemWidget(p){
		button = new QPushButton;
		QHBoxLayout * l = new QHBoxLayout;
		this->setLayout(l);
		l->addWidget(button);
		backGroundColor = QColor(rand() % 255, rand() % 255, rand() % 255, 255);
		this->setMouseTracking(true);
		objectManager = new QObject;

	}

	virtual void setEditorData(
		const QModelIndex & index
		)  override {
		auto model = index.model();
		if (0 == model) { return; }
		stringData = model->data(index, Qt::DisplayRole).toString();
	}

	void paintEvent(QPaintEvent *)override {

		{
			QPainter painter(this);
			painter.drawImage(0, 0, backGroundImage);
		}

		QPainter painter(this);
		int g_ = 255 - backGroundColor.green();
		QColor color_ = QColor(rand() % 255, g_, rand() % 255, 255);

		painter.setBrush(color_);
		painter.setPen(color_);
		painter.drawText(20, 20, stringData);

		isFirstPainted = true;

	}

	void beforePaint(
		const QStyleOptionViewItem & option,
		const QModelIndex & index) override {

		QImage backGroundImage_(option.rect.size(), QImage::Format_ARGB32_Premultiplied);
        /*如果被选中*/
		if (option.state&QStyle::State_Selected) {
			backGroundImage_.fill(QColor(11, 111, 11));
		}
		else {
			backGroundImage_.fill(backGroundColor);
		}
		backGroundImage = backGroundImage_;

		if (false == isEnterEvent) {
			updateEditorGeometry(option, index);
		}
		else {
			finalRect_ = option.rect;
		}

		setEditorData(index);

	}

	virtual void enterEvent(QEvent *)override {

		if (objectManager == 0) { return; }
		if (isFirstPainted == false) { return; }
		if (isEnterEvent) { return; }

		isEnterEvent = true;
		const auto && finalPos = this->geometry().topLeft();
		auto * animation = new QPropertyAnimation(this, "pos", objectManager);
		animation->setDuration(100);
		animation->setStartValue(finalPos - QPoint(3, 3));
		animation->setEndValue(finalPos);
		animation->connect(animation, &QPropertyAnimation::finished,
			[this]() {
			this->isEnterEvent = false;
			this->setGeometry(finalRect_);
		});
		animation->start(QPropertyAnimation::DeleteWhenStopped);
		
	}

	virtual void beforeWidgetDelete() override{
		delete objectManager;
		objectManager = 0;
	}

};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	

	ItemWidgetView<QListView> view;
	auto model = new QStringListModel(&view);
	{
		QStringList list_;
		list_.push_back("a");
		list_.push_back("b");
		list_.push_back("c");
		list_.push_back("d");
		list_.push_back("e");
		list_.push_back("f");
		list_.push_back("g");
		list_.push_back("h");
		list_.push_back("i");
		model->setStringList(list_);
	}
	view.setItemDelegate(new AbstractItemWidgetDelegate(
		&view,
		[&view]() {return new XWidget(&view); },
		&view));
	view.setItemWidgetModel(model);
    view.setSelectionMode(ItemWidgetView<QListView>::ExtendedSelection);
	view.show();
    

    return app.exec();
}
