/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_BRAVE_ADS_SEARCH_AD_METADATA_HANDLER_H_
#define BRAVE_BROWSER_BRAVE_ADS_SEARCH_AD_METADATA_HANDLER_H_

#include <vector>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "brave/vendor/bat-native-ads/include/bat/ads/public/interfaces/ads.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "third_party/blink/public/mojom/document_metadata/document_metadata.mojom.h"

namespace content {
class RenderFrameHost;
}

namespace brave_ads {

using SearchResultAdsList = std::vector<ads::mojom::SearchResultAdPtr>;

using RetrieveSearchAdMetadataCallback =
    base::OnceCallback<void(SearchResultAdsList)>;

class SearchAdMetadataHandler final {
 public:
  SearchAdMetadataHandler();
  virtual ~SearchAdMetadataHandler();

  SearchAdMetadataHandler(const SearchAdMetadataHandler&) = delete;
  SearchAdMetadataHandler& operator=(const SearchAdMetadataHandler&) = delete;

  bool IsAllowedBraveSearchHost(const GURL& url) const;

  void RetrieveSearchAdMetadata(content::RenderFrameHost* render_frame_host,
                                RetrieveSearchAdMetadataCallback callback);

 private:
  void OnRetrieveSearchAdMetadataEntities(
      RetrieveSearchAdMetadataCallback callback,
      blink::mojom::WebPagePtr web_page);

  mojo::Remote<blink::mojom::DocumentMetadata> document_metadata_;

  base::WeakPtrFactory<SearchAdMetadataHandler> weak_factory_{this};
};

}  // namespace brave_ads

#endif  // BRAVE_BROWSER_BRAVE_ADS_SEARCH_AD_METADATA_HANDLER_H_
