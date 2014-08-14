#ifndef NANSY_H
#define NANSY_H

#include <QWidget>
#include <QImage>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QPoint>
#include "NansyMenu.h"
#include "ItemSpace.h"


#define YSEPRATOR 10
#define XSEPRATOR 10

class Nansy : public QWidget
{
	Q_OBJECT

public:
	Nansy(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Nansy();

private:
	//gui element
	QImage *pMainBufferImage;
	NansyMenu *pFileMenu, *pViewMenu, *pSampleMenu, *pOptionMenu;
	QAction *pfOpenAction, *pfClearAction;
	QAction *pvRotateAction, *pvMoveAction, *pvScaleAction, *pvResetAction, *pvFixAction;
	QAction *psRndTriAction, *psElfAction, *psGirlAction, *psPlantAction;
	QAction *poLightAction, *poDirAction, *poNormAction, *poColorAction, *poSmoothAction, *poLineAction;
	void initMenu();

	//
	MidSpace *midSpace;
	ItemSpace* pItemSpace;

	//
	Qt::MouseButton mPressedButton;
	int mPressX, mPressY, mReleaseX, mReleaseY, mNowX, mNowY;
	void initMouseState();

protected:
	virtual void mouseReleaseEvent ( QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void paintEvent ( QPaintEvent *);
	virtual void showEvent(QShowEvent *);
	virtual bool eventFilter(QObject *, QEvent *);
	virtual void enterEvent(QEvent *);
	virtual void resizeEvent(QResizeEvent * event);

private slots:
	void showSth();
	void menuTriggered(QAction*);
	void hideAllMenu();
	void showAllMenu(QPoint);
	void setViewMode2Move();
	void setViewMode2Rotate();
	void setViewMode2Scale();
	void setViewMode2Fixed();
	void resetViewMode();

};

#endif // NANSY_H
