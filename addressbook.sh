#!/bin/bash

file="address.txt"

while true
do
    echo "----- ADDRESS BOOK -----"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"

    echo "Enter your choice:"
    read ch

    case $ch in

    #1)
        > $file
        echo "Address Book Created"
        ;;

    #2)
        cat $file
        ;;

    #3)
        echo "Enter Name:"
        read name
        echo "Enter Phone:"
        read phone
        echo "$name $phone" >> $file
        echo "Record Inserted"
        ;;

    #4)
        echo "Enter Name to Delete:"
        read name
        grep -v "^$name " $file > temp
        mv temp $file
        echo "Record Deleted"
        ;;

    #5)
        echo "Enter Name to Modify:"
        read name
        grep -v "^$name " $file > temp
        echo "Enter New Name:"
        read newname
        echo "Enter New Phone:"
        read phone
        echo "$newname $phone" >> temp
        mv temp $file
        echo "Record Modified"
        ;;

    #6)
        echo "Exit"
        break
        ;;

    #*)
        echo "Invalid Choice"
        ;;

    esac
done
 