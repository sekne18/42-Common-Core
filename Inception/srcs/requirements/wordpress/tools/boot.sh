#!/bin/bash

set -x

cd /var/www/html

if [ ! -f wp-config.php ]; then
	wp config create --dbname=${DB_NAME} --dbuser=${ADM_USER} --dbpass=${ADM_PASS} --dbhost=${DB_HOST} --allow-root
fi

wp core install --url="${DOMAIN}" --title="${TITLE}" --admin_user="${ADM_USER}" --admin_password="${ADM_PASS}" --admin_email="${ADM_MAIL}" --skip-email --allow-root || true

wp user create ${NORMAL_USER} ${NORMAL_MAIL} --role=author --user_pass=${NORMAL_PASS} --allow-root || true

wp theme install https://public-api.wordpress.com/rest/v1/themes/download/hola.zip --activate --allow-root || true

mkdir -p /run/php

/usr/sbin/php-fpm7.3 -F

