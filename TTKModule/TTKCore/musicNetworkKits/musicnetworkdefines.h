#ifndef MUSICNETWORKDEFINES_H
#define MUSICNETWORKDEFINES_H

/***************************************************************************
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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

/*! @brief The namespace of the network data.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    enum class NetworkCode
    {
        Query = 0xFF00,    /*!< Network state query*/
        Success = 0,       /*!< Network state success*/
        Error = -1,        /*!< Network state error*/
        UnKnow = 2,        /*!< Network state unknow*/
    };

    enum class Download
    {
        Music,             /*!< type of dwonlaod music*/
        Lrc,               /*!< type of dwonlaod lrc*/
        Cover,             /*!< type of dwonlaod cover*/
        Background,        /*!< type of dwonlaod background*/
        Video,             /*!< type of dwonlaod video*/
        Other              /*!< type of dwonlaod other user mod*/
    };

    enum class Record
    {
        Null,              /*!< None File Config*/
        NormalDownload,    /*!< Local Download File Config*/
        CloudDownload,     /*!< Cloud Download File Config*/
        CloudUpload        /*!< Cloud Upload Failed File Config*/
    };
}

#define DOWNLOAD_KEY_MUSIC      "DownloadMusic"
#define DOWNLOAD_KEY_LRC        "DownloadLrc"
#define DOWNLOAD_KEY_COVER      "DownloadCover"
#define DOWNLOAD_KEY_BACKGROUND "DownloadBackground"
#define DOWNLOAD_KEY_VIDEO      "DownloadVideo"
#define DOWNLOAD_KEY_OTHER      "DownloadOther"

#endif // MUSICNETWORKDEFINES_H
