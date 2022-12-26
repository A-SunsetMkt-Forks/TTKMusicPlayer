#ifndef MUSICABSTRACTDOWNLOADTABLEWIDGET_H
#define MUSICABSTRACTDOWNLOADTABLEWIDGET_H

/***************************************************************************
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "musicabstractsongslisttablewidget.h"
#include "musicdownloadrecordconfigmanager.h"

class TTKProgressBarItemDelegate;

/*! @brief The class of the download abstract table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicAbstractDownloadTableWidget : public MusicAbstractSongsListTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicAbstractDownloadTableWidget)
public:
    explicit MusicAbstractDownloadTableWidget(QWidget *parent = nullptr);
    ~MusicAbstractDownloadTableWidget();

    /*!
     * Update songs files in table.
     */
    virtual void updateSongsList(const MusicSongList &songs) override final;

Q_SIGNALS:
    /*!
     * Add current selected song to playlist.
     */
    void addSongToPlaylist(const QStringList &items);
    /*!
     * Update item title.
     */
    void updateItemTitle(int index);

public Q_SLOTS:
    /*!
     * Delete item from list at current row.
     */
    virtual void setDeleteItemAt() override final;
    /*!
     * Add selected music song path to list.
     */
    void musicPlay();
    /*!
     * Table widget item cell double clicked.
     */
    void itemDoubleClicked(int row, int column);
    /*!
     * Update download percent total time and current time progress.
     */
    void downloadProgressChanged(float percent, const QString &total, qint64 time);
    /*!
     * Create download item from download name and total time.
     */
    void createDownloadItem(const QString &name, qint64 time);

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Create cell item by input record.
     * Subclass should implement this function.
     */
    virtual void addCellItem(int index, const MusicSong &record) = 0;

    MusicObject::Record m_type;
    TTKProgressBarItemDelegate *m_progressBarDelegate;

};

#endif // MUSICABSTRACTDOWNLOADTABLEWIDGET_H
