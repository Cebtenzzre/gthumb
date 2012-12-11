/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2010 Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FACEBOOK_CONNECTION_H
#define FACEBOOK_CONNECTION_H

#include <glib-object.h>
#include <json-glib/json-glib.h>
#ifdef HAVE_LIBSOUP_GNOME
#include <libsoup/soup-gnome.h>
#else
#include <libsoup/soup.h>
#endif /* HAVE_LIBSOUP_GNOME */
#include <gthumb.h>

typedef enum {
	FACEBOOK_ACCESS_READ,
	FACEBOOK_ACCESS_WRITE
} FacebookAccessType;

#define FACEBOOK_REDIRECT_URI "https://www.facebook.com/connect/login_success.html"
#define FACEBOOK_HTTP_SERVER "https://www.facebook.com"

#define FACEBOOK_CONNECTION_ERROR facebook_connection_error_quark ()
GQuark facebook_connection_error_quark (void);

#define FACEBOOK_CONNECTION_ERROR_TOKEN_EXPIRED 190

#define FACEBOOK_TYPE_CONNECTION         (facebook_connection_get_type ())
#define FACEBOOK_CONNECTION(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), FACEBOOK_TYPE_CONNECTION, FacebookConnection))
#define FACEBOOK_CONNECTION_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST ((k), FACEBOOK_TYPE_CONNECTION, FacebookConnectionClass))
#define FACEBOOK_IS_CONNECTION(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), FACEBOOK_TYPE_CONNECTION))
#define FACEBOOK_IS_CONNECTION_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), FACEBOOK_TYPE_CONNECTION))
#define FACEBOOK_CONNECTION_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), FACEBOOK_TYPE_CONNECTION, FacebookConnectionClass))

typedef struct _FacebookConnection         FacebookConnection;
typedef struct _FacebookConnectionPrivate  FacebookConnectionPrivate;
typedef struct _FacebookConnectionClass    FacebookConnectionClass;

struct _FacebookConnection
{
	GthTask __parent;
	FacebookConnectionPrivate *priv;
};

struct _FacebookConnectionClass
{
	GthTaskClass __parent_class;
};

GType                facebook_connection_get_type             (void) G_GNUC_CONST;
FacebookConnection * facebook_connection_new                  (void);
void                 facebook_connection_set_access_token     (FacebookConnection    *self,
							       const char            *token);
const char *         facebook_connection_get_access_token     (FacebookConnection    *self);
void                 facebook_connection_add_access_token     (FacebookConnection    *self,
							       GHashTable            *data_set);
void		     facebook_connection_send_message         (FacebookConnection    *self,
						               SoupMessage           *msg,
						               GCancellable          *cancellable,
						               GAsyncReadyCallback    callback,
						               gpointer               user_data,
						               gpointer               source_tag,
						               SoupSessionCallback    soup_session_cb,
						               gpointer               soup_session_cb_data);
GSimpleAsyncResult * facebook_connection_get_result           (FacebookConnection    *self);
void                 facebook_connection_reset_result         (FacebookConnection    *self);

/* utilities */

char *               facebook_utils_get_authorization_url     (FacebookAccessType     access_type);
gboolean             facebook_utils_parse_response            (SoupMessage           *msg,
							       JsonNode             **node,
							       GError               **error);

#endif /* FACEBOOK_CONNECTION_H */
