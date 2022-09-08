#include "musicdownloadrecordwidget.h"
#include "musicitemdelegate.h"
#include "musicwidgetheaders.h"
#include "musicconnectionpool.h"

MusicDownloadRecordTableWidget::MusicDownloadRecordTableWidget(QWidget *parent)
    : MusicAbstractDownloadTableWidget(parent)
{
    setColumnCount(4);

    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 10);
    headerview->resizeSection(1, 168);
    headerview->resizeSection(2, 83);
    headerview->resizeSection(3, 50);

    m_type = MusicObject::Record::NormalDownload;
    setItemDelegateForColumn(2, m_delegate);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    MusicUtils::Widget::setTransparent(this, 0);
    verticalScrollBar()->setStyleSheet(MusicUIObject::MQSSScrollBarStyle03);

    G_CONNECTION_PTR->setValue(className(), this);
}

MusicDownloadRecordTableWidget::~MusicDownloadRecordTableWidget()
{
    G_CONNECTION_PTR->removeValue(className());
}

void MusicDownloadRecordTableWidget::createItem(int index, const MusicSong &record)
{
    QHeaderView *headerview = horizontalHeader();
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(index, 0, item);

                      item = new QTableWidgetItem;
    item->setToolTip(record.name());
    item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 20));
    QtItemSetForegroundColor(item, QColor(MusicUIObject::MQSSColor01));
    QtItemSetTextAlignment(item, Qt::AlignLeft | Qt::AlignVCenter);
    setItem(index, 1, item);

                      item = new QTableWidgetItem;
    item->setData(MUSIC_PROGRESS_ROLE, 100);
    setItem(index, 2, item);

                      item = new QTableWidgetItem(record.sizeStr());
    QtItemSetForegroundColor(item, QColor(MusicUIObject::MQSSColor01));
    QtItemSetTextAlignment(item, Qt::AlignRight| Qt::AlignVCenter);
    item->setData(MUSIC_TIME_ROLE, record.addTimeStr());
    setItem(index, 3, item);

    setFixedHeight(totalHeight());
}



MusicDownloadToolBoxWidget::MusicDownloadToolBoxWidget(QWidget *parent)
    : MusicFunctionToolBoxWidget(parent)
{
    MusicDownloadRecordTableWidget *downloadTable = new MusicDownloadRecordTableWidget(this);
    m_songItems << MusicSongItem();
    createWidgetItem(downloadTable, tr("Download"), 0);

    connect(downloadTable, SIGNAL(updateItemTitle(int)), SLOT(updateItemTitle(int)));
}

MusicDownloadToolBoxWidget::~MusicDownloadToolBoxWidget()
{
    while(!m_songItems.isEmpty())
    {
        delete m_songItems.back().m_itemObject;
        m_songItems.pop_back();
    }
}

void MusicDownloadToolBoxWidget::updateItemTitle(int index)
{
    if(index == 0)
    {
        const MusicSongItem *item = &m_songItems[index];
        setTitle(item->m_itemObject, QString("%1[%2]").arg(item->m_itemName).arg(item->m_songs.count()));
    }
}

void MusicDownloadToolBoxWidget::createWidgetItem(MusicAbstractDownloadTableWidget *widget, const QString &text, int index)
{
    MusicSongItem *item = &m_songItems.back();
    item->m_itemName = text;
    item->m_itemIndex = index;
    item->m_itemObject = widget;
    addItem(widget, item->m_itemName);

    widget->setToolIndex(item->m_itemIndex);
    widget->setSongsFileName(&item->m_songs);

    setTitle(widget, QString("%1[%2]").arg(item->m_itemName).arg(item->m_songs.count()));
}

MusicFunctionToolBoxWidgetItem *MusicDownloadToolBoxWidget::createItem(QWidget *item, const QString &text)
{
    MusicFunctionToolBoxWidgetItem *it = new MusicNormalToolBoxWidgetItem(m_itemIndexRaise, text, this);
    it->addItem(item);
    it->setItemExpand(true);
    return it;
}
