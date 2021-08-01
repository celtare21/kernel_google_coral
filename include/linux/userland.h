// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Vlad Adumitroaie <celtare21@gmail.com>.
 */

extern bool is_decrypted;
extern int get_enforce_value(void);
extern void set_selinux(int value);
extern void hijack_syscalls(void);
extern void restore_syscalls(bool set_enforce);
extern void set_gamma_hack(bool value);
extern bool get_gamma_hack(void);
extern void force_gamma_update(void);
