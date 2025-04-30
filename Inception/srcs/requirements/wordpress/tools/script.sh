#!bin/bash

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


#!/bin/bash

#set -x

#mkdir /var/www
#mkdir /var/www/html

#cd /var/www/html

#rm -rf *

#curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar

#chmod +x wp-cli.phar

#mv wp-cli.phar /usr/local/bin/wp

#wp core download --allow-root

#sed -i 's/listen = \/run\/php\/php7.3-fpm.sock/listen = 9000/g' /etc/php/7.3/fpm/pool.d/www.conf

