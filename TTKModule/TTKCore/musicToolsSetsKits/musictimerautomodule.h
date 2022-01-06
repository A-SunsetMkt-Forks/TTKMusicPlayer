#ifndef MUSICTIMERAUTOMODULE_H
#define MUSICTIMERAUTOMODULE_H

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

#include <QTimer>

#include "musicglobaldefine.h"

/*! @brief The class of the time check object.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct TTK_MODULE_EXPORT MusicTimeData
{
    int m_index;
    int m_hour;
    int m_minute;
    bool m_state;

    MusicTimeData()
    {
        m_index = -1;
        m_hour = -1;
        m_minute = -1;
        m_state = false;
    }
}MusicTimeData;
TTK_DECLARE_LIST(MusicTimeData)


/*! @brief The class of the time auto run.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicTimerAutoModule : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicTimerAutoModule)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicTimerAutoModule(QObject *parent = nullptr);
    ~MusicTimerAutoModule();

    /*!
     * Run time auto from local file config.
     */
    void runTimerAutoConfig();

public Q_SLOTS:
    /*!
     * Check current state by one minute.
     */
    void timeout();

protected:
    /*!
     * Set current system to shutdown.
     */
    void setShutdown();

    QTimer m_timer;
    MusicTimeDatas m_timeDatas;

};

#endif // MUSICTIMERAUTOMODULE_H
