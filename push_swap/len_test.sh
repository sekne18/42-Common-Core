#!/bin/bash

VERIFY=0
IS_RAND=0
COUNT=0
PRINT=0
INPUT=0
MIN_VAL=0
MAX_VAL=500
INC=1

show_help() {
	echo "Usage:"
       	echo "	./len_test.sh [-r] [-i] [-c] [-v] [-p] [-m number] [-M number] [-h]"
	echo
	echo "Options:"
	echo "	-i	print input"
	echo "	-v	verify if output sorts"
	echo "	-c	print amount of operations"
	echo "	-p	print operations"
	echo "	-r	random numbers instead of incremental"
	echo "	-m	set minimun boundary"
	echo "	-M	set maximum boundary"
	echo "	-h	print this"
}

while getopts "n:ricvpm:M:h" opt; do
	case $opt in
		m)
			MIN_VAL=$OPTARG
			;;
		M)
			MAX_VAL=$OPTARG
			;;
		r)	
			IS_RAND=1
			;;
		v)	
			VERIFY=1
			;;
		c)	COUNT=1
			;;
		p)
			PRINT=1
			;;
		i)
			INPUT=1
			;;
		h)	
			show_help
			exit 0
			;;
	esac
done

if (( $MIN_VAL > $MAX_VAL )); then
	INC=-1
fi

RESULT=$(seq $MIN_VAL $INC $MAX_VAL)
if [[ $IS_RAND > 0 ]]; then
	RESULT=$(echo "$RESULT" | shuf)
fi
RESULT=$(echo "$RESULT" | tr '\n' ' ')
if [[ $INPUT -gt 0 ]]; then
	echo "$RESULT"
fi
./push_swap "$RESULT" > tmp.txt
if [[ $PRINT -gt 0 ]]; then
	cat tmp.txt
fi
if [[ $COUNT -gt 0 ]]; then
	cat tmp.txt | wc -l 
fi
if [[ $VERIFY -gt 0 ]]; then
	cat tmp.txt | ./checker_linux "$RESULT"
fi
rm tmp.txt
