#!/bin/bash

service mysql start
sleep 5

mysql -e "CREATE DATABASE IF NOT EXISTS ${DB_NAME};"
mysql -e "CREATE USER '${DB_USER}'@'%' IDENTIFIED BY '${DB_PWD}';"
mysql -e "GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';"
mysql -u${DB_ROOT_USER} -p${DB_ROOT_PWD} -e "ALTER USER '${DB_ROOT_USER}'@'localhost' IDENTIFIED BY '${DB_ROOT_PWD}';"
mysql -e "FLUSH PRIVILEGES;"
mysqladmin -u${DB_ROOT_USER} -p${DB_ROOT_PWD} shutdown

mysqladmin -u root -p${DB_ROOT_PWD} shutdown

exec mysqld_safe

#if [ ! -d "/var/lib/mysql/mysql" ]; then
#    echo "Initializing MySQL data directory..."
#    mysql_install_db --user=mysql
#fi

#mysqld_safe &

#until mysqladmin ping 2>/dev/null; do
#    echo "Waiting for MySQL to be ready..."
#    sleep 2
#done

# Prepare SQL commands
#echo "Setting up database and users..."
#mysql -u root -p"${ROOT_PASS}" << EOF
#CREATE DATABASE IF NOT EXISTS ${DB_NAME};
#CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_PWD}';
#GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';
#ALTER USER 'root'@'localhost' IDENTIFIED BY '${ROOT_PASS}';
#FLUSH PRIVILEGES;
#EOF

#mysqladmin -u root -p"${ROOT_PASS}" shutdown

#echo "Starting MySQL..."
#exec mysqld
