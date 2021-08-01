// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Vlad Adumitroaie <celtare21@gmail.com>.
 */

#define pr_fmt(fmt) "userland_listener: " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/userland.h>

#define MAX_DEV 1
#define TMPBUFSIZE 50
#define NAME "userland_listener"

static bool gamma_hack;
static DEFINE_SPINLOCK(gamma_lock);

static int userland_open(struct inode *inode, struct file *file);
static int userland_release(struct inode *inode, struct file *file);
static ssize_t userland_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t userland_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);

static const struct file_operations userland_fops = {
	.owner      =	THIS_MODULE,
	.open       =	userland_open,
	.release    =	userland_release,
	.read       =	userland_read,
	.write      =	userland_write
};

struct userland_device_data {
	struct cdev cdev;
};

static int dev_major = 0;
static struct class *userland_class = NULL;
static struct userland_device_data userland_data[MAX_DEV];

static int userland_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	add_uevent_var(env, "DEVMODE=%#o", 0666);

	return 0;
}

static int __init userland_init(void)
{
	dev_t dev;

	if (alloc_chrdev_region(&dev, 0, MAX_DEV, NAME))
		return 0;

	dev_major = MAJOR(dev);

	userland_class = class_create(THIS_MODULE, NAME);
	userland_class->dev_uevent = userland_uevent;

	cdev_init(&userland_data[0].cdev, &userland_fops);
	userland_data[0].cdev.owner = THIS_MODULE;

	cdev_add(&userland_data[0].cdev, MKDEV(dev_major, 0), 1);

	device_create(userland_class, NULL, MKDEV(dev_major, 0), NULL, "userland_listener-%d", 0);

	return 0;
}

static ssize_t userland_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	return count;
}

static int userland_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int userland_release(struct inode *inode, struct file *file)
{
	return 0;
}

void set_gamma_hack(bool value)
{
	spin_lock(&gamma_lock);
	gamma_hack = value;
	spin_unlock(&gamma_lock);
}

bool get_gamma_hack(void)
{
	bool value;

	spin_lock(&gamma_lock);
	value = gamma_hack;
	spin_unlock(&gamma_lock);

	return value;
}

static int ulong_from_user(unsigned long *val, char const __user *buf, size_t count)
{
	char tmpbuf[TMPBUFSIZE];

	if (!count)
		return 0;

	if (count > TMPBUFSIZE - 1)
		return -EINVAL;

	memset(tmpbuf, 0x0, TMPBUFSIZE);

	if (copy_from_user(tmpbuf, buf, count))
		return -EFAULT;

	*val = simple_strtoul(tmpbuf, NULL, 0);

	return count;
}

static ssize_t userland_write(struct file *file, char const __user *buf, size_t count, loff_t *offset)
{
	unsigned long val;
	int retval;

	if (*offset)
		return -EINVAL;

	retval = ulong_from_user(&val, buf, count);
	if (retval <= 0)
		return count;

	switch (val)
	{
		case 1:
			pr_info("Disabling root.");
			restore_syscalls(true);
			break;
		case 2:
			pr_info("Enabling gamma hack.");
			set_gamma_hack(true);
			force_gamma_update();
			break;
		case 3:
			pr_info("Disabling gamma hack.");
			set_gamma_hack(false);
			force_gamma_update();
			break;
	}

	return count;
}

module_init(userland_init);
