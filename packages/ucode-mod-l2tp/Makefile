include $(TOPDIR)/rules.mk

PKG_NAME:=ucode-mod-l2tp
PKG_RELEASE:=0
PKG_MAINTAINER:=Packet Please <pktpls@systemli.org>

include $(INCLUDE_DIR)/package.mk

define Package/ucode-mod-l2tp
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=ucode l2tp module
  DEPENDS:=+libucode +libubox +libnl-tiny
  EXTRA_DEPENDS:=+kmod-l2tp
endef

define Package/ucode-mod-l2tp/description
The l2tp module provides functionality for creating and configuring
l2tp interfaces using the kernel generic netlink API.
endef

define Package/ucode-mod-l2tp/install
	$(INSTALL_DIR) $(1)/usr/lib/ucode
	$(CP) $(PKG_BUILD_DIR)/l2tp.so $(1)/usr/lib/ucode/
endef

define Build/Configure
endef

TARGET_CFLAGS += \
	-D_GNU_SOURCE \
	-I$(STAGING_DIR)/usr/include/libnl-tiny

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) $(FPIC) \
		-Wall -ffunction-sections -Wl,--gc-sections -shared -Wl,--no-as-needed -lubox -lnl-tiny \
		-o $(PKG_BUILD_DIR)/l2tp.so $(PKG_BUILD_DIR)/l2tp.c
endef

$(eval $(call BuildPackage,ucode-mod-l2tp))
