include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package.mk

PKG_NAME:=helloworld
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_INSTALL_DIR:=$(PKG_BUILD_DIR)/ipkg-install


define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=hello world example
endef

define Package/$(PKG_NAME)/description
	hello world
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef


TARGET_CFLAGS += \
	-I$(STAGING_DIR)/usr/include 

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	CC="$(TARGET_CC)" \
	AR="$(TARGET_CROSS)ar" \
	LD="$(TARGET_CROSS)ld" \
	CFLAGS="$(TARGET_CFLAGS)   $(TARGET_CPPFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS) -L$(STAGING_DIR)/usr/lib" 
endef


define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/helloworld $(1)/bin/
	$(CP) ./files/hello.init $(1)/etc/init.d/hello
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
