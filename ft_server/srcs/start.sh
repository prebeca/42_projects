service mysql start

chown -R www-data /var/www/*
chmod -R 755 /var/www/*

#Website folder
mkdir /var/www/domain
chown -R $USER:$USER /var/www/domain
cp srcs/info.php /var/www/domain/info.php

#nginx
cp srcs/domain /etc/nginx/sites-available/domain
ln -s /etc/nginx/sites-available/domain /etc/nginx/sites-enabled/
rm -rf /etc/nginx/sites-enabled/default
rm -rf /etc/nginx/sites-available/default
nginx -t

#MySQL
echo "CREATE DATABASE wordpress;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost' WITH GRANT OPTION;" | mysql -u root --skip-password
echo "update mysql.user set plugin='mysql_native_password' where user='root';" | mysql -u root --skip-password
echo "FLUSH PRIVILEGES;" | mysql -u root --skip-password

#phpmyadmin
wget https://files.phpmyadmin.net/phpMyAdmin/5.0.1/phpMyAdmin-5.0.1-all-languages.tar.gz && mv phpMyAdmin-5.0.1-all-languages.tar.gz /tmp/
tar xvf /tmp/phpMyAdmin-5.0.1-all-languages.tar.gz
mv phpMyAdmin-5.0.1-all-languages/ /var/www/domain/phpmyadmin
cp ./srcs/config.sample.inc.php /var/www/domain/phpmyadmin/config.inc.php

#wordpress
wget -c https://wordpress.org/latest.tar.gz
tar xvf latest.tar.gz
mv wordpress /var/www/domain/
cp ./srcs/wp-config-sample.php /var/www/domain/wordpress/wp-config.php

service php7.3-fpm start
service nginx restart

bash