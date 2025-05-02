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

    wp config set FORCE_SSL_ADMIN false --type=constant --allow-root

    wp config  set WP_REDIS_HOST $REDIS_HOST --type=constant --allow-root

    wp config set WP_REDIS_PORT $REDIS_PORT --type=constant --allow-root

    wp config  set WP_CACHE true --type=constant --allow-root

    until nc -z "$REDIS_HOST" 6379; do
      echo "Waiting for Redis..."
      sleep 2
    done
    wp plugin install redis-cache --allow-root

    wp plugin activate redis-cache --allow-root



    wp redis enable --allow-root

    chmod 777 /var/www/html/wp-content

    # install theme
    wp theme install twentyfifteen

    wp theme activate twentyfifteen

    wp theme update twentyfifteen
fi


/usr/sbin/php-fpm7.3 -F
