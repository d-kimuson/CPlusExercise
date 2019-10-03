#!/bin/sh

printf "Input File Name >> "; read FILE
printf "Input Overview >> "; read OVERVIEW
cp ./template.cc ${FILE}

# Replace
sed -i -e "s/FILENAME/"${FILE}"/g" ${FILE}
sed -i -e "s/OVERVIEW/"${OVERVIEW}"/g" ${FILE}
DATE=$(date | sed "s/年 /-/g" | sed "s/月 /-/g" | sed "s/日.*//g")
sed -i -e "s/DATE/"${DATE}"/g" ${FILE}

# delete backup file
\rm ${FILE}-e
