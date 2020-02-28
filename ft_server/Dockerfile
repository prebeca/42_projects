FROM debian:buster

COPY ./srcs/ ./srcs/

RUN apt-get update && apt-get install -y \
    wget \
    nginx \
    php-fpm php-mysql php-mbstring php-zip php-gd \
    mariadb-server

CMD bash srcs/start.sh
