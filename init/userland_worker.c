// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Vlad Adumitroaie <celtare21@gmail.com>.
 */

#define pr_fmt(fmt) "userland_worker: " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/string.h>

#define INITIAL_SIZE 4
#define DELAY 10000

static struct delayed_work userland_work;

static int use_userspace(char** argv)
{
	static char* envp[] = {
		"SHELL=/bin/sh",
                "HOME=/",
		"USER=shell",
		"TERM=xterm-256color",
		"PATH=/product/bin:/apex/com.android.runtime/bin:/apex/com.android.art/bin:/system_ext/bin:/system/bin:/system/xbin:/odm/bin:/vendor/bin:/vendor/xbin",
                "DISPLAY=:0",
		NULL
	};

	pr_info("Calling userspace!");

	return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
}


static void free_memory(char** argv, int size)
{
	int i;

	for (i = 0; i < size; i++)
		kfree(argv[i]);
	kfree(argv);
}

static char** alloc_memory(int size)
{
	char** argv;
	int i;

	argv = kmalloc(size * sizeof(char*), GFP_KERNEL);
	if (!argv) {
		pr_err("Couldn't allocate memory!");
		return NULL;
	}

	for (i = 0; i < size; i++) {
		argv[i] = kmalloc(size * sizeof(char), GFP_KERNEL);
		if (!argv[i]) {
			pr_err("Couldn't allocate memory!");
			free_memory(argv, i);
			return NULL;
		}
	}

	return argv;
}

static void userland_worker(struct work_struct *work)
{
	char** argv;
	int ret;

	argv = alloc_memory(INITIAL_SIZE);
	if (!argv)
		return;

	strcpy(argv[0], "/system/bin/setprop");
	strcpy(argv[1], "persist.device_config.runtime_native.usap_pool_enabled");
	strcpy(argv[2], "true");
	argv[3] = NULL;

	ret = use_userspace(argv);
	if (!ret)
		pr_info("Props set succesfully!");
	else
		pr_err("Couldn't set props! %d", ret);

	free_memory(argv, INITIAL_SIZE);
}

static int __init userland_worker_entry(void)
{
	INIT_DELAYED_WORK(&userland_work, userland_worker);
	queue_delayed_work(system_power_efficient_wq,
			&userland_work, DELAY);

	return 0;
}

static void userland_worket_exit(void)
{
	return;
}

module_init(userland_worker_entry);
module_exit(userland_worket_exit);
