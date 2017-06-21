read a
read b 
if [ $a -lt $b ];then
	temp=$a
	a=$b
	b=$temp
fi 
ra=`expr $a % $b` 
while [[ $ra -gt 0 ]]
do 
	a=$b
	b=$ra
	ra=`expr $a % $a`
	echo $ra 
done
echo "max==>" $b 

exit 0 		 
