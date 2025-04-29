FROM debian:buster

ARG DOMAIN
ARG CERTS_

ENV DOMAIN=$DOMAIN
ENV CERTS_=$CERTS_

RUN apt update -y && apt upgrade -y
RUN apt install -y nginx openssl

COPY ./tools/script.sh /script.sh

RUN chmod +x /script.sh
RUN /script.sh

CMD ["nginx", "-g", "daemon off;"]


