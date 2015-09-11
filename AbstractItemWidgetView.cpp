
#include <QAbstractItemView>
#include "AbstractItemWidget.hpp"
#include "AbstractItemWidgetView.hpp"
#include "AbstractItemWidgetDelegate.hpp"

/* 开始修改Model结构 */
void
AbstractItemWidgetView::beginChangeModelStruct(){
}

/* 结束修改Model结构 */
void
AbstractItemWidgetView::endChangeModelStruct(){
}

/* 打开编辑域 */
AbstractItemWidget *
AbstractItemWidgetView::openPersistentEditorWidget(const QModelIndex &index){
	auto * view_ = this->getWidgetItemView();
	if (view_ == 0) { return 0; }
	auto * delegate_ = view_->itemDelegate();
	auto d_ = qobject_cast<AbstractItemWidgetDelegate *>(delegate_);
	if (d_) {
		return d_->openPersistentEditorWidget(index);
	}
	return 0;
}
/* 关闭编辑域 */
void
AbstractItemWidgetView::closePersistentEditorWidget(const QModelIndex &index){
	auto * view_ = this->getWidgetItemView();
	if (view_ == 0) { return; }
	auto * delegate_ = view_->itemDelegate();
	auto d_ = qobject_cast< AbstractItemWidgetDelegate  *>(delegate_);
	if (d_) {
		return d_->closePersistentEditorWidget(index);
	}
	view_->closePersistentEditor(index);
}
/* 设置模型 */
void
AbstractItemWidgetView::setItemWidgetModel(QAbstractItemModel * model )  {
    if (model == 0) { return; }
    auto * view_ = this->getWidgetItemView();
    if(view_==0){ return; }
    auto * m_ = view_->model();
    if (m_ == model) { return; }
    {
        view_->setModel(model);
    }
    {
        {
            /* 关闭信号槽连接 */
            if (m_) {
                m_->disconnect(view_);
                view_->disconnect(m_);
            }
        }
		{
			/*连接信号槽*/
			view_->connect(
				model, &QAbstractItemModel::columnsAboutToBeInserted,
				view_,[this](const QModelIndex & i, int x, int y) {_columnsAboutToBeInserted(i, x, y); });

			view_->connect(model, &QAbstractItemModel::columnsAboutToBeMoved,
				view_,[this](const QModelIndex & a, int b, int c, const QModelIndex & d, int e) {_columnsAboutToBeMoved(a, b, c, d, e); });

			view_->connect(model, &QAbstractItemModel::columnsAboutToBeRemoved,
				view_,[this](const QModelIndex & a, int b, int c) {this->_columnsAboutToBeRemoved(a, b, c); });

			view_->connect(model, &QAbstractItemModel::columnsInserted,
				view_,[this](const QModelIndex  &a, int b, int c) {  _columnsInserted(a, b, c); });

			view_->connect(model, &QAbstractItemModel::columnsMoved,
				view_,[this](const QModelIndex & a, int b, int c, const QModelIndex & d, int e) {
				_columnsMoved(a,b,c,d,e); });

            view_->connect(model, &QAbstractItemModel::columnsRemoved ,
				view_,[this](const QModelIndex & a, int b, int c) { _columnsRemoved(a,b,c); });

            view_->connect(model, &QAbstractItemModel::modelAboutToBeReset ,
				view_,[this]() {_modelAboutToBeReset(); });

            view_->connect(model, &QAbstractItemModel::modelReset ,
				view_,[this](){_modelReset(); } );

			view_->connect(model, &QAbstractItemModel::rowsAboutToBeInserted,
				view_, [this](const QModelIndex & a, int b, int c) {_rowsAboutToBeInserted(a,b,c); });

			view_->connect(model, &QAbstractItemModel::rowsAboutToBeMoved,
				view_, [this](const QModelIndex & a, int b, int c,const QModelIndex & d, int e) {_rowsAboutToBeMoved(a,b,c,d,e); });

			view_->connect(model, &QAbstractItemModel::rowsAboutToBeRemoved,
				view_, [this](const QModelIndex & a, int b, int c) {_rowsAboutToBeRemoved(a,b,c); });

			view_->connect(model, &QAbstractItemModel::rowsInserted,
				view_, [this](const QModelIndex & a, int b, int c) {_rowsInserted(a,b,c); });

			view_->connect(model, &QAbstractItemModel::rowsMoved,
				view_, [this](const QModelIndex & a, int b, int c,const QModelIndex & d, int e) {_rowsMoved(a,b,c,d,e); });

			view_->connect(model, &QAbstractItemModel::rowsRemoved,
				view_, [this](const QModelIndex & a, int b, int c) {_rowsRemoved(a,b,c); });

        }
    }
}

/**/
