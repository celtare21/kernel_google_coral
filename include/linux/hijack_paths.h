// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Vlad Adumitroaie <celtare21@gmail.com>.
 */

#define ORIG_LEN(file) (int) strlen(file)

//Hosts
static const char *hosts_files[] = { "/data/local/tmp/kernel/k_hosts" };
static const char *hosts_orig_files[] = { "/system/etc/hosts " };

//SafetyNet
static const char *sf_files[] = { "/data/local/tmp/kernel/k_keystore2", "/data/local/tmp/kernel/k_libkeystore-attestation-application-id.so" };
static const char *sf_orig_files[] = { "/system/bin/keystore2", "/system/lib64/libkeystore-attestation-application-id.so" };
