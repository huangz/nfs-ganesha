/*
 * vim:expandtab:shiftwidth=8:tabstop=8:
 *
 * Copyright CEA/DAM/DIF  (2008)
 * contributeur : Philippe DENIEL   philippe.deniel@cea.fr
 *                Thomas LEIBOVICI  thomas.leibovici@cea.fr
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * ---------------------------------------
 */

/**
 * \file    nfs4_op_secinfo.c
 * \author  $Author: deniel $
 * \date    $Date: 2005/11/28 17:02:52 $
 * \version $Revision: 1.8 $
 * \brief   Routines used for managing the NFS4 COMPOUND functions.
 *
 * nfs4_op_secinfo.c : Routines used for managing the NFS4 COMPOUND functions.
 *
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef _SOLARIS
#include "solaris_port.h"
#endif

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/file.h>           /* for having FNDELAY */
#include "HashData.h"
#include "HashTable.h"
#include "rpc.h"
#include "log_macros.h"
#include "stuff_alloc.h"
#include "nfs23.h"
#include "nfs4.h"
#include "mount.h"
#include "nfs_core.h"
#include "cache_inode.h"
#include "cache_content.h"
#include "nfs_exports.h"
#include "nfs_creds.h"
#include "nfs_proto_functions.h"
#include "nfs_tools.h"

/**
 * nfs4_op_secinfo: The NFS4_OP_SECINFO
 * 
 * Implements the NFS4_OP_SECINFO
 *
 * @param op    [IN]    pointer to nfs4_op arguments
 * @param data  [INOUT] Pointer to the compound request's data
 * @param resp  [IN]    Pointer to nfs4_op results
 * 
 * @return NFS4_OK if ok, any other value show an error.
 *
 */
#define arg_SECINFO4 op->nfs_argop4_u.opsecinfo
#define res_SECINFO4 resp->nfs_resop4_u.opsecinfo

int nfs4_op_secinfo(struct nfs_argop4 *op,
                    compound_data_t * data, struct nfs_resop4 *resp)
{
  char __attribute__ ((__unused__)) funcname[] = "nfs4_op_secinfo";

  resp->resop = NFS4_OP_SECINFO;
  res_SECINFO4.status = NFS4_OK;

  if((res_SECINFO4.SECINFO4res_u.resok4.SECINFO4resok_val =
      (secinfo4 *) Mem_Alloc(2 * sizeof(secinfo4))) == NULL)
    {
      res_SECINFO4.status = NFS4ERR_SERVERFAULT;
      return res_SECINFO4.status;
    }

  /* For the moment, we just have AUTH_NONE and AUTH_UNIX, and this needs no secinfo */
  res_SECINFO4.SECINFO4res_u.resok4.SECINFO4resok_val[0].flavor = AUTH_UNIX;
  res_SECINFO4.SECINFO4res_u.resok4.SECINFO4resok_val[1].flavor = AUTH_NONE;
  res_SECINFO4.SECINFO4res_u.resok4.SECINFO4resok_len = 2;

  return res_SECINFO4.status;
}                               /* nfs4_op_secinfo */

/**
 * nfs4_op_secinfo_Free: frees what was allocared to handle nfs4_op_secinfo.
 * 
 * Frees what was allocared to handle nfs4_op_secinfo.
 *
 * @param resp  [INOUT]    Pointer to nfs4_op results
 *
 * @return nothing (void function )
 * 
 */
void nfs4_op_secinfo_Free(SECINFO4res * resp)
{
  /* Nothing to be done */
  return;
}                               /* nfs4_op_secinfo_Free */
