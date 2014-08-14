#include <QPainter>
#include <QString>
#include "Nansy.h"



Nansy::Nansy(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
	, mPressedButton(Qt::NoButton)
	, mPressX(0)
	, mPressY(0)
	, mReleaseX(0)
	, mReleaseY(0)
	, mNowX(0)
	, mNowY(0)
{
	pMainBufferImage = new QImage(WINWIDTH, WINHEIGHT, QImage::Format_ARGB32);
	midSpace = new MidSpace(pMainBufferImage);
	pItemSpace = new ItemSpace(midSpace);
	initMenu();
	connect(pItemSpace, SIGNAL(changed()), this, SLOT(update()));
}

Nansy::~Nansy()
{

}

void Nansy::initMenu()
{
	pFileMenu = new NansyMenu(tr("File"));	
	pViewMenu = new NansyMenu(tr("View"));
	pSampleMenu = new NansyMenu(tr("Sample"));
	pOptionMenu = new NansyMenu(tr("Option"));
	connect(pFileMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));
	connect(pViewMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));
	connect(pSampleMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));
	connect(pOptionMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));
	connect(pFileMenu, SIGNAL(entered()), pViewMenu, SLOT(hide()));
	connect(pFileMenu, SIGNAL(entered()), pSampleMenu, SLOT(hide()));
	connect(pFileMenu, SIGNAL(entered()), pOptionMenu, SLOT(hide()));
	connect(pViewMenu, SIGNAL(entered()), pFileMenu, SLOT(hide()));
	connect(pViewMenu, SIGNAL(entered()), pSampleMenu, SLOT(hide()));
	connect(pViewMenu, SIGNAL(entered()), pOptionMenu, SLOT(hide()));
	connect(pSampleMenu, SIGNAL(entered()), pViewMenu, SLOT(hide()));
	connect(pSampleMenu, SIGNAL(entered()), pFileMenu, SLOT(hide()));
	connect(pSampleMenu, SIGNAL(entered()), pOptionMenu, SLOT(hide()));
	connect(pOptionMenu, SIGNAL(entered()), pFileMenu, SLOT(hide()));
	connect(pOptionMenu, SIGNAL(entered()), pViewMenu, SLOT(hide()));
	connect(pOptionMenu, SIGNAL(entered()), pSampleMenu, SLOT(hide()));

	//file action
	pfOpenAction = new QAction(tr("Open"), pFileMenu);
	connect(pfOpenAction, SIGNAL(triggered()), pItemSpace, SLOT(OpenObj()));
	pfClearAction = new QAction(tr("Clear"), pFileMenu);
	connect(pfClearAction, SIGNAL(triggered()), pItemSpace, SLOT(Clear()));
	pFileMenu->addAction(pfOpenAction);
	pFileMenu->addAction(pfClearAction);

	//view action
	pvRotateAction = new QAction(tr("Rotate"), pViewMenu);
	connect(pvRotateAction, SIGNAL(triggered()), this, SLOT(setViewMode2Rotate()));
	pvMoveAction = new QAction(tr("Move"), pViewMenu);
	connect(pvMoveAction, SIGNAL(triggered()), this, SLOT(setViewMode2Move()));
	pvScaleAction = new QAction(tr("Scale"), pViewMenu);
	connect(pvScaleAction, SIGNAL(triggered()), this, SLOT(setViewMode2Scale()));
	pvResetAction = new QAction(tr("Reset"), pViewMenu);
	connect(pvResetAction, SIGNAL(triggered()), this, SLOT(resetViewMode()));
	pvFixAction = new QAction(tr("Fix"), pViewMenu);
	connect(pvFixAction, SIGNAL(triggered()), this, SLOT(setViewMode2Fixed()));
	pViewMenu->addAction(pvRotateAction);
	pViewMenu->addAction(pvMoveAction);
	pViewMenu->addAction(pvScaleAction);
	pViewMenu->addAction(pvResetAction);

	//sample action
	psRndTriAction = new QAction(tr("Random Triangles"), pSampleMenu);
	connect(psRndTriAction, SIGNAL(triggered()), pItemSpace, SLOT(ShowRandomTriangle()));
	connect(psRndTriAction, SIGNAL(triggered()), this, SLOT(setViewMode2Fixed()));
	pSampleMenu->addAction(psRndTriAction);
	psElfAction = new QAction(tr("Elf"), pSampleMenu);
	connect(psElfAction, SIGNAL(triggered()), pItemSpace, SLOT(ShowElf()));
	connect(psElfAction, SIGNAL(triggered()), this, SLOT(setViewMode2Fixed()));
	pSampleMenu->addAction(psElfAction);
	psGirlAction = new QAction(tr("Girl"), pSampleMenu);
	connect(psGirlAction, SIGNAL(triggered()), pItemSpace, SLOT(ShowGirl()));
	connect(psGirlAction, SIGNAL(triggered()), this, SLOT(setViewMode2Fixed()));
	pSampleMenu->addAction(psGirlAction);
	psPlantAction = new QAction(tr("Plant"), pSampleMenu);
	connect(psPlantAction, SIGNAL(triggered()), pItemSpace, SLOT(ShowPlant()));
	connect(psPlantAction, SIGNAL(triggered()), this, SLOT(setViewMode2Fixed()));
	pSampleMenu->addAction(psPlantAction);

	//option action
	poLightAction = new QAction(tr("Enable Light"), pOptionMenu);
	poLightAction->setCheckable(true);
	poLightAction->setChecked(true);
	connect(poLightAction, SIGNAL(triggered()), pItemSpace, SLOT(SwitchLight()));
	poDirAction = new QAction(tr("Enable Direction"), pOptionMenu);
	poDirAction->setCheckable(true);
	poDirAction->setChecked(true);
	connect(poDirAction, SIGNAL(triggered()), pItemSpace, SLOT(SwitchDir()));
	poNormAction = new QAction(tr("Calculate Norm"), pOptionMenu);
	poNormAction->setCheckable(true);
	poNormAction->setChecked(false);
	connect(poNormAction, SIGNAL(triggered()), pItemSpace, SLOT(SwitchNorm()));
	poColorAction = new QAction(tr("Enable Color"), pOptionMenu);
	poColorAction->setCheckable(true);
	poColorAction->setChecked(true);
	connect(poColorAction, SIGNAL(triggered()), pItemSpace, SLOT(SwitchColor()));
	poSmoothAction = new QAction(tr("Smooth Color"), pOptionMenu);
	poSmoothAction->setCheckable(true);
	poSmoothAction->setChecked(true);
	connect(poSmoothAction, SIGNAL(triggered()), pItemSpace, SLOT(SwitchSmooth()));
	poLineAction = new QAction(tr("Line Mode"), pOptionMenu);
	poLineAction->setCheckable(true);
	poLineAction->setChecked(false);
	connect(poLineAction, SIGNAL(triggered()), pItemSpace, SLOT(SwitchLine()));
	pOptionMenu->addAction(poLightAction);
	pOptionMenu->addAction(poDirAction);
	pOptionMenu->addAction(poNormAction);
	pOptionMenu->addAction(poColorAction);
	pOptionMenu->addAction(poSmoothAction);
	pOptionMenu->addAction(poLineAction);

	pFileMenu->installEventFilter(this);
	pViewMenu->installEventFilter(this);
	pSampleMenu->installEventFilter(this);
	pOptionMenu->installEventFilter(this);
}

void Nansy::mouseReleaseEvent ( QMouseEvent * event )
{
	if(event->button() == Qt::RightButton){
		showAllMenu(event->globalPos());
	} else if(event->button() == Qt::LeftButton){
		mNowX = mPressX;
		mNowY = mPressY;
	}
	mPressedButton = Qt::NoButton;
}

void Nansy::mousePressEvent(QMouseEvent * event)
{
	mPressX = event->x();
	mPressY = event->y();
	mPressedButton = event->button();
	mNowX = mPressX;
	mNowY = mPressY;
}

void Nansy::mouseMoveEvent(QMouseEvent * event)
{
	if(mPressedButton == Qt::LeftButton){
		pItemSpace->MouseMoved(mNowX, mNowY, event->x(), event->y());
		mNowX = event->x();
		mNowY = event->y();
	}
}

void Nansy::paintEvent(QPaintEvent * event )
{
	pItemSpace->reDraw();
	enterEvent(NULL);
	QPainter painter;
	painter.begin(this);	
	painter.drawImage(0, 0, *pMainBufferImage);
//	painter.drawText(QRect(WINWIDTH - 100, WINHEIGHT - 70, 80, 12), Qt::AlignRight, "Nansy");
//	painter.drawText(QRect(WINWIDTH - 200, WINHEIGHT - 40, 180, 12), Qt::AlignRight, tr("Jin Bingwen 10821021"));
	painter.end();
}

void Nansy::showEvent(QShowEvent * event)
{
	static bool first = true;
	if(first){
		this->setFixedSize(WINWIDTH, WINHEIGHT);	
		showAllMenu(QPoint(0, 0));
		hideAllMenu();
	}
}

bool Nansy::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::MouseButtonPress){
		if(pFileMenu->activeAction() || pViewMenu->activeAction() || pSampleMenu->activeAction() || pOptionMenu->activeAction()){
			return QObject::eventFilter(obj, event);
		}
		else{
			hideAllMenu();
			return true;
		}		
	}
	else {
		return QObject::eventFilter(obj, event);
	}
}

void Nansy::enterEvent(QEvent * event)
{
	static int i = 0;
	setWindowTitle(QString::number(++i));
}

void Nansy::showSth()
{
	QWidget *sth = new QWidget;
	sth->show();
}

void Nansy::menuTriggered(QAction* act)
{
	hideAllMenu();
}

void Nansy::hideAllMenu()
{
	pViewMenu->hide();
	pFileMenu->hide();
	pSampleMenu->hide();
	pOptionMenu->hide();
}

void Nansy::showAllMenu(QPoint pos)
{
	QPoint startPos = pos;
	startPos.setY(startPos.y() - pFileMenu->height() - YSEPRATOR);
	startPos.setX(startPos.x() + XSEPRATOR);
	pFileMenu->popup(startPos);
	startPos = pos;
	startPos.setY(startPos.y() + YSEPRATOR);
	startPos.setX(startPos.x() + XSEPRATOR);
	pViewMenu->popup(startPos);
	pSampleMenu->popup(QPoint(pos.x() - XSEPRATOR - pSampleMenu->width(), pos.y() + YSEPRATOR));
	pOptionMenu->popup(QPoint(pos.x() - XSEPRATOR - pOptionMenu->width(), pos.y() - pOptionMenu->height() - YSEPRATOR));
	
}

void Nansy::initMouseState()
{
	mPressedButton = Qt::NoButton;
	mPressX = 0;
	mPressY = 0;
	mReleaseX = 0;
	mReleaseY = 0;
	mNowX = 0;
	mNowY = 0;
}

void Nansy::setViewMode2Fixed()
{
	pItemSpace->SetViewMode(Fixed);
}

void Nansy::setViewMode2Move()
{
	pItemSpace->SetViewMode(Move);
}

void Nansy::setViewMode2Rotate()
{
	pItemSpace->SetViewMode(Rotate);
}

void Nansy::setViewMode2Scale()
{
	pItemSpace->SetViewMode(Scale);
}

void Nansy::resetViewMode()
{
	pItemSpace->SetViewMode(Default);
}

void Nansy::resizeEvent( QResizeEvent * event )
{
	*pMainBufferImage = QImage(event->size().width(), event->size().height(),
		QImage::Format_ARGB32);
}
