#include <QMenu>

class NansyMenu : public QMenu
{
	Q_OBJECT

public:
	NansyMenu ( const QString & title, QWidget * parent = 0 ) ;
	~NansyMenu();

protected:
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);

signals:
	void entered();
	void leaved();
};