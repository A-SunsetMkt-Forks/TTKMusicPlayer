#include "musiclrcsearchtablewidget.h"
#include "musictoastlabel.h"
#include "musicitemdelegate.h"
#include "musicdownloadqueryfactory.h"
#include "musicgiflabelwidget.h"

MusicLrcSearchTableWidget::MusicLrcSearchTableWidget(QWidget *parent)
    : MusicItemSearchTableWidget(parent)
{
    setColumnCount(7);

    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 30);
    headerview->resizeSection(1, 213);
    headerview->resizeSection(2, 181);
    headerview->resizeSection(3, 55);
    headerview->resizeSection(4, 24);
    headerview->resizeSection(5, 24);
    headerview->resizeSection(6, 24);
}

MusicLrcSearchTableWidget::~MusicLrcSearchTableWidget()
{
    removeItems();
}

void MusicLrcSearchTableWidget::startSearchQuery(const QString &text)
{
    if(!G_NETWORK_PTR->isOnline())   //no network connection
    {
        removeItems();
        return;
    }

    MusicItemSearchTableWidget::startSearchQuery(text);
    connect(m_networkRequest, SIGNAL(downLoadDataChanged(QString)), SIGNAL(resolvedSuccess()));
    m_loadingLabel->run(true);
    m_networkRequest->startToSearch(MusicAbstractQueryRequest::QueryType::Lrc, text);
}

void MusicLrcSearchTableWidget::musicDownloadLocal(int row)
{
    if(row < 0 || (row >= rowCount() - 1))
    {
        MusicToastLabel::popup(tr("Please select one item first!"));
        return;
    }

    const MusicObject::MusicSongInformationList songInfos(m_networkRequest->songInfoList());
    ///download lrc
    MusicAbstractDownLoadRequest *d = G_DOWNLOAD_QUERY_PTR->makeLrcRequest(songInfos[row].m_lrcUrl,
                                      MusicUtils::String::lrcDirPrefix() + m_networkRequest->queryValue() + LRC_FILE, this);
    connect(d, SIGNAL(downLoadDataChanged(QString)), SIGNAL(lrcDownloadStateChanged(QString)));
    d->startRequest();
}

void MusicLrcSearchTableWidget::itemCellEntered(int row, int column)
{
    MusicItemSearchTableWidget::itemCellEntered(row, column);
    if(column == 6)
    {
        setCursor(QCursor(Qt::PointingHandCursor));
    }
    else
    {
        unsetCursor();
    }
}

void MusicLrcSearchTableWidget::itemCellClicked(int row, int column)
{
    MusicItemSearchTableWidget::itemCellClicked(row, column);
    switch(column)
    {
        case 6: musicDownloadLocal(row); break;
        default: break;
    }
}

void MusicLrcSearchTableWidget::itemDoubleClicked(int row, int column)
{
    if(column <= 0)
    {
        return;
    }

    musicDownloadLocal(row);
}

void MusicLrcSearchTableWidget::removeItems()
{
    MusicItemSearchTableWidget::removeItems();
    setColumnCount(7);
}

void MusicLrcSearchTableWidget::createSearchedItem(const MusicResultInfoItem &songItem)
{
    const int count = rowCount();
    setRowCount(count + 1);

    QHeaderView *headerview = horizontalHeader();
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(TTK_CHECKED_ROLE, Qt::Unchecked);
    setItem(count, 0, item);

                      item = new QTableWidgetItem;
    item->setToolTip(songItem.m_songName);
    item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 20));
    QtItemSetForegroundColor(item, QColor(MusicUIObject::MQSSColor02));
    setItem(count, 1, item);

                      item = new QTableWidgetItem;
    item->setToolTip(songItem.m_singerName);
    item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(2) - 20));
    QtItemSetForegroundColor(item, QColor(MusicUIObject::MQSSColor02));
    setItem(count, 2, item);

                      item = new QTableWidgetItem(songItem.m_duration);
    QtItemSetForegroundColor(item, QColor(MusicUIObject::MQSSColor02));
    setItem(count, 3, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(randSimulation()));
    setItem(count, 4, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(":/tiny/lb_server_type"));
    item->setToolTip(songItem.m_type);
    setItem(count, 5, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(":/contextMenu/btn_download"));
    setItem(count, 6, item);
}

void MusicLrcSearchTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
    MusicItemSearchTableWidget::contextMenuEvent(event);

    QMenu menu(this);
    createContextMenu(menu);
    menu.exec(QCursor::pos());
}
