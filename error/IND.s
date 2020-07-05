.name "Jumper !"
.comment "en fait C forker !"

live:	st r6,:gogo
gogo:	st r6,19999999999999999999999999
	st r6,-1
	st r6,127
	st r6,-128
	st r6,32767
	st r6,32768
	st r6,-32768
	st r6,-32769
	st r6,2147483647
	st r6,2147483648
	st r6,2147483649
	st r6,-2147483647
	st r6,-2147483648
	st r6,-2147483649
	and r1, %0, r1
	and r1, %1, r1
	and r1, %-1, r1
	and r6,%127,r1
	and r6,%-128,r1
	and r6,%32767,r1
	and r6,%32768,r1
	and r6,%-32768,r1
	and r6,%-32769,r1
	and r6,%2147483648,r1
	and r6,%-2147483649,r1
