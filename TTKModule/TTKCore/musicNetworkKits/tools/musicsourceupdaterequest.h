#ifndef MUSICSOURCEUPDATEREQUEST_H
#define MUSICSOURCEUPDATEREQUEST_H

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

#include <QVariantMap>
#include "ttkversion.h"
#include "musicglobaldefine.h"

/*! @brief The class of source data query pdate request.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicSourceUpdateRequest : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicSourceUpdateRequest)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSourceUpdateRequest(QObject *parent = nullptr);

    /*!
     * Start to download data from net.
     */
    void startRequest();

    /*!
     * Get lasted version.
     */
    QString version() const;
    /*!
     * Get lasted version description.
     */
    QString versionDescription() const;
    /*!
     * Is lasted version.
     */
    bool isLastedVersion() const;

Q_SIGNALS:
    /*!
     * Send download data from net.
     */
    void downLoadDataChanged(const QVariant &bytes);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    void downLoadFinished(const QByteArray &bytes);

private:
    QVariantMap m_rawData;

};

#endif // MUSICSOURCEUPDATEREQUEST_H
