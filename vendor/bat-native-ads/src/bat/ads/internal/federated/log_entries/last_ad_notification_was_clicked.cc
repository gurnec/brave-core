/* Copyright 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/federated/log_entries/last_ad_notification_was_clicked.h"

#include "base/time/time.h"
#include "bat/ads/ad_history_info.h"
#include "bat/ads/ads_history_info.h"
#include "bat/ads/internal/ads_history/ads_history.h"
#include "bat/ads/internal/federated/covariate_logs_util.h"

#include <iostream>

namespace ads {

namespace {
constexpr int kMissingValue = -1;
}  // namespace

LastAdNotificationWasClicked::
    LastAdNotificationWasClicked() = default;

LastAdNotificationWasClicked::
    ~LastAdNotificationWasClicked() = default;

mojom::DataType LastAdNotificationWasClicked::GetDataType() const {
  return mojom::DataType::kBool;
}

mojom::CovariateType LastAdNotificationWasClicked::GetCovariateType() const {
  return mojom::CovariateType::kLastAdNotificationWasClicked;
}

std::string LastAdNotificationWasClicked::GetValue() const {
  const AdsHistoryFilterType filter_type = AdsHistoryFilterType::kNone;
  const AdsHistorySortType sort_type = AdsHistorySortType::kDescendingOrder;
  const base::Time from = base::Time::Now() - base::Days(30);
  const base::Time to = base::Time::Now();

  const AdsHistoryInfo history =
      history::Get(filter_type, sort_type, from, to);

  std::cout << "*** FOOBAR A " << history.items.size() << std::endl;

  if (history.items.empty()) {
    return ToString(kMissingValue);
  }

  return ToString(0);
  // return ToString(GetNumberOfEvents(events, ads::UserActivityEventType::kBrowserDidBecomeActive));
}

}  // namespace ads
