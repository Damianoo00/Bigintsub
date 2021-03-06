#!/bin/bash
make_test(){
if [ $($1) == $2 ]
then
    echo "Succes"
else
    echo "Error"
    echo "(Return $($1) insted of $2)"
fi
}

echo "Test 1 ([+] - [+] 32):"
echo $(make_test "./bigintsub 12345678901234567890123456789012 21098765432109876543210987654321" "-8753086530875308653087530865309")
echo "Test 2: ([+] - [<+] 32)"
echo $(make_test "./bigintsub 10000000000000000000000000000000 1" "9999999999999999999999999999999")
echo "Test 3: ([+] - [>+] 32)"
echo $(make_test "./bigintsub 1 10000000000000000000000000000000" "-9999999999999999999999999999999")
echo "Test 4 ([] - [] = 0):"
echo $(make_test "./bigintsub 1 1" "0")
echo "Test 5:([0] - [+]"
echo $(make_test "./bigintsub 0 3" "-3") 
echo "Test 6:([0] - [-]"
echo $(make_test "./bigintsub 0 -6" "6") 
echo "Test 7: ([-] - [>+])"
echo $(make_test "./bigintsub -1 10" "-11")
echo "Test 8: ([-] - [<+])"
echo $(make_test "./bigintsub -3 2" "-5") 
echo "Test 9: ([-] - [<-])"
echo $(make_test "./bigintsub -1 -10" "9")
echo "Test 10: ([-] - [>-])"
echo $(make_test "./bigintsub -10 -7" "-3")
echo "Test 11: ([0] - [0])"
echo $(make_test "./bigintsub 0 0" "0")

