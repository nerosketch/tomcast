/*
 * File:   igmp.h
 * Author: bashmak
 *
 * Created on 11 сентября 2017 г., 18:08
 */

#ifndef IGMP_H
#define IGMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/igmp.h>
#include <netinet/ip.h>
#include <net/if.h>

    int connect_igmp_src(void);
    int igmp_rcv(int sock, int (rec_callback_func)(struct ip *, struct igmp *));

#ifdef __cplusplus
}
#endif

#endif /* IGMP_H */
