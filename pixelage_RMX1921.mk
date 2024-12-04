#
# Copyright (C) 2021-2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit some common Pixelage stuff
TARGET_BOOT_ANIMATION_RES := 1080
TARGET_SUPPORTS_QUICK_TAP := true
WITH_GAPPS := true
TARGET_GAPPS_ARCH := arm64
TARGET_DEFAULT_PIXEL_LAUNCHER := true
TARGET_HAS_UDFPS := true
TARGET_FACE_UNLOCK_SUPPORTED := true
TARGET_EXCLUDES_AUDIOFX := true
$(call inherit-product, vendor/pixelage/config/common_full_phone.mk)

# Inherit from RMX1921 device
$(call inherit-product, $(LOCAL_PATH)/device.mk)

PRODUCT_BRAND := realme
PRODUCT_DEVICE := RMX1921
PRODUCT_MANUFACTURER := realme
PRODUCT_NAME := pixelage_RMX1921
PRODUCT_MODEL := RMX1921

PRODUCT_GMS_CLIENTID_BASE := android-oppo

PRODUCT_BUILD_PROP_OVERRIDES += \
    BuildDesc="RMX1921-user 11 RKQ1.201217.002 1651205774457 release-keys" \
    BuildFingerprint=realme/RMX1921/RMX1921:11/RKQ1.201217.002/1651205774457:user/release-keys \
    DeviceName=RMX1921 \
    DeviceProduct=RMX1921 \
    SystemDevice=RMX1921 \
    SystemName=RMX1921
