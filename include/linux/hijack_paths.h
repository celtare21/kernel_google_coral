// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Vlad Adumitroaie <celtare21@gmail.com>.
 */

#define ORIG_LEN(file) (int) strlen(file)

//Hosts
static const char *hosts_file_1 = "/data/local/tmp/kernel/k_hosts";
static const char *hosts_orig_file_1 = "/system/etc/hosts";

//Safetynet
static const char *sf_file_1 = "/data/local/tmp/kernel/k_keystore2";
static const char *sf_file_2 = "/data/local/tmp/kernel/k_libkeystore-attestation-application-id.so";
static const char *sf_orig_file_1 = "/system/bin/keystore2";
static const char *sf_orig_file_2 = "/system/lib64/libkeystore-attestation-application-id.so";
