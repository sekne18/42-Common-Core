#!/bin/bash

# Checking /etc/hosts file for 127.0.0.1
# and changing localhost to domain name
# only if 127.0.0.1 is at the first lines of the file
target='/etc/hosts'
localhost="localhost"
domain="jsekne.42.fr"
domain2="www.jsekne.42.fr"
dns=$(cat $target | awk '$1 ~ /^127.0.0.1/ { print $2 }')
dns2=$(cat $target | awk '$1 ~ /^127.0.0.1/ { print $3 }')
line=$(cat /etc/hosts | grep -n "^127.0.0.1" | awk '{print $1}' | cut -d : -f 1)

echo -e "${CY}⣿⣿⣿ setup.sh ⣿⣿⣿${NC}"
if [[ "$dns" = "$localhost" ]]; then
    sudo sed -i '1s/'"$localhost"'/'"$domain $domain2"'/' "$target"
    dns=$(cat $target | awk '$1 ~ /^127.0.0.1/ { print $2 }')
    dns2=$(cat $target | awk '$1 ~ /^127.0.0.1/ { print $3 }')
fi
if [[ "$dns" = "$domain" ]]; then
    echo -e "Domain${GR} [ok] ${YL} $dns $dns2${NC}"
fi
