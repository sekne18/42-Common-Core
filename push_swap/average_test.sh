#!/bin/bash

INPUT=0
RUNS=1
MIN_VAL=1
MAX_VAL=500

show_help() {
	echo "Usage:"
       	echo "	./average_test.sh [-c] [-l] [-h]"
	echo
	echo "Options:"
	echo "	-l	specify input length"
	echo "	-c	number of runs"
	echo "	-h	print this"
}

while getopts "hl:c:" opt; do
	case $opt in
		l)	MAX_VAL=$OPTARG
			;;
		c)	RUNS=$OPTARG
			;;
		h)	
			show_help
			exit 0
			;;
	esac
done

RESULT=$(seq $MIN_VAL $INC $MAX_VAL)
RESULT=$(echo "$RESULT" | shuf)
RESULT=$(echo "$RESULT" | tr '\n' ' ')
if [[ $INPUT -gt 0 ]]; then
	echo "$RESULT"
fi
ARRAY=()
ITERATION=0
while [[ $ITERATION -lt $RUNS ]]; do
	COUNT=$(./len_test.sh -rc -m $MIN_VAL -M $MAX_VAL)
	ARRAY+=($COUNT)
	ITERATION=$((ITERATION+1))
done
SUM=0
MAX=${ARRAY[0]}
MIN=${ARRAY[0]}
for NUM in "${ARRAY[@]}"; do
	if [[ $NUM -gt $MAX ]]; then
		MAX=$NUM
	fi
	if [[ $NUM -lt $MIN ]]; then
		MIN=$NUM
	fi
	SUM=$((SUM + NUM))
done
AVG=$((SUM / RUNS))
echo "avg ops for input length of $MAX_VAL: $AVG"
echo "min: $MIN | max: $MAX"
