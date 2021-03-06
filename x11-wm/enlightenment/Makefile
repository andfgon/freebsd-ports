# Created by: Yukihiro Nakai <Nakai@Mlab.t.u-tokyo.ac.jp>
# $FreeBSD$

PORTNAME=	enlightenment
PORTVERSION=	0.21.7
PORTREVISION=	1
PORTEPOCH=	2
CATEGORIES=	x11-wm enlightenment
MASTER_SITES=	http://download.enlightenment.org/rel/apps/${PORTNAME}/
DIST_SUBDIR=	enlightenment

MAINTAINER=	enlightenment@FreeBSD.org
COMMENT=	Artistic X window manager

LICENSE=	BSD2CLAUSE

LIB_DEPENDS=	libefl.so:devel/efl \
		libxcb-keysyms.so:x11/xcb-util-keysyms

GNU_CONFIGURE=	yes
USES=		alias autoreconf desktop-file-utils execinfo gettext-tools \
		gmake iconv libtool pathfix pkgconfig tar:xz
USE_XORG=	xcb
USE_LDCONFIG=	yes
INSTALL_TARGET=	install-strip
SUB_FILES=	pkg-message

CONFIGURE_ARGS=	--with-profile=MEDIUM_PC \
		--disable-connman --disable-bluez4 \
		--disable-device-udev --disable-mount-udisks

.include "Makefile.plist"

OPTIONS_DEFINE=		NLS
OPTIONS_GROUP=		MIXER
OPTIONS_GROUP_MIXER=	ALSA PULSEAUDIO
OPTIONS_DEFAULT=	ALSA
OPTIONS_SUB=		yes

NLS_USES=		gettext-runtime
NLS_CONFIGURE_ENABLE=	nls

ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
PULSEAUDIO_LIB_DEPENDS=	libpulse.so:audio/pulseaudio

post-patch:
	@${REINPLACE_CMD} -e \
		's/\(setuid_root_mode = a=rx,u+x\)s/\1/g' \
		${WRKSRC}/src/bin/Makefile.mk \
		${WRKSRC}/src/modules/Makefile_cpufreq.mk

.include <bsd.port.pre.mk>

.if ${ARCH} == "sparc64"
BROKEN=		Does not install on sparc64: signal 10
.endif

.include <bsd.port.post.mk>
