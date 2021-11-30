#!/bin/bash

if (( $# != 1 ));
then
	echo "Usage: $0 <fileToCreate>"
	exit 1
fi

if [ -f $1 ]
then
	rm $1
fi

numberElementLine=0
for (( i=0;i <256; i++ ))
do
	printf "{\"\"," >> $1
	printf  "0x%02X" $i >> $1
	printf ",NULL}, " >> $1
	let "numberElementLine=numberElementLine+1"
	if (( $numberElementLine >= 32 ));
	then
		printf "\n" >> $1
		numberElementLine=0
	fi
done

exit 0
