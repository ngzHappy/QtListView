
#ifndef __ITEM_Delegate_WIDGET__VIEW_VIEW_HPP__
#define __ITEM_Delegate_WIDGET__VIEW_VIEW_HPP__

class AbstractItemWidget    ;
class AbstractItemWidgetView;

#include <QStyledItemDelegate>
#include <functional>

class AbstractItemWidgetDelegate :
        public QStyledItemDelegate {
    Q_OBJECT
protected:
	AbstractItemWidgetView * view = 0;
	/* 设置视图 */
	void setView(AbstractItemWidgetView * v) { view = v; }
public:
	typedef std::function<AbstractItemWidget*()> CreatEditorFunctionType;
public:
    /* 构造函数 */
    AbstractItemWidgetDelegate(AbstractItemWidgetView * ,QObject *  );
    AbstractItemWidgetDelegate(AbstractItemWidgetView * v):AbstractItemWidgetDelegate(v,nullptr){}
	AbstractItemWidgetDelegate(AbstractItemWidgetView * v,const CreatEditorFunctionType & f, QObject *p):AbstractItemWidgetDelegate(v,p) {
		setCreatEditorFunction(f);
	}
	 
    /* 析构函数 */
	virtual ~AbstractItemWidgetDelegate();

	/*读取视图*/
	AbstractItemWidgetView * getView() const{ return view; }

	/*创建Item*/
	QWidget * createEditor(
		QWidget * parent,
		const QStyleOptionViewItem & option,
		const QModelIndex & index) const override;

	/*绘制item*/
	void paint(
		QPainter * painter,
		const QStyleOptionViewItem & option,
		const QModelIndex & index) const override;

	/*获得item的高 长没用忽略*/
	QSize sizeHint(
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;

	/*设置model data*/
	void setModelData(
		QWidget * editor,
		QAbstractItemModel * model,
		const QModelIndex & index) const override;

	/*设置item data*/
	void setEditorData(
		QWidget * editor,
		const QModelIndex & index) const override;

	virtual void updateEditorGeometry(
		QWidget *,
		const QStyleOptionViewItem & option,
		const QModelIndex & index)  const override;

	virtual AbstractItemWidget *openPersistentEditorWidget(const QModelIndex &index) const;
	virtual void closePersistentEditorWidget(const QModelIndex &index) const;

    virtual void closeAllWidgetItem();
protected:
	bool event(QEvent * e) override;

private:
	class ThisPrivate;
	friend class ThisPrivate;
	ThisPrivate * thisp = 0;
private:
	CreatEditorFunctionType creat_editor_function;
public:
	const auto & getCreatEditorFuncton() const { return creat_editor_function; }
private:
	void setCreatEditorFunction(const CreatEditorFunctionType & i) {
		creat_editor_function = i;
	}
};



#endif


