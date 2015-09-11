#ifndef __ITEM__WIDGET__VIEW__H0PP__
#define __ITEM__WIDGET__VIEW__H0PP__

#include "AbstractItemWidget.hpp"
#include "AbstractItemWidgetDelegate.hpp"
#include "AbstractItemWidgetView.hpp"
#include <QEvent>

template<typename ViewBaseType>
class ItemWidgetView  :
        public ViewBaseType ,
        public AbstractItemWidgetView
{
    bool isOnChangingStruct = false;
public:

    QAbstractItemView * getWidgetItemView() const override {
        return (QAbstractItemView *)this;
    }

    void beginChangeModelStruct(){
        if(this->isAbstractItemWidgetViewOnDestory()){return;}
        isOnChangingStruct=true;
        auto* d_ = qobject_cast<AbstractItemWidgetDelegate *>(this->itemDelegate());
        if (d_) { d_->closeAllWidgetItem(); }
    }

    void endChangeModelStruct(){
        if(this->isAbstractItemWidgetViewOnDestory()){return;}
        isOnChangingStruct=false;
        this->viewport()->update();
    }

protected:
    void paintEvent(QPaintEvent *e) override{
        /* 在model struct改变期间禁止重绘 */
        if(isOnChangingStruct){return;}
        ViewBaseType::paintEvent(e);
    }
    bool viewportEvent(QEvent *event) override{
        /* 在model struct改变期间禁止重绘 */
        if(isOnChangingStruct&&(event->type() == QEvent::Paint)){
            return true;
        }
        return ViewBaseType::viewportEvent(event);
    }
public:
    explicit ItemWidgetView( QWidget * s =0): ViewBaseType(s){}
    ~ItemWidgetView() {
		/* 关闭绘制体系 */
        isOnChangingStruct = true;
		/* 关闭所有item widget */
        auto * d_ = qobject_cast<AbstractItemWidgetDelegate *>(this->itemDelegate());
        if (d_) { d_->closeAllWidgetItem(); }
    }
};


#endif


