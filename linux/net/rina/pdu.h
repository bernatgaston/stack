/*
 * Protocol Data Unit
 *
 *    Francesco Salvestrini <f.salvestrini@nextworks.it>
 *    Miquel Tarzan         <miquel.tarzan@i2cat.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef RINA_PDU_H
#define RINA_PDU_H

#include <linux/types.h>

#include "common.h"
#include "qos.h"
#include "buffer.h"
#include "sdu.h"

#define PDU_FLAGS_FRAG_MIDDLE         0x00
#define PDU_FLAGS_FRAG_FIRST          0x01
#define PDU_FLAGS_FRAG_LAST           0x02
#define PDU_FLAGS_CARRY_COMPLETE_SDU  0x03
#define PDU_FLAGS_CARRY_MULTIPLE_SDUS 0x07
#define PDU_FLAGS_DATA_RUN            0x80

typedef uint8_t pdu_flags_t;

#define PDU_TYPE_EFCP       0x8000 /* EFCP PDUs */
#define PDU_TYPE_DT         0x8001 /* Data Transfer PDU */
#define PDU_TYPE_CC         0x8002 /* Common Control PDU */
#define PDU_TYPE_SACK       0x8004 /* Selective ACK */
#define PDU_TYPE_NACK       0x8006 /* Forced Retransmission PDU (NACK) */
#define PDU_TYPE_FC         0x8009 /* Flow Control only */
#define PDU_TYPE_ACK        0x800C /* ACK only */
#define PDU_TYPE_ACK_AND_FC 0x800D /* ACK and Flow Control */
#define PDU_TYPE_MGMT       0xC000 /* Management */

typedef uint16_t pdu_type_t;

#define pdu_type_is_ok(X)                               \
        ((X && PDU_TYPE_EFCP)       ? true :            \
         ((X && PDU_TYPE_DT)         ? true :           \
          ((X && PDU_TYPE_CC)         ? true :          \
           ((X && PDU_TYPE_SACK)       ? true :         \
            ((X && PDU_TYPE_NACK)       ? true :        \
             ((X && PDU_TYPE_FC)         ? true :       \
              ((X && PDU_TYPE_ACK)        ? true :      \
               ((X && PDU_TYPE_ACK_AND_FC) ? true :     \
                ((X && PDU_TYPE_MGMT)       ? true :    \
                 false)))))))))

typedef uint seq_num_t;

struct pci *          pci_create(cep_id_t   dst_cep_id,
                                 cep_id_t   src_cep_id,
                                 address_t  dst_address,
                                 address_t  src_address,
                                 seq_num_t  nxt_seq_send,
                                 qos_id_t   qos_id,
                                 pdu_type_t type);
/* NOTE: The following function may return -1 */
struct pci *          pci_create_from(const void * data);
struct pci *          pci_create_from_ni(const void * data);
struct pci *          pci_dup(const struct pci * pci);
struct pci *          pci_dup_ni(const struct pci * pci);
int                   pci_destroy(struct pci * pci);
ssize_t               pci_length(const struct pci * pci);
pdu_type_t            pci_type(const struct pci * pci);
address_t             pci_source(const struct pci * pci);
address_t             pci_destination(const struct pci * pci);
cep_id_t              pci_cep_source(const struct pci * pci);
cep_id_t              pci_cep_destination(const struct pci * pci);

struct pdu;

struct pdu *          pdu_create_from(struct sdu * sdu, struct pci * pci);
struct pdu *          pdu_create_with(struct sdu * sdu);
struct pdu *          pdu_create_with_ni(struct sdu * sdu);
bool                  pdu_is_ok(const struct pdu * pdu);
const struct buffer * pdu_buffer_ro(const struct pdu * pdu);
struct buffer *       pdu_buffer_rw(struct pdu * pdu);
const struct pci *    pdu_pci(const struct pdu * pdu);
struct pci *          pdu_pci_rw(struct pdu * pdu);
int                   pdu_destroy(struct pdu * pdu);

#endif