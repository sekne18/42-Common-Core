FROM debian:buster

ARG DOMAIN
ARG CERTS_

ENV DOMAIN=$DOMAIN
ENV CERTS_=$CERTS_

RUN apt update -y && apt upgrade -y
RUN apt install -y nginx openssl

#COPY ./tools/script.sh /script.sh
RUN mkdir -p /var/www/static

# Copy static site files from the bonus folder
COPY ../bonus/static_site/portfolio/ /var/www/static/

# Copy NGINX configuration script
COPY ./nginx/tools/script.sh /script.sh

#RUN mkdir -p /var/www/static

#COPY ../bonus/static-site/ /var/www/static/

RUN chmod +x /script.sh
RUN /script.sh

CMD ["nginx", "-g", "daemon off;"]


