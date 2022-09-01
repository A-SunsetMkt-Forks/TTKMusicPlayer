#ifndef MUSICPLAYLIST_H
#define MUSICPLAYLIST_H

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

#include "musicglobaldefine.h"

/*! @brief The class of the music play item.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT MusicPlayItem
{
    int m_toolIndex;
    QString m_path;

    MusicPlayItem()
        : m_toolIndex(-1)
    {

    }

    MusicPlayItem(int index, const QString &path)
        : m_toolIndex(index),
          m_path(path)
    {

    }

    inline bool isValid() const
    {
        return m_toolIndex != -1 && !m_path.isEmpty();
    }

    inline bool operator== (const MusicPlayItem &other) const
    {
        return m_toolIndex == other.m_toolIndex && m_path == other.m_path;
    }
};
TTK_DECLARE_LIST(MusicPlayItem);


/*! @brief The class of the music play list.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicPlaylist : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicPlaylist)
public:
    explicit MusicPlaylist(QObject *parent = nullptr);

    /*!
     * Get current play mode.
     */
    MusicObject::PlayMode playbackMode() const;
    /*!
     * Set current play mode.
     */
    void setPlaybackMode(MusicObject::PlayMode mode);

    /*!
     * Map item index at container.
     */
    int mapItemIndex(const MusicPlayItem &item) const;
    /*!
     * Get current play index.
     */
    int currentIndex() const;
    /*!
     * Get current play item.
     */
    MusicPlayItem currentItem() const;
    /*!
     * Get current play music media path.
     */
    QString currentMediaPath() const;

    /*!
     * Get all music media path.
     */
    MusicPlayItemList *mediaList();
    /*!
     * Get queue music media path.
     */
    MusicPlayItemList *queueList();

    /*!
     * Get current medias count.
     */
    int count() const;
    /*!
     * Check current medias is empty.
     */
    bool isEmpty() const;
    /*!
     * Clear current medias.
     */
    void clear();
    /*!
     * Find item by index and content.
     */
    int find(int toolIndex, const QString &content, int from = 0);

    /*!
     * Add music media, not append remember.
     */
    void add(int toolIndex, const QString &content);
    /*!
     * Add music media list, not append remember.
     */
    void add(int toolIndex, const QStringList &items);
    /*!
     * Add music media list, not append remember.
     */
    void add(const MusicPlayItem &item);
    /*!
     * Add music media list, not append remember.
     */
    void add(const MusicPlayItemList &items);

    /*!
     * Append music medias.
     */
    void append(int toolIndex, const QString &content);
    /*!
     * Append music medias.
     */
    void append(int toolIndex, const QStringList &items);
    /*!
     * Append music media.
     */
    void append(const MusicPlayItem &item);
    /*!
     * Append music medias.
     */
    void append(const MusicPlayItemList &items);
    /*!
     * Append music media by index and content.
     */
    void appendQueue(int toolIndex, const QString &content);

    /*!
     * Remove music media from current medias by index pos.
     */
    bool remove(int pos);
    /*!
     * Remove music media from current medias by index pos.
     */
    int remove(int toolIndex, const QString &content);
    /*!
     * Remove music all queue media.
     */
    void removeQueue();

Q_SIGNALS:
    /*!
     * Current play index changed emit.
     */
    void currentIndexChanged(int index);
    /*!
     * Current play mode changed emit.
     */
    void playbackModeChanged(MusicObject::PlayMode mode);

public Q_SLOTS:
    /*!
     * Set current play index.
     */
    void setCurrentIndex(int index = DEFAULT_LOW_LEVEL);
    /*!
     * Set current play index.
     */
    void setCurrentIndex(int toolIndex, const QString &path);

protected:
    int m_currentIndex;
    MusicPlayItemList m_mediaList;
    MusicPlayItemList m_queueList;
    MusicObject::PlayMode m_playbackMode;

};

#endif // MUSICPLAYLIST_H
