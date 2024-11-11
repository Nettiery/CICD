
#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="2.txt"

for var in -e -i -v -c -l -n -h -s -f -o 
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          echo "$DIFF_RES"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
done


echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"