#ifndef MUSICITEMSEARCHEDIT_H
#define MUSICITEMSEARCHEDIT_H

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

#include "musicsearchedit.h"

/*! @brief The class of the search line edit widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicItemSearchEdit : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicItemSearchEdit)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicItemSearchEdit(QWidget *parent = nullptr);
    ~MusicItemSearchEdit();

    /*!
     * Get the line eidtor.
     */
    inline MusicSearchEdit* editor() const { return m_searchEdit; }
    inline MusicSearchEdit* operator()() const { return m_searchEdit; }

private:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override final;

    MusicSearchEdit *m_searchEdit;

};


/*! @brief The class of the query line edit widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicItemQueryEdit : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicItemQueryEdit)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicItemQueryEdit(QWidget *parent = nullptr);
    ~MusicItemQueryEdit();

    /*!
     * Get the line eidtor.
     */
    inline MusicSearchEdit* editor() const { return m_searchEdit; }
    inline MusicSearchEdit* operator()() const { return m_searchEdit; }

Q_SIGNALS:
    /*!
     * Trigger the item.
     */
    void trigger(const QString &text);

private Q_SLOTS:
    /*!
     * User input the enter key.
     */
    void enterFinished();

private:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override final;

    MusicSearchEdit *m_searchEdit;

};

#endif // MUSICITEMSEARCHEDIT_H
