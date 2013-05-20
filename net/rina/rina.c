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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>

#include "rina.h"

static __initconst const char banner[] =
        KERN_INFO
	"rina: RINA stack v" RINA_VERSION_STRING "\n";

MODULE_DESCRIPTION("RINA stack");
MODULE_LICENSE("GPLv2");
MODULE_AUTHOR("Francesco Salvestrini <f.salvestrini>");

static __init int rina_init(void)
{
        printk(banner);

        return 0;
}

static __exit void rina_exit(void)
{
}

module_init(rina_init);
module_exit(rina_exit);
