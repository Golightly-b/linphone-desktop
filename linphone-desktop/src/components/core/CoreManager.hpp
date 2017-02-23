/*
 * CoreManager.hpp
 * Copyright (C) 2017  Belledonne Communications, Grenoble, France
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Created on: February 2, 2017
 *      Author: Ronan Abhamon
 */

#ifndef CORE_MANAGER_H_
#define CORE_MANAGER_H_

#include "../calls/CallsListModel.hpp"
#include "../contacts/ContactsListModel.hpp"
#include "../settings/SettingsModel.hpp"
#include "../sip-addresses/SipAddressesModel.hpp"
#include "CoreHandlers.hpp"

// =============================================================================

class QTimer;

class CoreManager : public QObject {
  Q_OBJECT;

public:
  ~CoreManager () = default;

  void enableHandlers ();

  std::shared_ptr<linphone::Core> getCore () {
    return m_core;
  }

  std::shared_ptr<CoreHandlers> getHandlers () {
    return m_handlers;
  }

  // ---------------------------------------------------------------------------
  // Singleton models.
  // ---------------------------------------------------------------------------

  CallsListModel *getCallsListModel () const {
    return m_calls_list_model;
  }

  ContactsListModel *getContactsListModel () const {
    return m_contacts_list_model;
  }

  SipAddressesModel *getSipAddressesModel () const {
    return m_sip_addresses_model;
  }

  SettingsModel *getSettingsModel () const {
    return m_settings_model;
  }

  // ---------------------------------------------------------------------------
  // Initialization.
  // ---------------------------------------------------------------------------

  static void init (const QString &configPath);

  static CoreManager *getInstance () {
    return m_instance;
  }

  // ---------------------------------------------------------------------------

  // Must be used in a qml scene.
  // Warning: The ownership of `VcardModel` is `QQmlEngine::JavaScriptOwnership` by default.
  Q_INVOKABLE VcardModel *createDetachedVcardModel ();

private:
  CoreManager (const QString &configPath, QObject *parent = Q_NULLPTR);

  void setDatabasesPaths ();
  void setResourcesPaths ();

  std::shared_ptr<linphone::Core> m_core;
  std::shared_ptr<CoreHandlers> m_handlers;

  CallsListModel *m_calls_list_model;
  ContactsListModel *m_contacts_list_model;
  SipAddressesModel *m_sip_addresses_model;
  SettingsModel *m_settings_model;

  QTimer *m_cbs_timer;

  static CoreManager *m_instance;
};

#endif // CORE_MANAGER_H_
