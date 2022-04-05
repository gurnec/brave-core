/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_ads/notification_helper/notification_helper.h"

#include "base/no_destructor.h"
#include "build/build_config.h"

#if BUILDFLAG(IS_ANDROID)
#include "brave/browser/brave_ads/notification_helper/notification_helper_android.h"
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_LINUX)
#include "brave/browser/brave_ads/notification_helper/notification_helper_linux.h"
#endif  // BUILDFLAG(IS_LINUX)

#if BUILDFLAG(IS_MAC)
#include "brave/browser/brave_ads/notification_helper/notification_helper_mac.h"
#endif  // BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_WIN)
#include "brave/browser/brave_ads/notification_helper/notification_helper_win.h"
#endif  // BUILDFLAG(IS_WIN)

namespace brave_ads {

NotificationHelper::NotificationHelper() = default;

NotificationHelper::~NotificationHelper() = default;

bool NotificationHelper::CanShowNativeNotifications() {
  return true;
}

bool NotificationHelper::CanShowBackgroundNotifications() const {
  return true;
}

bool NotificationHelper::ShowMyFirstAdNotification() {
  return false;
}

NotificationHelper* NotificationHelper::GetInstance() {
#if BUILDFLAG(IS_ANDROID)
  static base::NoDestructor<NotificationHelperAndroid> notification_helper;
#elif BUILDFLAG(IS_LINUX)
  static base::NoDestructor<NotificationHelperLinux> notification_helper;
#elif BUILDFLAG(IS_MAC)
  static base::NoDestructor<NotificationHelperMac> notification_helper;
#elif BUILDFLAG(IS_WIN)
  static base::NoDestructor<NotificationHelperWin> notification_helper;
#else
  // Return a default notification helper for unsupported platforms
  static base::NoDestructor<NotificationHelper> notification_helper;
#endif  // BUILDFLAG(IS_ANDROID)

  return notification_helper.get();
}

}  // namespace brave_ads
