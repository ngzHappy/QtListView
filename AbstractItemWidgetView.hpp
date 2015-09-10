
#ifndef __ITEM__WIDGET__VIEW_VIEW_HPP__
#define __ITEM__WIDGET__VIEW_VIEW_HPP__

class QAbstractItemView;
class AbstractItemWidget;
class QAbstractItemModel;
class QModelIndex;

class AbstractItemWidgetView{
	bool isAbstractItemWidgetViewOnDestory_ = false;
public:
    /* 构造函数 */
    AbstractItemWidgetView(){}
    /* 析构函数 */
	virtual ~AbstractItemWidgetView() { isAbstractItemWidgetViewOnDestory_ = true; }
	/* 查看是否在析构 */
	bool isAbstractItemWidgetViewOnDestory() const {
		return isAbstractItemWidgetViewOnDestory_;
	}
    /* 删除构造函数 */
    AbstractItemWidgetView(const AbstractItemWidgetView &) =delete;
    AbstractItemWidgetView(AbstractItemWidgetView &&) =delete;
    /* 删除拷贝构造函数 */
    AbstractItemWidgetView & operator=(const AbstractItemWidgetView &) =delete;
    AbstractItemWidgetView & operator=(AbstractItemWidgetView &&) =delete;
public:
    /* 获得视图 */
    virtual QAbstractItemView * getWidgetItemView() const = 0;
protected:
    /* 开始修改Model结构 */
    virtual void beginChangeModelStruct();
    /* 结束修改Model结构 */
    virtual void endChangeModelStruct();
public:
    /* 打开编辑域 */
    virtual AbstractItemWidget * openPersistentEditorWidget(const QModelIndex & );
    /* 关闭编辑域 */
    virtual void closePersistentEditorWidget(const QModelIndex & );
private:
    /* 与改变Model结构相关的函数 */
    void _columnsAboutToBeInserted(const QModelIndex &, int, int) { beginChangeModelStruct(); }
    void _columnsAboutToBeMoved(const QModelIndex &,int,int,const QModelIndex &,int) { beginChangeModelStruct(); }
    void _columnsAboutToBeRemoved(const QModelIndex &, int, int) { beginChangeModelStruct(); }
    void _rowsAboutToBeInserted(const QModelIndex &, int, int) { beginChangeModelStruct(); }
    void _modelAboutToBeReset() { beginChangeModelStruct(); }
    void _rowsAboutToBeMoved(const QModelIndex &, int, int, const QModelIndex &, int) { beginChangeModelStruct(); }
    void _rowsAboutToBeRemoved(const QModelIndex &, int, int) { beginChangeModelStruct(); }

    void _columnsInserted(const QModelIndex &  , int , int ) { endChangeModelStruct(); }
    void _columnsMoved(const QModelIndex &, int, int, const QModelIndex &, int  ) { endChangeModelStruct(); }
    void _columnsRemoved(const QModelIndex &  , int  , int  ) { endChangeModelStruct(); }
    void _modelReset() { endChangeModelStruct(); }
    void _rowsInserted(const QModelIndex &  , int  , int  ) { endChangeModelStruct(); }
    void _rowsMoved(const QModelIndex &  , int  , int  , const QModelIndex &  , int  ) { endChangeModelStruct(); }
    void _rowsRemoved(const QModelIndex &  , int  , int  ) { endChangeModelStruct(); }
public:
    /* 设置模型 */
    virtual void setItemWidgetModel( QAbstractItemModel *  )  ;
private:
 
};


#endif
