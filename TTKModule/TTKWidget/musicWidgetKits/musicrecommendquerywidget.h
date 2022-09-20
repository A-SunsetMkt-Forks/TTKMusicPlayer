#ifndef MUSICRECOMMENDQUERYWIDGET_H
#define MUSICRECOMMENDQUERYWIDGET_H

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

#include "musicabstractitemquerywidget.h"
#include "musicitemquerytablewidget.h"

/*! @brief The class of the recommend music query table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicRecommendQueryTableWidget : public MusicItemQueryTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicRecommendQueryTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicRecommendQueryTableWidget(QWidget *parent = nullptr);
    ~MusicRecommendQueryTableWidget();

    /*!
     * Set network query input.
     */
    virtual void setQueryInput(MusicAbstractQueryRequest *query) override final;

public Q_SLOTS:
    /*!
     * Create searched items.
     */
    virtual void createSearchedItem(const MusicSearchedItem &songItem) override final;

};


/*! @brief The class of recommend music query widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicRecommendQueryWidget : public MusicAbstractItemQueryWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicRecommendQueryWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicRecommendQueryWidget(QWidget *parent = nullptr);

    /*!
     * Set current name to search founds.
     */
    virtual void setSongName(const QString &name) override final;
    /*!
     * Set current id to search founds.
     */
    virtual void setSongNameById(const QString &id) override final;

    /*!
     * Resize window bound by widget resize called.
     */
    void resizeWindow();

public Q_SLOTS:
    /*!
     * Query all quality musics is finished.
     */
    void queryAllFinished();

protected:
    /*!
     * Create init interface lables.
     */
    void createLabels();

};


#endif // MUSICRECOMMENDQUERYWIDGET_H
