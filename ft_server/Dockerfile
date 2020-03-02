FROM debian:buster

COPY ./srcs/ ./srcs/

RUN apt-get update && apt-get install -y \
    wget \
    nginx \
    php7.3-fpm php7.3-mysql php7.3-mbstring php7.3-zip php7.3-gd \
    mariadb-server \
    openssl

CMD bash srcs/start.sh
