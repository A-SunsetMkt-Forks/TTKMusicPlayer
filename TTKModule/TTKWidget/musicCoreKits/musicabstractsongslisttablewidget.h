#ifndef MUSICABSTRACTSONGSLISTTABLEWIDGET_H
#define MUSICABSTRACTSONGSLISTTABLEWIDGET_H

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

#include <QMenu>
#include "musicsong.h"
#include "musicsmoothmovingwidget.h"

/*! @brief The class of the songs list abstract table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicAbstractSongsListTableWidget : public MusicSmoothMovingTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicAbstractSongsListTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicAbstractSongsListTableWidget(QWidget *parent = nullptr);
    ~MusicAbstractSongsListTableWidget();

    /*!
     * Set songs file names.
     */
    virtual void setSongsFileName(MusicSongList *songs);
    /*!
     * Update songs file names in table.
     */
    virtual void updateSongsFileName(const MusicSongList &songs);
    /*!
     * Select the current play row by given index.
     */
    virtual void selectRow(int index);

    /*!
     * Get all rows height.
     */
    int totalHeight() const;
    /*!
     * Set tool index.
     */
    void setToolIndex(int index);
    /*!
     * Get the current play row.
     */
    inline void setPlayRowIndex(int index) { m_playRowIndex = index; }
    /*!
     * Get the current play row.
     */
    inline int playRowIndex() const { return m_playRowIndex; }

Q_SIGNALS:
    /*!
     * Check is current play stack widget.
     */
    void isCurrentIndex(bool &state);

public Q_SLOTS:
    /*!
     * Delete item from list at current row.
     */
    virtual void setDeleteItemAt();
    /*!
     * Music item has been clicked.
     */
    void musicPlayClicked();
    /*!
     * Delete all items from list.
     */
    void setDeleteItemAll();
    /*!
     * Open the music at local path.
     */
    void musicOpenFileDir();
    /*!
     * Open music file information widget.
     */
    void musicFileInformation();
    /*!
     * To search song mv by song name.
     */
    void musicSongMovieFound();
    /*!
     * Open music album query widget.
     */
    void musicAlbumQueryWidget();
    /*!
     * Open music similar query widget.
     */
    void musicSimilarQueryWidget();
    /*!
     * Open music song shared widget.
     */
    void musicSongSharedWidget();
    /*!
     * Open music song download widget.
     */
    void musicSongDownload();
    /*!
     * To search song mv by song name in play widget.
     */
    void musicSongPlayedMovieFound();
    /*!
     * Open music similar query widget in play widget.
     */
    void musicPlayedSimilarQueryWidget();
    /*!
     * Open music song shared widget in play widget.
     */
    void musicSongPlayedSharedWidget();
    /*!
     * Open music song KMicro widget in play widget.
     */
    void musicSongPlayedKMicroWidget();

protected:
    /*!
     * Create more menu information.
     */
    void createMoreMenu(QMenu *menu);
    /*!
     * Get current song path.
     */
    QString currentSongPath() const;
    /*!
     * Get song path.
     */
    QString songPath(int index) const;
    /*!
     * Get current song name.
     */
    QString currentSongName() const;
    /*!
     * Get song name.
     */
    QString songName(int index) const;

    int m_toolIndex;
    int m_playRowIndex;
    MusicSongList *m_songs;
    bool m_hasParentToolIndex;

};

#endif // MUSICABSTRACTSONGSLISTTABLEWIDGET_H
