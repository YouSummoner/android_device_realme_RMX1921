/*
 * Copyright (C) 2021 LineageOS Project
 *
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fstream>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <string.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include <android-base/properties.h>
#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;

std::vector<string> ro_props_default_source_order = {
    "",
    "bootimage.",
    "odm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor."
};

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info *pi;

    pi = (prop_info *)__system_property_find(prop);

    if (pi)
	__system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_dalvikvm_properties() {
  struct sysinfo sys;
  sysinfo(&sys);
  if (sys.totalram > 6144ull * 1024 * 1024) {
    // from - phone-xhdpi-8192-dalvik-heap.mk
    property_override("dalvik.vm.heapstartsize", "16m");
    property_override("dalvik.vm.heapgrowthlimit", "384m");
    property_override("dalvik.vm.heapmaxfree", "8m");
    }
  else if (sys.totalram > 4096ull * 1024 * 1024) {
    // from - phone-xhdpi-6144-dalvik-heap.mk
    property_override("dalvik.vm.heapstartsize", "16m");
    property_override("dalvik.vm.heapgrowthlimit", "384m");
    property_override("dalvik.vm.heapmaxfree", "8m");
    }
  else {
    // from - phone-xhdpi-4096-dalvik-heap.mk
    property_override("dalvik.vm.heapstartsize", "8m");
    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heapmaxfree", "16m");
    property_override("ro.lmk.psi_complete_stall_ms", "600");
    property_override("ro.lmk.psi_partial_stall_ms", "130");
    property_override("ro.lmk.swap_free_low_percentage", "20");
    property_override("ro.lmk.thrashing_limit", "55");
    property_override("ro.lmk.thrashing_limit_decay", "37");
  }
  property_override("dalvik.vm.heaptargetutilization", "0.75");
  property_override("dalvik.vm.heapsize", "512m");
  property_override("dalvik.vm.heapminfree", "8m");
}

void nfc_device_check() {
    /*
     * Detect device region and set properties
     */
    std::ifstream infile("/proc/oppoVersion/operatorName");
    string operatorName;

    getline(infile, operatorName);

    if (operatorName == "11" || operatorName == "34") {
        property_override("ro.boot.product.hardware.sku", "RMX1921EU");
	property_override("ro.hardware.nfc_nci", "nqx.default");
	property_override("ro.nfc.port", "I2C");
    } else {
        property_override("ro.boot.product.hardware.sku", "RMX1921");
    }
}

void vendor_load_properties() {

  // dalvikvm props
  load_dalvikvm_properties();
  // SafetyNet workaround
  property_override("ro.boot.verifiedbootstate", "green");
  // NFC Device Check
  nfc_device_check();
}
