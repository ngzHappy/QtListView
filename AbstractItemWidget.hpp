
#ifndef __ITEM__WIDGET__VIEW__HPP__
#define __ITEM__WIDGET__VIEW__HPP__

#include <QWidget>
#include <QRect>
#include <QStyleOptionViewItem>

class AbstractItemWidget :
        public QWidget {
    Q_OBJECT
public:
    /* 构造函数 */
    explicit AbstractItemWidget( QWidget * p  ):QWidget(p){}
    AbstractItemWidget() :AbstractItemWidget(nullptr) {}
    /* 析构函数 */
    virtual ~AbstractItemWidget(){}
protected:
    /* 记录item真实位置及大小,用于支持动画 */
    QRect finalRect_;
public:
    const QRect & finalRect() const { return finalRect_; }
    /* 即将删除widget */
    virtual void beforeWidgetDelete() {}

    /* 设置paint数据 */
    virtual void beforePaint(
            const QStyleOptionViewItem & option,
            const QModelIndex & index) {
   		finalRect_ = option.rect;
        this->setEditorData(index);
    }

    /* 设置模型数据 */
    virtual void setModelData(
            QAbstractItemModel * model,
            const QModelIndex & index
            ) const{
        (void) model;
        (void) index;
    }

    /* 重新设置数据 */
    virtual void setEditorData(
            const QModelIndex & index
            )  {
        (void) index;
    }

    /* 构造 */
    virtual AbstractItemWidget * instance(
            QWidget * parent,
            const QStyleOptionViewItem & option,
            const QModelIndex & index
            ){
        this->setParent(parent);
        this->beforePaint(option,index);
        return this;
    }

	virtual void updateEditorGeometry(
		const QStyleOptionViewItem & option,
		const QModelIndex & index)   {
		(void)index;
		finalRect_ = option.rect;
		this->setGeometry(finalRect_);
	}

};




#endif

