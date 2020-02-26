FROM debian:buster

EXPOSE 80

COPY ./srcs/ ./srcs/

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y wget
RUN apt-get install -y nginx
RUN apt-get install -y php-fpm php-mysql php-mbstring php-zip php-gd
RUN apt-get install -y mariadb-server


CMD bash srcs/start.sh