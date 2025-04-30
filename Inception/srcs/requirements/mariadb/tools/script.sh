#!/bin/bash

service mysql start
sleep 5

if [ ! -d "/var/lib/mysql/${DB_NAME}" ]; then
  echo "Initializing new MariaDB setup..."
  mysql -u root -e "CREATE DATABASE IF NOT EXISTS ${DB_NAME};"
  mysql -u root -e "CREATE USER '${DB_USER}'@'%' IDENTIFIED BY '${DB_PWD}';"
  mysql -u root -e "GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';"
  mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PWD}';"
  mysql -u root -e "FLUSH PRIVILEGES;"
  mysqladmin -u root -p"${DB_ROOT_PWD}" shutdown
else
  echo "Database already initialized. Skipping setup."
  mysqladmin -u root -p"${DB_ROOT_PWD}" shutdown
fi

exec mysqld_safe
