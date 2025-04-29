FROM debian:buster

ARG DOMAIN
ARG DB_NAME
ARG ADM_PASS
ARG ADM_USER
ARG DB_HOST
ARG TITLE
ARG ADM_MAIL
ARG NORMAL_USER
ARG NORMAL_PASS
ARG NORMAL_MAIL

ENV DOMAIN=${DOMAIN}
ENV DB_NAME=${DB_NAME}
ENV ADM_PASS=${ADM_PASS}
ENV ADM_USER=${ADM_USER}
ENV DB_HOST=${DB_HOST}
ENV TITLE=${TITLE}
ENV ADM_MAIL=${ADM_MAIL}
ENV NORMAL_USER=${NORMAL_USER}
ENV NORMAL_PASS=${NORMAL_PASS}
ENV NORMAL_MAIL=${NORMAL_MAIL}

RUN apt update -y && apt upgrade -y
RUN apt install -y php-fpm php-mysql curl

COPY ./tools/script.sh /script.sh
COPY ./tools/boot.sh /boot.sh

RUN chmod +x /script.sh
RUN chmod +x /boot.sh

RUN /script.sh

RUN chown -R www-data:www-data /var/www/html

CMD ["/boot.sh"]

