#ifndef MUSICHOTKEYMANAGER_H
#define MUSICHOTKEYMANAGER_H

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

#include "ttksingleton.h"

class QGlobalShortcut;

/*! @brief The class of the global hotkey setting manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicHotKeyManager : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicHotKeyManager)
public:
    /*!
     * Set input connection.
     */
    void setInputModule(QObject *object);
    /*!
     * Set hotKey by given string list keys.
     */
    void setHotKeys(const QStringList &keys);
    /*!
     * Set hotKey by given index and string key.
     */
    void setHotKey(int index, const QString &key);
    /*!
     * Set hotKey by given index and virtual key.
     */
    void setHotKey(int index, int key);

    /*!
     * Get the object key by given hotKey index.
     */
    QObject* hotKey(int index);
    /*!
     * Add hotKey by given index and string key.
     */
    void addHotKey(const QString &key);
    /*!
     * Set hotKey by given index and virtual key.
     */
    void addHotKey(int key);

    /*!
     * Enable or disable the hotkey by index.
     */
    void setEnabled(int index, bool enable);
    /*!
     * check the given hotkey is enabled or not.
     */
    bool enabled(int index);
    /*!
     * Enable or disable all hotkeys.
     */
    void enabledAll(bool enable);

    /*!
     * Mapping the virtual key to string key.
     */
    QString toString(int key, int modifiers);
    /*!
     * Get hotkey count.
     */
    int count() const;

    /*!
     * Get default key string.
     */
    QStringList defaultKeys() const;
    /*!
     * Get key string.
     */
    QStringList keys() const;

private:
    /*!
     * Set default key.
     */
    void setDefaultKey();

    QList<QGlobalShortcut*> m_hotkeys;

    TTK_DECLARE_SINGLETON_CLASS(MusicHotKeyManager)

};

#define G_HOTKEY_PTR makeMusicHotKeyManager()
TTK_MODULE_EXPORT MusicHotKeyManager* makeMusicHotKeyManager();

#endif // MUSICHOTKEYMANAGER_H
