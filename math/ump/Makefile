# Created by: Nicola Vitale <nivit@email.it>
# $FreeBSD$

PORTNAME=	ump
PORTVERSION=	0.8.6
PORTREVISION=	10
CATEGORIES=	math
MASTER_SITES=	SF/u-m-p/u-m-p/${PORTVERSION}
PKGNAMESUFFIX=	-math

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Graphical, easy to use math program

LICENSE=	GPLv2

USES=		gmake pkgconfig tar:bzip2
USE_GNOME=	gtk20
USE_GL=		glu

ALL_TARGET=	${PORTNAME}

CONFLICTS=	ump-1.[0-9]*

DESKTOP_ENTRIES="Ump" "" "" "ump" "Education;Math;Science;GTK;" ""

post-patch:
	@${REINPLACE_CMD} -e 's|%%PREFIX%%|${PREFIX}|' ${WRKSRC}/src/main.cpp

post-install:
	${INSTALL_DATA} ${WRKSRC}/ump.conf \
		${STAGEDIR}${PREFIX}/etc/ump.conf.sample

.include <bsd.port.mk>
