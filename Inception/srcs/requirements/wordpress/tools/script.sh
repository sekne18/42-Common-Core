#!/bin/bash

# wait for mysql to start
sleep 10
# Install Wordpress

if [ ! -f /var/www/html/wp-config.php ]; then
    wp config create --dbname=$DB_NAME --dbuser=$DB_USER \
        --dbpass=$DB_PWD --dbhost=$DB_HOST --allow-root  --skip-check

    wp core install --url=$DOMAIN --title=$TITLE --admin_user=$WP_ADMIN_USER \
        --admin_password=$WP_ADMIN_PWD --admin_email=$WP_ADMIN_MAIL \
        --allow-root

    wp user create $WP_USER $WP_MAIL --role=author --user_pass=$WP_PWD --allow-root

    chmod 777 /var/www/html/wp-content

    # install theme
    wp theme install twentyfifteen

    wp theme activate twentyfifteen

    wp theme update twentyfifteen
fi


/usr/sbin/php-fpm7.3 -F
