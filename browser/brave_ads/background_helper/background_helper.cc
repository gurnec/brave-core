/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_ads/background_helper/background_helper.h"

#include "base/no_destructor.h"
#include "build/build_config.h"

#if BUILDFLAG(IS_ANDROID)
#include "brave/browser/brave_ads/background_helper/background_helper_android.h"
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(IS_LINUX)
#include "brave/browser/brave_ads/background_helper/background_helper_linux.h"
#endif  // BUILDFLAG(IS_LINUX)

#if BUILDFLAG(IS_MAC)
#include "brave/browser/brave_ads/background_helper/background_helper_mac.h"
#endif  // BUILDFLAG(IS_MAC)

#if BUILDFLAG(IS_WIN)
#include "brave/browser/brave_ads/background_helper/background_helper_win.h"
#endif  // BUILDFLAG(IS_WIN)

namespace brave_ads {

BackgroundHelper::BackgroundHelper() = default;

BackgroundHelper::~BackgroundHelper() = default;

bool BackgroundHelper::IsForeground() const {
  return true;
}

void BackgroundHelper::AddObserver(Observer* observer) {
  observers_.AddObserver(observer);
}

void BackgroundHelper::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

void BackgroundHelper::TriggerOnBackground() {
  for (auto& observer : observers_) {
    observer.OnBackground();
  }
}

void BackgroundHelper::TriggerOnForeground() {
  for (auto& observer : observers_) {
    observer.OnForeground();
  }
}

BackgroundHelper* BackgroundHelper::GetInstance() {
#if BUILDFLAG(IS_ANDROID)
  static base::NoDestructor<BackgroundHelperAndroid> background_helper;
#elif BUILDFLAG(IS_LINUX)
  static base::NoDestructor<BackgroundHelperLinux> background_helper;
#elif BUILDFLAG(IS_MAC)
  static base::NoDestructor<BackgroundHelperMac> background_helper;
#elif BUILDFLAG(IS_WIN)
  static base::NoDestructor<BackgroundHelperWin> background_helper;
#else
  // Return a default background helper for unsupported platforms
  static base::NoDestructor<BackgroundHelper> background_helper;
#endif  // BUILDFLAG(IS_ANDROID)

  return background_helper.get();
}

}  // namespace brave_ads
