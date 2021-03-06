#!/bin/bash
clear

RED='\033[0;31m'
NC='\033[0m' # No Color

outname="aBigNum.out";
main="main_aBigNum.cpp"

srcfiles=(
    "aBigNum/aBigNum.cpp"
);

src="";
for i in ${srcfiles[@]}
do
    src+=" $i";
done

gcccmd="g++ -Wall -m32 $src $main -o $outname"

rm $outname
printf "${RED}Build started...${NC}\n"
$gcccmd
printf "${RED}Build finished...${NC}\n"

printf "${RED}Running C++${NC}\n"
./$outname
printf "${RED}Finished.${NC}\n"
