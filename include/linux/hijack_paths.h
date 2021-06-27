// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Vlad Adumitroaie <celtare21@gmail.com>.
 */

//Hosts
static const char *hosts_name = "/data/local/tmp/hosts_k";
static const char *hosts_orig_name = "/system/etc/hosts";
#define HOSTS_ORIG_LEN (int) strlen(hosts_orig_name)

//Volte
static const char *volte_orig_file_1 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/cmcc_sub/sr_dsds/mcfg_hw.mbn";
static const char *volte_orig_file_2 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/cmcc_sub/la/7+7_mode/sr_dsds/mcfg_hw.mbn";
static const char *volte_orig_file_3 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/cmcc_sub/la/ss/mcfg_hw.mbn";
static const char *volte_orig_file_4 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/cmcc_sub/la/ss_apq_o/mcfg_hw.mbn";
static const char *volte_orig_file_5 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/wd/7+7_mode/sr_dsds/mcfg_hw.mbn";
static const char *volte_orig_file_6 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/wd/ss/mcfg_hw.mbn";
static const char *volte_orig_file_7 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/wd8/7+7_mode/sr_dsds/mcfg_hw.mbn";
static const char *volte_orig_file_8 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/generic/common/sm8150/wd8/ss/mcfg_hw.mbn";
static const char *volte_orig_file_9 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/mbn_hw.dig";
static const char *volte_orig_file_10 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/mbn_hw.txt";
static const char *volte_orig_file_11 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/oem_hw.txt";
static const char *volte_orig_file_12 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/oem_hw_a.txt";
static const char *volte_orig_file_13 = "/system/vendor/rfs/msm/mpss/readonly/vendor/mbn/mcfg_hw/oem_hw_w.txt";

//SafetyNet
static const char *sn_file_1 = "/data/local/tmp/sn/bin/bad";
static const char *sn_file_2 = "/data/local/tmp/sn/lib64/bad";
static const char *sn_orig_file_1 = "/system/bin/bad";
static const char *sn_orig_file_2 = "/system/lib64/bad";

#define ORIG_LEN(file) (int) strlen(file)


