--- src/wayland-server.c.orig	2016-09-20 17:33:11.000000000 +0000
+++ src/wayland-server.c	2016-12-13 20:07:06.878000000 +0000
@@ -25,6 +25,8 @@
 
 #define _GNU_SOURCE
 
+#include "../config.h"
+
 #include <stdlib.h>
 #include <stdint.h>
 #include <stddef.h>
@@ -43,6 +45,11 @@
 #include <sys/file.h>
 #include <sys/stat.h>
 
+#ifdef HAVE_SYS_UCRED_H
+#include <sys/types.h>
+#include <sys/ucred.h>
+#endif
+
 #include "wayland-util.h"
 #include "wayland-private.h"
 #include "wayland-server.h"
@@ -79,7 +86,13 @@
 	struct wl_list link;
 	struct wl_map objects;
 	struct wl_signal destroy_signal;
+#ifdef HAVE_SYS_UCRED_H
+	/* FreeBSD */
+	struct xucred xucred;
+#else
+	/* Linux */
 	struct ucred ucred;
+#endif
 	int error;
 	struct wl_signal resource_created_signal;
 };
@@ -466,10 +479,20 @@
 	if (!client->source)
 		goto err_client;
 
+#if defined(SO_PEERCRED)
+	/* Linux */
 	len = sizeof client->ucred;
 	if (getsockopt(fd, SOL_SOCKET, SO_PEERCRED,
 		       &client->ucred, &len) < 0)
 		goto err_source;
+#elif defined(LOCAL_PEERCRED)
+	/* FreeBSD */
+	len = sizeof client->xucred;
+	if (getsockopt(fd, SOL_SOCKET, LOCAL_PEERCRED,
+		       &client->xucred, &len) < 0 ||
+		       client->xucred.cr_version != XUCRED_VERSION)
+		goto err_source;
+#endif
 
 	client->connection = wl_connection_create(fd);
 	if (client->connection == NULL)
@@ -523,12 +546,23 @@
 wl_client_get_credentials(struct wl_client *client,
 			  pid_t *pid, uid_t *uid, gid_t *gid)
 {
+#ifdef HAVE_SYS_UCRED_H
+	/* FreeBSD */
+	if (pid)
+		*pid = 0; /* FIXME: not defined on FreeBSD */
+	if (uid)
+		*uid = client->xucred.cr_uid;
+	if (gid)
+		*gid = client->xucred.cr_gid;
+#else
+	/* Linux */
 	if (pid)
 		*pid = client->ucred.pid;
 	if (uid)
 		*uid = client->ucred.uid;
 	if (gid)
 		*gid = client->ucred.gid;
+#endif
 }
 
 /** Get the file descriptor for the client
