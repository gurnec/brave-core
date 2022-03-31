import * as React from 'react'
import { useSelector } from 'react-redux'

import SelectNetworkItem from '../select-network-item'
import { BraveWallet, WalletState } from '../../../constants/types'

function SelectNetwork () {
  // redux
  const {
    accounts,
    networkList: networks,
    selectedNetwork
  } = useSelector((state: { wallet: WalletState }) => state.wallet)

  const hasSolAccount = React.useMemo(() => { return accounts.some(account => account.coin === BraveWallet.CoinType.SOL) }, [accounts])
  const hasFilAccount = React.useMemo(() => { return accounts.some(account => account.coin === BraveWallet.CoinType.FIL) }, [accounts])

  const networkList = React.useMemo(() => {
    if (!hasSolAccount && !hasFilAccount) {
      return networks.filter((network) =>
        network.coin !== BraveWallet.CoinType.FIL &&
        network.coin !== BraveWallet.CoinType.SOL)
    }
    if (hasSolAccount && !hasFilAccount) {
      return networks.filter((network) => network.coin !== BraveWallet.CoinType.FIL)
    }
    if (!hasSolAccount && hasFilAccount) {
      return networks.filter((network) => network.coin !== BraveWallet.CoinType.SOL)
    }
    return networks
  }, [networks, hasSolAccount, hasFilAccount])

  return (
    <>
      {networkList.map((network) =>
        <SelectNetworkItem
          selectedNetwork={selectedNetwork}
          key={`${network.chainId}-${network.coin}`}
          network={network}
        />
      )}
    </>
  )
}

export default SelectNetwork
