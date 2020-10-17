.name "zork"
.comment "just a basic living prog"
l2:		sti r1, %:live, %1
		sti r2, %:l2, %0
		and r1, %0,r1
live:
		live %0
		zjmp %:live
