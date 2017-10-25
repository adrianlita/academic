#!/bin/bash
clear

RED='\033[0;31m'
NC='\033[0m' # No Color

outname="test.out";
main="main.cpp"

srcfiles=(
    "matrix.cpp"
);

a5src="";
for i in ${srcfiles[@]}
do
    a5src+=" $i";
done


gcccmd="g++ -Wall -m32 $src $main -o $outname"

rm $outname
printf "${RED}Build started...${NC}\n"
$gcccmd
printf "${RED}Build finished...${NC}\n"

printf "${RED}Running C++${NC}\n"
./$outname
printf "${RED}Finished.${NC}\n"
