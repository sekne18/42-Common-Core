CONTAINERS := $(shell docker ps -qa)
IMAGES := $(shell docker images -qa)
VOLUMES := $(shell docker volume ls -q)
NETWORKS := $(shell (docker network ls -q 2>&1 >/dev/null))

all:
	mkdir -p /home/jsekne/data/wordpress /home/jsekne/data/mariadb
	docker compose -f srcs/docker-compose.yml up -d

fclean:
	docker stop $(CONTAINERS) || true; docker rm $(CONTAINERS) || true; docker rmi -f $(IMAGES) || true; docker volume rm $(VOLUMES) || true; docker network rm $(NETWORKS) || true

re: fclean all

%:
	docker-compose -f srcs/docker-compose.yml $@

.PHONY: all fclean re
