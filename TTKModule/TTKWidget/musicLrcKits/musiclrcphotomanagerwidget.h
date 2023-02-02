#ifndef MUSICLRCPHOTOMANAGERWIDGET_H
#define MUSICLRCPHOTOMANAGERWIDGET_H

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

#include <QGridLayout>
#include "musicabstractmovedialog.h"

/*! @brief The class of the lrc photo pixmap item.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicLrcPhotoItem : public QLabel
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLrcPhotoItem)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLrcPhotoItem(QWidget *parent = nullptr);

    /*!
     * Update pix image.
     */
    void updatePixmap(const QString &path);

    /*!
     * Select the current item.
     */
    void setSelected(bool v);
    /*!
     * Get current selected item state.
     */
    inline bool isSelected() const { return m_isSelected; }

    /*!
     * Get current item apth.
     */
    inline QString path() const { return m_path; }

private:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override final;
    virtual void paintEvent(QPaintEvent *event) override final;

    QString m_path;
    bool m_isSelected;

};


/*! @brief The class of the lrc photo widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicLrcPhotoWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLrcPhotoWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLrcPhotoWidget(QWidget *parent = nullptr);
    ~MusicLrcPhotoWidget();

    /*!
     * Create cell item by input data.
     */
    void addCellItem(const QString &path);

public Q_SLOTS:
    /*!
     * Add button clicked.
     */
    void addButtonClicked();
    /*!
     * Delete button clicked.
     */
    void deleteButtonClicked();
    /*!
     * Export button clicked.
     */
    void exportButtonClicked();

private:
    /*!
     * Create all widget in layout.
     */
    void initialize();
    /*!
     * Check current selection is valid or not.
     */
    bool isValid() const;

    QGridLayout *m_gridLayout;
    QList<MusicLrcPhotoItem*> m_items;

};


namespace Ui {
class MusicLrcPhotoManagerWidget;
}

/*! @brief The class of the lrc art photo upload.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicLrcPhotoManagerWidget : public MusicAbstractMoveDialog
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLrcPhotoManagerWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLrcPhotoManagerWidget(QWidget *parent = nullptr);
    ~MusicLrcPhotoManagerWidget();

private:
    Ui::MusicLrcPhotoManagerWidget *m_ui;

    MusicLrcPhotoWidget *m_photoWidget;

};

#endif // MUSICLRCPHOTOMANAGERWIDGET_H
