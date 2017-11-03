#!/bin/bash
clear

RED='\033[0;31m'
NC='\033[0m' # No Color

outname="sysinfo.out";
main="sysinfo.c"

gcccmd="gcc -Wall $main -o $outname"

rm $outname
printf "${RED}Build started...${NC}\n"
$gcccmd
printf "${RED}Build finished...${NC}\n"

printf "${RED}Running...${NC}\n"
./$outname
printf "${RED}Finished.${NC}\n"
