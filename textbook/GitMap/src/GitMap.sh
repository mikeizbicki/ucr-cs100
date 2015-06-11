#!/bin/bash/

#Beginning comment
path=$1
currDir=`pwd`

if [ -z "$path" ]
then
	echo "Path was not specified. Script will execute in current directory"
	path='.'
fi

cd $path

#make temporary files that will assure us that no file of that name exists
temp_file="$(mktemp)"
temp_file2="$(mktemp)"
temp_file3="$(mktemp)"
tempDir="$(mktemp -d XXX --tmpdir='.')"
lsInfo="$(mktemp XXX --tmpdir='.')"
map="Mike_Izbicki's_Treasure_Map"

#create file to get all branch names
git branch > $temp_file	

#filter out the branch we are currently in
cat $temp_file | grep '\*' > $temp_file2
currBranch=`cat $temp_file2 | awk '{print $2;}'`

#find how many times we need to loop, so how many branches there are
branches=`wc -l $temp_file | awk '{print $1;}'`

#this will let us traverse all our branches as if they were in a vector of string
count=1
changed=0
fileEnd2="Branch2"
#fileEnd="Branch"
while [ $count -le $branches ]
do
	sed -n ''$count'p' < $temp_file | awk '{print $1;}' > $temp_file3
	atBranch=`cat $temp_file3`
	totalBranch2=$atBranch$fileEnd2
	totalBranch=$atBranch
	if [ "$atBranch" != "*" ]
		then
			git checkout $atBranch
			((changed++))
	else
			totalBranch2=$currBranch$fileEnd2
			totalBranch=$currBranch
			git checkout $currBranch
	fi
	git log > $totalBranch2
	cat $totalBranch2 | sed "s/commit.*//g" | sed "s/Merge:.*//g" | sed 's/<.*>//g' | sed 's/-0700//g' | sed '/^\s*$/d' > $tempDir\/$totalBranch
	echo $totalBranch >> $lsInfo
	rm $totalBranch2
	((count++))
done

if [ $changed -gt 0 ]
then
	git checkout $currBranch
fi

rm $temp_file
rm $temp_file2
rm $temp_file3

echo "Please wait a minute"
#init for boxes
function findLength {
	fileSize=`wc -l $2 | awk '{print $1;}'`
	length=0
	lineNum=$1
	lineNumCond=$(($lineNum+4))

	lineCnt=0

	while [ $lineCnt -ne $lineNumCond -a $lineCnt -ne $fileSize ]
	do
		read -r lengthLine
		lengthLineSeg=`echo $lengthLine | awk '{print $1;}'`
		
		if [ $(($lineCnt+1)) == $lineNumCond ]
		then
			if [ "$lengthLineSeg" != "Author:" ]
			then
				((lineCnt--))
			fi
		fi

		if [ $lineCnt -ge $lineNum ]
		then
			currLength=`echo $lengthLine | wc -L`
			if [ $currLength -gt $length ]
			then
				length=$currLength
			fi
		fi
		((lineCnt++))
	done <$2

	boxCnt=0
	boxLength="_"
	lineSeg="_"

	while [ $boxCnt -ne $length ]
	do
		boxLength=$boxLength$lineSeg
		((boxCnt++))
	done
}

function width {
	compare=$1
	base=0
	LineLength=${#line}
	remaining=$((length - LineLength))
	((remaining--))
	if [ $compare -gt $base ]
	then
		((remaining++))
		((remaining++))
	fi
	space='.'
	tempCnt=0
	while [ $tempCnt -le $(($remaining+1)) ]
	do
		line=$line$space
		((tempCnt++))
	done
	edge="|"
	line=$line$edge
	#echo $line >> $map
}


lsInfoSize=`wc -l $lsInfo | awk '{print $1;}'`
dateString=''
historySize=`wc -l $tempDir/master | awk '{print $1;}'`
count=0
lineCntParam=0
special=0
while read -r line
do
	outputLine=1
	firstSegLine=`echo $line | awk '{print $1;}'`

	#find proper length
	if [ $(($count%3)) == 0 ]
	then
		if [ "$firstSegLine" = "Author:" ]
		then
			if [ $count -ne 0 ]
			then
				boxLength='|'$boxLength'|'
				echo $boxLength >> $map
				echo "" >> $map
			fi
			findLength $lineCntParam "$tempDir/master"
		else
			((count--))
		fi
	fi
	
	if [ "$firstSegLine" = "Author:" ]
	then
		if [ $count -ne 0 ]
		then
			echo ^ >> $map; echo \| >> $map
		fi
		boxLength=$boxLength
		echo '.'$boxLength >> $map
		newLineCnt=0
		newLineGuard=''
		while [ $newLineCnt -ne $(($boxCnt+1)) ]
		do
			newLineGuard=$newLineGuard$'.'
			((newLineCnt++))
		done
		newLineGuard='|'$newLineGuard'|'
		echo $newLineGuard >> $map

		special=0
		width $special	
		outputLine=0
		line='|'$line
		echo $line >> $map
	fi

	if [ "$firstSegLine" = "Date:" ]
		then
			dateString=$line
			special=1
			width $special	
			outputLine=0
			line='|'$line
			echo $line >> $map
		fi

	if [ "$firstSegLine" != "Author:" -a "$firstSegLine" != "Date:" ]
	then
		branchCnt=0
		sameDate=0
		while read -r fileName
		do
			fileNamePlain=$fileName
			fileName=$tempDir\/$fileName
			count2=0

			while [ $count2 -ne 3 ]
			do
				read -r compareLine

				#if [[ "$fileNamePlain" = "signals" ]]
				#then
				#	echo $compareLine >> help
				#	echo $line >> help
				#fi

				if [ $count2 -eq 1 ] #compare date
				then
					if [ "$compareLine" = "$dateString" ]
					then
						sameDate=1
					fi
				fi

				if [[ $sameDate -eq 1 ]] && [[ $count2 -eq 2 ]] #compare commit message
				then
					if [[ "$compareLine" = "$line" ]] || [[ "$compareLine" = "$lineBackup" ]]
					then
						if [ $outputLine -eq 1 ]
						then
							special=0
							lineBackup=$line
							width $special	
							label=$line" -----> ("$fileNamePlain")"
						fi
						
						if [ $outputLine -eq 0 ]
						then
							label=$label" -----> ("$fileNamePlain")"
						fi
						outputLine=0
					fi
				fi
				((count2++))
			done <$fileName
			
			if [[ $(($branchCnt+1)) -eq $lsInfoSize ]] && [[ $outputLine -eq 0 ]]
			then
				label='|'$label
				echo $label >> $map
			fi
			
			((branchCnt++))
		done <$lsInfo
	fi

	if [ $outputLine -ne 0 ]
	then
		special=0
		width $special	
		line='|'$line
		echo $line >> $map
	fi

	((lineCntParam++))	
	((count++))

	if [ $lineCntParam -eq "$historySize" ]
	then
		boxLength='|'$boxLength'|'
		echo $boxLength >> $map
	fi

done <$tempDir\/master

rm $lsInfo
rm -rf $tempDir

cd $currDir
