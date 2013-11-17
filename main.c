/*
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/kallsyms.h>

#include "hook.h"
#include "my_bq24192_charger.h"

// Lookups
unsigned long ksym_bq24192_write_reg;
unsigned long ksym_mem_text_address_restore;
unsigned long ksym_mem_text_address_writeable;
unsigned long ksym_mem_text_writeable_spinlock;
unsigned long ksym_mem_text_writeable_spinunlock;

// Local
static uintptr_t backup_bq24192_write_reg[2];

static int __init n5charge_init(void)
{
	ksym_bq24192_write_reg = kallsyms_lookup_name(
			"bq24192_write_reg");
	if (!ksym_bq24192_write_reg) return -EFAULT;

	ksym_mem_text_address_restore = kallsyms_lookup_name(
			"mem_text_address_restore");
	ksym_mem_text_address_writeable = kallsyms_lookup_name(
			"mem_text_address_writeable");
	ksym_mem_text_writeable_spinlock = kallsyms_lookup_name(
			"mem_text_writeable_spinlock");
	ksym_mem_text_writeable_spinunlock = kallsyms_lookup_name(
			"mem_text_writeable_spinunlock");

	if (hook_and_backup((void*) ksym_bq24192_write_reg,
			backup_bq24192_write_reg,
			my_bq24192_write_reg)) return -EFAULT;

	return 0;
}

static void __exit n5charge_exit(void)
{
	unhook_and_restore((void*) ksym_bq24192_write_reg,
			backup_bq24192_write_reg);
}

module_init(n5charge_init);
module_exit(n5charge_exit);

MODULE_DESCRIPTION("Nexus 5 Fast Charge");
MODULE_AUTHOR("Michael Zhou <mzhou@cse.unsw.edu.au>");
MODULE_LICENSE("GPL");
