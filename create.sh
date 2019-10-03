#!/bin/sh

printf "Input File Name >> "; read FILE
printf "Input Overview >> "; read OVERVIEW
cp ./template.cc ${FILE}

# Replace
sed -i -e "s/FILENAME/"${FILE}"/g" ${FILE} && \rm ${FILE}
sed -i -e "s/OVERVIEW/"${OVERVIEW}"/g" ${FILE} && \rm ${FILE}
# sed -i -e "s/DATE/"$(date)"/g" ${FILE}

# delete backup file
\rm ${FILE}-e
