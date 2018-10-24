insert()
{
echo "Enter name"
read name
echo "Enter Phone"
read phone
echo "Enter Address"
read address
echo "$1|$name|$phone|$address" >> $addressdb
echo "Record Added Succesfully"
}
modify()
{
grep -v -w $1 $addressdb > tempdb
echo "Enter name"
read name
echo "Enter phone"
read phone
echo "Enter address"
read address
cat tempdb > $addressdb
echo "$1|$name|$phone|$address|" >> $addressdb
echo "Record Modified Successfully"
}
delete()
{
grep -v -w $1 $addressdb > tempdb
cat tempdb > $addressdb
echo "Record Deleted Succesfully"
}
echo "Enter the database Name"
read addressdb

if [ -f $addressdb ]
then echo "Database Already Exists"
else
echo "Roll No|Name|Phone No|Address" >$addressdb
fi
while(true)
do
echo "1.Insert Record 2.Display Record 3.Modify Record 4.Delete Record 5.View all Records"
echo "Enter your choice"
read ch
case $ch in
1)
while [ true ]
do
echo "Enter Roll No"
read rollno
if ( grep -w $rollno $addressdb)
then
echo "Record ALready Exists"
else
insert $rollno
break
fi
done
;;
2)
echo "Enter Roll No"
read rollno
if ( grep -w $rollno $addressdb )
then
echo ""
else
echo "Record Absent in Database"
fi
;;
3)
echo "Enter Roll No"
read rollno
if ( grep -w $rollno $addressdb)
then
modify $rollno
else
echo "Record Does Not Exist"
fi
;;
4)
echo "Enter Roll No"
read rollno
if (grep -w $rollno $addressdb )
then
delete $rollno
else
echo "Record Not in Database"
fi
;;
5)
cat $addressdb
;;
6)
exit
break
;;
*)
echo "Enter valid data"
read ch
esac
done

