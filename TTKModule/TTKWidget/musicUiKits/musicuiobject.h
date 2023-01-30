#ifndef MUSICUIOBJECT_H
#define MUSICUIOBJECT_H

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

#include "ttkglobal.h"

/*! @brief The namespace of the application ui object.
 * @author Greedysky <greedysky@163.com>
 */
namespace MusicUIObject
{
///Color
    const QString Color01 = "#444444";

    const QString Color02 = "#646464";

///Color
    const QString ColorStyle01 = " \
            color:#FFFFFF;";

    const QString ColorStyle02 = " \
            color:#E67300;";

    const QString ColorStyle03 = " \
            color:#888888;";

    const QString ColorStyle04 = " \
            color:#AAAAAA;";

    const QString ColorStyle05 = " \
            color:#FF0000;";

    const QString ColorStyle06 = " \
            color:#F4F4F4;";

    const QString ColorStyle07 = " \
            color:#A0630B;";

    const QString ColorStyle08 = " \
            color:#158FE1;";

    const QString ColorStyle09 = " \
            color:#444444;";

    const QString ColorStyle10 = " \
            color:#169AF3;";

    const QString ColorStyle11 = " \
            color:#000000;";

    const QString ColorStyle12 = " \
            color:#FFF697;";

///Background
    const QString BackgroundStyle01 = " \
            background-color:transparent; " +
#ifdef Q_OS_UNIX
            QString("border-style:falt;") +
#endif
            QString();

    const QString BackgroundStyle02 = " \
            background-color:rgb(0, 0, 0);";

    const QString BackgroundStyle03 = " \
            background-color:rgba(0, 0, 0, 35);";

    const QString BackgroundStyle04 = " \
            background-color:rgba(0, 0, 0, 50);";

    const QString BackgroundStyle05 = " \
            background-color:rgba(0, 0, 0, 100);";

    const QString BackgroundStyle06 = " \
            background-color:rgba(0, 0, 0, 140);";

    const QString BackgroundStyle07 = " \
            background-color:rgba(0, 0, 0, 175);";

    const QString BackgroundStyle08 = " \
            background-color:rgb(41, 41, 41);";

    const QString BackgroundStyle09 = " \
            background-color:rgb(240, 240, 240);";

    const QString BackgroundStyle10 = " \
            background-color:rgb(255, 255, 255);";

    const QString BackgroundStyle11 = " \
            background-color:rgba(255, 255, 255, 200);";

    const QString BackgroundStyle12 = " \
            background-color:rgb(250, 231, 191);";

    const QString BackgroundStyle13 = " \
            background-color:rgb(254, 249, 229);";

///border
    const QString BorderStyle01 = " \
            border:none;";

    const QString BorderStyle02 = " \
            border:1px solid #666666;";

    const QString BorderStyle03 = " \
            border:1px solid gray;";

    const QString BorderStyle04 = " \
            border:1px solid #0095CD;";

    const QString BorderStyle05 = " \
            border-top:1px dashed gray;";

    const QString BorderStyle06 = " \
            border-radius:3px;";

    const QString BorderStyle07 = " \
            border-top-left-radius:5px; border-top-right-radius:5px;";

///Font
    const QString FontStyle01 = " \
            font-weight:bold;";

    const QString FontStyle02 = " \
            font-size:12px;";

    const QString FontStyle03 = " \
            font-size:15px;";

    const QString FontStyle04 = " \
            font-size:20px;";

    const QString FontStyle05 = " \
            font-size:25px;";

///Custom
    const QString CustomStyle01 = " \
            text-align:left;";

    const QString CustomStyle02 = " \
            text-align:center;";

///ToolButton
    const QString ToolButtonStyle01 = " \
            QToolButton{ background-color:transparent; " +
#ifdef Q_OS_UNIX
            QString("border-style:falt;") +
#endif
            QString("}");

    const QString ToolButtonStyle02 = " \
            QToolButton::hover{ border:1px solid #000000; }";

    const QString ToolButtonStyle03 = " \
            QToolButton{ border:none; }";

    const QString ToolButtonStyle04 = ToolButtonStyle01 + ToolButtonStyle03 + " \
            QToolButton::hover{ background-color:rgba(255, 255, 255, 20); }";

    const QString ToolButtonStyle05 = ToolButtonStyle01 + " \
            QToolButton::menu-indicator{ image:None; }";

    const QString ToolButtonStyle06 = " \
            QToolButton{ border:1px solid #777777; background:#FFFFFF; color:#555555; } \
            QToolButton::hover{ border:1px solid #444444; color:#222222; } \
            QToolButton::disabled{ color:#999999; border:1px solid #BBBBBB; }";

///PushButton
    const QString PushButtonStyle01 = " \
            QPushButton{ background-color:transparent; " +
#ifdef Q_OS_UNIX
            QString("border-style:falt;") +
#endif
            QString("}");

    const QString PushButtonStyle02 = PushButtonStyle01 + " \
            QPushButton{ border-none; }";

    const QString PushButtonStyle03 = " \
            QPushButton{ border-radius:3px; background-color:#158FE1; color:white; } \
            QPushButton::disabled{ background-color:#BBBBBB; }";

    const QString PushButtonStyle04 = " \
            QPushButton{ border:1px solid #AAAAAA; background:#FFFFFF; color:#777777; } \
            QPushButton::hover{ border:1px solid #555555; color:#444444; } \
            QPushButton::disabled{ color:#BBBBBB; border:1px solid #DDDDDD; }";

    const QString PushButtonStyle05 = PushButtonStyle03 + " \
            QPushButton{ font-size:17px; font-weight:bold; }";

    const QString PushButtonStyle06 = " \
            QPushButton{ color:#CCCCCC; } \
            QPushButton:hover{ color:#FFFFFF; }";
           
    const QString PushButtonStyle07 = PushButtonStyle06 + " \
            QPushButton{ text-align:right; }";

    const QString PushButtonStyle08 = " \
            QPushButton{ border-radius:5px; font-size:20px; \
            background:rgba(0, 0, 0, 50); } \
            QPushButton::hover{ background:rgba(0, 0, 0, 100); }";

    const QString PushButtonStyle09 = " \
            QPushButton{ border-radius:2px; background:rgba(0, 0, 0, 50); }";

    const QString PushButtonStyle10 = " \
            QPushButton::menu-indicator{ image:none; }";

    const QString PushButtonStyle11 = " \
            QPushButton{ color:#E6C117; } \
            QPushButton:hover{ color:#E6E317; } \
            QPushButton{ text-align:right; }";

    const QString PushButtonStyle12 = " \
            QPushButton{ background-color:#DDDDDD; color:#222222; }";

    const QString PushButtonStyle13 = " \
            QPushButton{ color:#444444; }";

///RadioButton
    const QString RadioButtonStyle01 = " \
            QRadioButton{ background-color:transparent; } \
            QRadioButton::indicator::unchecked{ image:url(:/control/btn_radioButton_unchecked); } \
            QRadioButton::checked{ color:#E67300; } \
            QRadioButton::indicator:checked{ image:url(:/control/btn_radiobutton_checked); } \
            QRadioButton::disabled{ color:#BBBBBB; }";

///CheckBox
    const QString CheckBoxStyle01 = " \
            QCheckBox{ background-color:transparent; } \
            QCheckBox::indicator::unchecked{ image:url(:/control/btn_checkBox_unchecked); } \
            QCheckBox::checked{ color:#E67300; } \
            QCheckBox::indicator:checked{ image:url(:/control/btn_checkBox_checked); } \
            QCheckBox::disabled{ color:#BBBBBB; }";

    const QString CheckBoxStyle02 = " \
            QCheckBox{ background-color:transparent; } \
            QCheckBox::indicator::unchecked{ image:url(:/control/btn_radioButton2_unchecked); } \
            QCheckBox::checked{ color:#E67300; } \
            QCheckBox::indicator:checked{ image:url(:/control/btn_radiobutton2_checked); } \
            QCheckBox::disabled{ color:#BBBBBB; }";

    const QString CheckBoxStyle03 = CheckBoxStyle01 + " \
            QCheckBox::checked{ color:rgb(0, 169, 236); }";

    const QString CheckBoxStyle04 = CheckBoxStyle01 + " \
            QCheckBox{ color:#888888; }";

    const QString CheckBoxStyle05 = " \
            QCheckBox{ background-color:transparent; color:rgb(222, 222, 222); } \
            QCheckBox::indicator::unchecked{ image:url(:/control/btn_checkBox2_unchecked); } \
            QCheckBox::checked{ color:rgb(255, 255, 255); } \
            QCheckBox::indicator:checked{ image:url(:/control/btn_checkBox2_checked); } \
            QCheckBox::disabled{ color:#BBBBBB; }";

///GroupBox
    const QString GroupBoxStyle01 = " \
            QGroupBox::indicator::unchecked{ image:url(:/control/btn_checkBox_unchecked); } \
            QGroupBox::indicator:checked{ image:url(:/control/btn_checkBox_checked); }";

///ScrollBar
    const QString ScrollBarStyle01 = " \
            QScrollBar{ background:#FFFFFF; width:8px; padding-top:0px; padding-bottom:0px; } \
            QScrollBar::handle:vertical{ border-radius:4px; background:#CFCFCF; min-height: 30px; } \
            QScrollBar::handle:vertical::disabled{ background:#DBDBDB; } \
            QScrollBar::handle:vertical:hover{ background:#BBBBBB; } \
            QScrollBar::add-line, QScrollBar::sub-line{ background:none; border:none; } \
            QScrollBar::add-page, QScrollBar::sub-page{ background:none; }";

    const QString ScrollBarStyle02 = " \
            QScrollBar{ background:#FFFFFF; height:8px; padding-left:0px; padding-right:0px; } \
            QScrollBar::handle:horizontal{ border-radius:4px; background:#CFCFCF; min-width: 30px; } \
            QScrollBar::handle:horizontal::disabled{ background:#DBDBDB; } \
            QScrollBar::handle:horizontal:hover{ background:#BBBBBB; } \
            QScrollBar::add-line, QScrollBar::sub-line{ background:none; border:none; } \
            QScrollBar::add-page, QScrollBar::sub-page{ background:none; }";

    const QString ScrollBarStyle03 = ScrollBarStyle01 + " \
            QScrollBar{ background:transparent; }";

    const QString ScrollBarStyle04 = ScrollBarStyle02 + " \
            QScrollBar{ background:transparent; }";

///Label
    const QString LabelStyle01 = " \
            QLabel{ color:#888888; background-color:#FFE6E6; border:1px solid gray; }";

///LineEdit
    const QString LineEditStyle01 = " \
            QLineEdit{ font-size:12px; color:#666666; font-weight:normal; border:1px solid gray; } \
            QLineEdit::hover{ border:1px solid rgb(22, 154, 243); } \
            QLineEdit::disabled{ color:#BBBBBB; border:1px solid #BBBBBB; }";

    const QString LineEditStyle02 = " \
            QLineEdit{ border-image:url(:/tiny/lb_transparent); font-size:13px; color:#333333; }";

    const QString LineEditStyle03 = " \
            QLineEdit{ color:#6495ED; border:1px solid #555555; }";

    const QString LineEditStyle04 = LineEditStyle01 + " \
            QLineEdit{ color:white; border:1px solid #545454; } \
            QLineEdit::disabled{ color:#323232; border:1px solid #323232; }";

///Menu
    const QString MenuStyle01 = " \
            QMenu{ padding:5px; } \
            QMenu::icon{ margin-left:10px; } \
            QMenu::right-arrow{ background: url(:/tiny/lb_arrow_up_normal); } \
            QMenu::item{ color:#666666; padding:6px 30px 6px 30px; border:1px solid transparent; } \
            QMenu::item:disabled{ color:#AAAAAA; } \
            QMenu::item:selected{ color:white; background: rgb(22, 154, 243); } \
            QMenu::separator{ height:1px; background:#DDDDDD; margin-top:5px; margin-bottom:5px; }" +
#if TTK_QT_VERSION_CHECK(5,12,0)
            QString("QMenu::item{ padding:6px 30px 6px 10px; } "
                    "QMenu::item::icon{ padding:6px 30px 6px 10px; }") +
#endif
            QString();

    const QString MenuStyle02 = MenuStyle01 + " \
            QMenu{ background:rgba(255, 255, 255, 235); }";

    const QString MenuStyle03 = MenuStyle01 + " \
            QMenu{ border:none; background:rgba(0, 0, 0, 210); border-radius:4px; } \
            QMenu::item{ color:#BBBBBB; } \
            QMenu::item:disabled{ color:#555555; } \
            QMenu::item:selected{ background:rgba(0, 0, 0, 200); } \
            QMenu::separator{ background:#BBBBBB; }";

    const QString MenuStyle04 = MenuStyle03 + " \
            QMenu{ background:rgba(0, 0, 0, 150); }";

    const QString MenuStyle05 = " \
            QMenu{ border:none; background:transparent; }";

///Slider
    const QString SliderStyle01 = " \
            QSlider::groove:horizontal{ \
            background:#FFFEA1; height:3px; border-radius:1px; } \
            QSlider::sub-page:horizontal{ background:#FFFEA1; } \
            QSlider::add-page:horizontal{ background:#4E4F4F; } \
            QSlider::handle:horizontal{ background:#FFFEA1; \
            width:9px; margin-top:-3px; margin-bottom:-3px; border-radius:4px; }";

    const QString SliderStyle02 = " \
            QSlider::groove:vertical{ \
            background: #FFFEA1; width:3px; border-radius:1px; } \
            QSlider::sub-page:vertical{ background:#4E4F4F; } \
            QSlider::add-page:vertical{ background:#FFFEA1; } \
            QSlider::handle:vertical{ background:#FFFEA1; \
            height:9px; margin-left:-3px; margin-right:-3px; border-radius:4px; }";

    const QString SliderStyle03 = " \
            QSlider::groove:vertical{ background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \
            stop:0 #B5B4B4, stop:1 #FCFCFC); width:3px; } \
            QSlider::handle:vertical{ border-image:url(:/control/lb_slider_handle_normal); \
            height:21px; margin-left:-8px; margin-right:-8px; } \
            QSlider::handle:vertical:disabled{ border-image:url(:/control/lb_slider_disable); } \
            QSlider::handle:vertical:hover{ border-image:url(:/control/lb_slider_handle_hover); border:none; }";

    const QString SliderStyle04 = SliderStyle03 + " \
            QSlider::groove:vertical{ background:white; } \
            QSlider::sub-page:vertical{ background:#AFC7F8; } \
            QSlider::add-page:vertical{ background:white; border:1px solid #ACF; }";

    const QString SliderStyle05 = " \
            QSlider::groove:horizontal{ background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \
            stop:0 #B5B4B4, stop:1 #FCFCFC); height:4px; } \
            QSlider::handle:horizontal{ border-image:url(:/control/lb_slider_handle_normal); \
            width:21px; margin-top:-8px; margin-bottom:-8px; } \
            QSlider::handle:horizontal:disabled{ border-image:url(:/control/lb_slider_disable); } \
            QSlider::handle:horizontal:hover{ border-image:url(:/control/lb_slider_handle_hover); border:none; }";

    const QString SliderStyle06 = SliderStyle05 + " \
            QSlider::groove:horizontal{ background:white; } \
            QSlider::sub-page:horizontal{ background:#AFC7F8; } \
            QSlider::add-page:horizontal{ background:white; border:1px solid #ACF; }";

    const QString SliderStyle07 = " \
            QSlider::add-page:Horizontal{ background-color:rgba(120, 120, 120, 100); height:4px; } \
            QSlider::sub-page:Horizontal{ background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, \
            y2:0, stop:0 rgba(231, 80, 229, 255), stop:1 rgba(7, 208, 255, 255)); height:4px; } \
            QSlider::groove:Horizontal{ background:transparent; height:4px; } \
            QSlider::handle:Horizontal{ border-image:url(':/image/lb_slider'); \
            width:8px; height:6px; margin:-2px 0px -2px 0px; }";

    const QString SliderStyle08 = " \
            QSlider::groove:horizontal{ background-image:url(:/control/lb_volume_back); } \
            QSlider::sub-page:horizontal{ border-image:url(:/control/lb_volume_fore); } \
            QSlider::add-page:horizontal{ background-image:url(:/control/lb_volume_back); } \
            QSlider::handle:horizontal{ margin:0px -2px 0px -2px; \
            background-image:url(:/control/lb_volume_handle_normal); width:13px; } \
            QSlider::handle:horizontal:hover{ background-image:url(:/control/lb_volume_handle_hover); }";

    const QString SliderStyle09 = " \
            QSlider::groove:horizontal{ background-image:url(:/control/lb_volume_back); } \
            QSlider::sub-page:horizontal{ border-image:url(:/control/lb_make_fore); } \
            QSlider::add-page:horizontal{ border-image:url(:/control/lb_make_back); } \
            QSlider::handle:horizontal{ margin:0px -1px 0px -1x; \
            border-image:url(:/control/lb_make_slider_handle_normal); width:18px; } \
            QSlider::handle:horizontal:hover{ border-image:url(:/control/lb_make_slider_handle_hover); } \
            QSlider::handle:horizontal:disabled{ border-image:url(:/control/lb_make_slider_disable); }";

    const QString SliderStyle10 = " \
            QSlider::groove:horizontal{ \
            background:transparent; height:3px; border-radius:1px; } \
            QSlider::sub-page:horizontal{ background:rgba(255, 255, 255, 190); } \
            QSlider::add-page:horizontal{ background:rgba(255, 255, 255, 50); } \
            QSlider::handle:horizontal{ background:rgba(255, 255, 255, 255); \
            width:9px; margin-top:-3px; margin-bottom:-3px; border-radius:4px; }";

///ComboBox
    const QString ComboBoxStyle01 = " \
            QComboBox{ border: 1px solid gray; color:#666666; } \
            QComboBox::hover{ border: 1px solid rgb(22, 154, 243); } \
            QComboBox::drop-down{ subcontrol-origin:padding; \
            subcontrol-position:top right; width:20px; border-left:none; } \
            QComboBox::down-arrow{ image:url(:/image/btn_down_arrow); } \
            QComboBox::disabled{ border: 1px solid #BBBBBB; }";

    const QString ComboBoxStyle02 = ComboBoxStyle01 + " \
            QComboBox{ border:none; } \
            QComboBox::hover{ border:none; }";

///TableWidget
    const QString TableWidgetStyle01 =
#if defined Q_OS_UNIX && !TTK_QT_VERSION_CHECK(5,7,0) //Fix linux selection-background-color stylesheet bug
            "QTableWidget::item:selected{ background:rgba(20, 20, 20, 20); }";
#else
            "QTableWidget{ selection-background-color:rgba(20, 20, 20, 20); }";
#endif

    const QString TableWidgetStyle02 =
#if defined Q_OS_UNIX && !TTK_QT_VERSION_CHECK(5,7,0) //Fix linux selection-background-color stylesheet bug
            "QTableWidget::item:selected{ background:rgb(220, 220, 220); }";
#else
            "QTableWidget{ selection-background-color:rgb(220, 220, 220); }";
#endif

    const QString TableWidgetStyle03 =
#if defined Q_OS_UNIX && !TTK_QT_VERSION_CHECK(5,7,0) //Fix linux selection-background-color stylesheet bug
            "QTableWidget::item:selected{ background:rgb(50, 50, 50); }";
#else
            "QTableWidget{ selection-background-color:rgb(50, 50, 50); }";
#endif

    const QString TableWidgetStyle04 = " \
            QTableWidget{ background:rgb(0, 0, 0); }";

///TabWidget
    const QString TabWidgetStyle01 = " \
            QTabWidget{ border:none; } \
            QTabWidget::pane{ border:none; } \
            QTabBar::tab{ height:30px; width:100px; background-color:#BFBFBF; color:white; margin-left:0; margin-right:0; } \
            QTabBar::tab:selected{ background-color:#158FE1; color:white}";

///TextEdit
    const QString TextEditStyle01 = " \
            QTextEdit{ border:1px solid gray; color:#666666; } \
            QTextEdit::hover{ border:1px solid rgb(22, 154, 243); } \
            QTextEdit::disabled{ color:#BBBBBB; border: 1px solid #BBBBBB; }";

///HeadView
    const QString HeaderView01 = " \
            QHeaderView{ background-color:white; color:black; }";

///Widget
    const QString WidgetStyle01 = " \
            QWidget{ background:rgba(255, 255, 255, 50); color:white; font-weight:bold; }";

///SpinBox
    const QString SpinBoxStyle01 = " \
            QSpinBox{ font-size:12px; color:#666666; font-weight:normal; border: 1px solid gray; } \
            QSpinBoxt::hover{ border:1px solid rgb(22, 154, 243); } \
            QSpinBox::up-button{ image:url(:/image/btn_up_arrow); } \
            QSpinBox::down-button{ image:url(:/image/btn_down_arrow); } \
            QSpinBox::disabled{ color:#BBBBBB; border: 1px solid #BBBBBB; }";

///ProgressBar
    const QString ProgressBar01 = " \
            QProgressBar{ border:none; background:rgb(210, 225, 240); text-align:center; } \
            QProgressBar::chunk{ background:rgb(60, 140, 220); }";

///ItemView
    const QString ItemView01 = " \
            QAbstractItemView::item{ height:20px; }";

}

#endif // MUSICUIOBJECT_H
