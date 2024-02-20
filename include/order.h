//
// Created by carlos on 11-2-24.
//

#ifndef DYDX_CLIENT_ORDER_H
#define DYDX_CLIENT_ORDER_H

SubaccountId(owner=address, number=subaccount_number)

OrderId(
    subaccount_id=subaccount_id,
    client_id=client_id,
    order_flags=order_flags,
    clob_pair_id=int(clob_pair_id)
        )

class Order {
    order_id=order_id,
    side=side,
    quantums=quantums,
    subticks=subticks,
    good_til_block=good_til_block,
    time_in_force=time_in_force.value,
    reduce_only=reduce_only,
    client_metadata=client_metadata,
    condition_type=condition_type,
    conditional_order_trigger_subticks=conditional_order_trigger_subticks,
};

#endif // DYDX_CLIENT_ORDER_H
