## Copyright (c) 2024 Ambarella International LP
##
## This file and its contents ("Software") are protected by intellectual
## property rights including, without limitation, U.S. and/or foreign
## copyrights. This Software is also the confidential and proprietary
## information of Ambarella International LP and its licensors. You may not use, reproduce,
## disclose, distribute, modify, or otherwise prepare derivative works of this
## Software or any portion thereof except pursuant to a signed license agreement
## or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
## In the absence of such an agreement, you agree to promptly notify and return
## this Software to Ambarella International LP
##
## THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
## INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
## MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
## IN NO EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT,
## INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
## (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
## LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR BUSINESS
## INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
## CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
## POSSIBILITY OF SUCH DAMAGE.

LIBS += audit
audit_BASENAME=audit-2.8.5
audit_ARCHIVE=$(audit_BASENAME).tar.gz
audit_URL=https://people.redhat.com/sgrubb/audit/$(audit_ARCHIVE)

LIBS += bfd
bfd_BASENAME=binutils-2.25.1
bfd_ARCHIVE=$(bfd_BASENAME).tar.bz2
bfd_URL=http://ftp.gnu.org/gnu/binutils/$(bfd_ARCHIVE)

LIBS += bzip2
bzip2_BASENAME=bzip2-1.0.6
bzip2_ARCHIVE=$(bzip2_BASENAME).tar.gz
bzip2_URL=https://nchc.dl.sourceforge.net/project/bzip2/$(bzip2_ARCHIVE)

LIBS += elfutils
elfutils_BASENAME=elfutils-0.163
elfutils_ARCHIVE=$(elfutils_BASENAME).tar.bz2
elfutils_URL=https://fedorahosted.org/releases/e/l/elfutils/0.163/$(elfutils_ARCHIVE)

LIBS += lzma
lzma_BASENAME=xz-5.2.1
lzma_ARCHIVE=$(lzma_BASENAME).tar.gz
lzma_URL=http://tukaani.org/xz/$(lzma_ARCHIVE)

LIBS += slang
slang_BASENAME=slang-2.3.2
slang_ARCHIVE=$(slang_BASENAME).tar.bz2
slang_URL=https://www.jedsoft.org/releases/slang/$(slang_ARCHIVE)

LIBS += unwind
unwind_BASENAME=libunwind-1.6.2
unwind_ARCHIVE=$(unwind_BASENAME).tar.gz
unwind_URL=http://download.savannah.gnu.org/releases/libunwind/$(unwind_ARCHIVE)

LIBS += zlib
zlib_BASENAME=zlib-1.2.13
zlib_ARCHIVE=$(zlib_BASENAME).tar.gz
zlib_URL=http://zlib.net/$(zlib_ARCHIVE)

DLDIR=dl
DEPSDIR=deps-$(ARCH)
BUILDDIR=build-$(ARCH)
HOST=$(shell echo $(CROSS_COMPILE) | sed 's/.$$//')
PREFIX=$(realpath $(shell pwd))/$(DEPSDIR)
MAKE1=$(MAKE) -j1

CC=$(CROSS_COMPILE)gcc

export CC

.PHONY: all clean $(LIBS)

all: $(LIBS)

define LIB_template
$1_DIR=$$(BUILDDIR)/$$($1_BASENAME)
$1_EXTRACT=$$($1_DIR)/.extract
$1_INSTALL=$$(DEPSDIR)/lib/.$1.install

$$(DLDIR)/$$($1_ARCHIVE):
	mkdir -p $$(DLDIR) && cd $$(DLDIR) && wget -N --no-check-certificate $$($1_URL)
	mkdir -p $$(DLDIR) && cd $$(DLDIR)

$$($1_EXTRACT): $$(DLDIR)/$$($1_ARCHIVE)
	mkdir -p $$(BUILDDIR) && tar xf $$< -C $$(BUILDDIR)
	touch $$@

$1: $$($1_INSTALL)

$1-clean:
	rm -rf $$($1_DIR)
endef

$(foreach lib,$(LIBS),$(eval $(call LIB_template,$(lib))))

$(audit_INSTALL): $(audit_EXTRACT)
	#cp $(CURDIR)/$(DLDIR)/libaudit.h $(audit_DIR)/lib
	cd $(audit_DIR) && ./configure --host=$(HOST) --prefix=$(PREFIX) --disable-zos-remote
	$(MAKE) -C $(audit_DIR)/lib
	$(MAKE) -C $(audit_DIR)/lib install
	touch $@

CFLAGS=-I$(PREFIX)/include -Wno-error=use-after-free -Wno-error=missing-attributes -Wno-error=misleading-indentation -Wno-error=nonnull-compare -Wno-error=implicit-fallthrough -Wno-error=absolute-value -Wno-error=format-truncation
LDFLAGS=-L$(PREFIX)/lib

$(bfd_INSTALL): $(zlib_INSTALL) $(bfd_EXTRACT)
	cd $(bfd_DIR)/libiberty && ./configure --host=$(HOST) --prefix=$(PREFIX) --enable-install-libiberty
	$(MAKE) -C $(bfd_DIR)/libiberty
	$(MAKE) -C $(bfd_DIR)/libiberty install
	cd $(bfd_DIR)/bfd && CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" ./configure --host=$(HOST) --prefix=$(PREFIX) --with-zlib
	$(MAKE) -C $(bfd_DIR)/bfd
	$(MAKE) -C $(bfd_DIR)/bfd install
	touch $@

$(bzip2_INSTALL): $(bzip2_EXTRACT)
	$(MAKE) -C $(bzip2_DIR) clean
	$(MAKE) CC="$(CC)" PREFIX=$(PREFIX) -C $(bzip2_DIR) -f Makefile-libbz2_so
	mkdir -p $(DEPSDIR)/lib
	cp -a $(bzip2_DIR)/libbz2.so* $(DEPSDIR)/lib/
	@rm -f $(DEPSDIR)/lib/libbz2.so
	# The dynamic library is required to prevent errors while building elfutils
	cd $(DEPSDIR)/lib && ln -s libbz2.so.1.0 libbz2.so
	$(MAKE) -C $(bzip2_DIR) clean
	$(MAKE) CC="$(CC)" PREFIX=$(PREFIX) -C $(bzip2_DIR) install
	touch $@

elfutils_LDFLAGS=$(LDFLAGS) -Wl,-rpath-link $(PREFIX)/lib

$(elfutils_INSTALL): $(zlib_INSTALL) $(lzma_INSTALL) $(bzip2_INSTALL) $(elfutils_EXTRACT)
	cd $(elfutils_DIR) && CFLAGS="$(CFLAGS)" LDFLAGS="$(elfutils_LDFLAGS)" ./configure --host=$(HOST) --prefix=$(PREFIX) --with-zlib --with-bzlib --with-lzma
	$(MAKE) -C $(elfutils_DIR)
	$(MAKE) -C $(elfutils_DIR) install
	touch $@

$(lzma_INSTALL): $(lzma_EXTRACT)
	cd $(lzma_DIR) && ./configure --host=$(HOST) --prefix=$(PREFIX)
	$(MAKE) -C $(lzma_DIR)
	$(MAKE) -C $(lzma_DIR) install
	touch $@

$(slang_INSTALL): $(slang_EXTRACT)
	cd $(slang_DIR) && ./configure --host=$(HOST) --prefix=$(PREFIX) --with-pcre=no --with-pcrelib=no --with-pcreinc=no --with-png=no
	$(MAKE1) -C $(slang_DIR)
	$(MAKE1) -C $(slang_DIR) install-all
	touch $@

$(zlib_INSTALL): $(zlib_EXTRACT)
	cd $(zlib_DIR) && ./configure --prefix=$(PREFIX)
	#cp $(CURDIR)/$(DLDIR)/Makefile.zlib $(zlib_DIR)/Makefile
	$(MAKE) -C $(zlib_DIR)
	$(MAKE) -C $(zlib_DIR) install
	touch $@

$(unwind_INSTALL): $(unwind_EXTRACT)
	cd $(unwind_DIR) && ./configure --host=$(HOST) --prefix=$(PREFIX) --enable-debug --enable-debug-frame
	cd $(unwind_DIR) && $(MAKE)
	cd $(unwind_DIR) && $(MAKE) install
	touch $@

clean:
	rm -rf $(BUILDDIR)
	rm -rf $(DEPSDIR)
