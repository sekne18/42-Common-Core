FROM debian:buster

ARG DB_NAME
ARG ADM_USER
ARG ADM_PASS
ARG ROOT_PASS

ENV DB_NAME=$DB_NAME
ENV ADM_USER=$ADM_USER
ENV ADM_PASS=$ADM_PASS
ENV ROOT_PASS=$ROOT_PASS

RUN apt update -y && apt upgrade -y
RUN apt install -y mariadb-server

COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

COPY ./tools/script.sh /script.sh

RUN chmod +x /script.sh

CMD [ "/script.sh" ]

