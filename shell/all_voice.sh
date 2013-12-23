#!/usr/bin/env bash

voices=`say -v ?|cut -d " " -f1`
echo "voices is:$voices"

for i in $voices 
do
	`say -v $i "Hello,I am $i"`
done
