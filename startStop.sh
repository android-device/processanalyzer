#!/bin/bash
./rel/kpiAnalyzer -no chrome &
while true ; do
	read -s input;
	if [ "$input" = "s" ] ; then
		kill $(pidof kpiAnalyzer);
		break;
	else
		kill -TSTP $(pidof kpiAnalyzer);
	fi
	read -s input;
	if [ "$input" = "s" ] ; then
		kill $(pidof kpiAnalyzer);
		break;
	else
		kill -CONT $(pidof kpiAnalyzer);
	fi
done
