	.data

fileName: 	.asciiz "C:/Users/trung/Desktop/input.txt"
fileOut: 		.asciiz "C:/Users/trung/Desktop/output.txt"
fileWords: 	.space 1024
Size:		.space 4
A:			.word 0:1000		
Newline: 		.asciiz "\n"
Space: 		.asciiz " "
	.text
	.globl main
	
main:
	move $t7,$0
	jal READ
	jal SaveArray
	
	
	addi $s1,$0,0			#left=0
	subi $s2,$s7,2			#right=size-2
	subi $s3,$s7,1			#pos=size -1
	
	
	subi $sp,$sp,4
	sw $ra,0($sp)
	jal QuickSort
	lw $ra,0($sp)
 	addi $sp,$sp,4
 	
 	move $t7,$0
	move $t4,$0
	
	#open file
	li $v0,13
	la $a0,fileOut
	li $a1,1
	syscall
	move $s1,$v0
	
PRINT_A:		
    	bge $t7, $s7, PRINT_END 	#Dung in 
    	
    	lw $t9,A($t4)				#t9 gia tri mang
    	addi $t5,$0,1				#t5=1
    	move $t6,$0				#t6=0
    	
    	subi $sp,$sp,4
    	sw   $ra,0($sp)
    	jal COUNT
    	lw $ra,0($sp)
    	addi $sp,$sp,4
    	
    	lw $t9,A($t4)				#dat lai t9 sau khi dem
    	
######################

	move $t8,$t5
	
    	ItoA:
	beqz $t6,LAST				#Neu con 1 ki tu thi nhay den LAST
	
    	div $t9,$t8
    	mflo $t9
    	subi $sp,$sp,4
    	sw $ra,0($sp)
    	jal WRITE_CHARACTER	#Write tung ki tu vao ouput
    	lw $ra,0($sp)
    	addi $sp,$sp,4
    	mfhi $t9
    	div $t8,$t8,10
    	subi $t6,$t6,1
    	j ItoA
    	
    	  	
    	
    	LAST:					#In ki tu cuoi + space
    	addi $t9,$t9,48
    	sw $t9,A($t4)
    	li $v0,15					# write_file syscall code = 15
    	move $a0,$s1				# file descriptor
    	la $a1,A($t4)				# the string that will be written
    	li $a2, 1					# length of the toWrite string
    	syscall
    	
     	
    	li $v0, 15
    	la $a1,Space				#Space
    	li $a2,1
    	syscall
    	
    	addi $t7, $t7, 1  			# Dem phan tu
	addi $t4, $t4, 4  			# nhay toi phan tu mang tiep theo
	
	j PRINT_A 				# lap lai vong lap
    	
	
PRINT_END:
	li $v0,16
	syscall
	li $v0, 10
	syscall


	COUNT:					#Dem so ki tu cua t9
		addi $t8,$0,10
		div $t9,$t8
		mflo $t8
		beqz $t8,END_COUNT
		addi $t6,$t6,1
		mulo $t5,$t5,10
		move $t9,$t8
	j COUNT

	END_COUNT:
	jr $ra
	
WRITE_CHARACTER:
	addi $t9,$t9,48
    	sw $t9,A($t4)
    	li $v0,15					# write_file syscall code = 15
    	move $a0,$s1				# file descriptor
    	la $a1,A($t4)				# the string that will be written
    	li $a2, 1					# length of the toWrite string
    	syscall
    	jr $ra
	
	
READ:	
	li $v0,13           			# open_file syscall code = 13
    	la $a0,fileName     			# get the file name
    	li $a1,0           				# file flag = read (0)
    	syscall
    	move $s0,$v0        			# save the file descriptor. $s0 = file
	
	#read the file
	li $v0, 14					# read_file syscall code = 14
	move $a0,$s0				# file descriptor
	la $a1,fileWords  			# The buffer that holds the string of the WHOLE file
	la $a2,1024				# hardcoded buffer length
	syscall
	
	# print whats in the file
	#li $v0, 4		# read_string syscall code = 4
	#la $a0,fileWords
	#syscall

	#Close the file
    	li $v0, 16         				# close_file syscall code
    	move $a0,$s0      			# file descriptor to close
    	syscall
jr $ra
#########################################################################################     	
	# read and Stored to the array
	SaveArray:
		addu $sp, $sp, -4
		la $t0, fileWords
		#la $s0, array
		addi $s1,$0, 0
		sw $ra, 0($sp)
		jal StoredtoArray
		lw $ra, ($sp)
		addu $sp, $sp, 4
		jr $ra

	StoredtoArray:
		lb $t6, ($t0)
		move $s2, $t6
		beq $s2, 0, nStoredtoArray
		beq $s2, 13, StoredNumberofElements 
		addi $s2, $s2, -48
		bltz $s2, Stored 
		addi $s3, $0, 10
		mult $s1, $s3
		mflo $s1
		add $s1, $s1, $s2
		addi $t0, $t0, 1
		j StoredtoArray

		Stored:
			addi $t0, $t0, 1
			sw  $s1,A($t7)
			addi $t7,$t7,4
			move $s1, $0
			
			j StoredtoArray

		StoredNumberofElements:
			addi $t0, $t0, 2
			move $s7, $s1
			move $s1, $0
			
			j StoredtoArray
		
	nStoredtoArray:	
		sw $s1,A($t7)
		jr $ra	

				
QuickSort:

	QuickSortLEFT:			

		subi $sp,$sp,4
		sw   $ra,0($sp)
		jal partition			#Chay ham partition
		lw   $ra,0($sp)
		addi $sp,$sp,4

		#Neu gia tri tra ve =left, hoac =left +1 thi xong QSleft
		move $s4,$v0 			#s4=return
		subi $s4,$s4,1
		sub $s4,$s4,$s1		#s4=return-left-1
		blez $s4,QuickSortRIGHT	#Neu QSleft done->QSright


		subi $s3,$v0,1			#new pos=return-1
		mulo $t0,$s3,4
		lw   $t3,A($t0)			#new A[pos]

		subi $s2,$s3,1			#new right=pos-1
		mulo $t0,$s2,4
		lw   $t2,A($t0)			#new A[right]

		addi $s1,$s1,0			#left ban dau
		mulo $t0,$s1,4
		lw   $t1,A($t0)			#A[left]
		j QuickSortLEFT

	QuickSortRIGHT: 
		addi $s1,$v0,1			#new left=return+1
		mulo $t0,$s1,4
		lw $t1,A($t0)

		subi $s2,$s7,2
		mulo $t0,$s2,4
		lw   $t2,A($t0)			#right

		addi $s3,$s2,1
		mulo $t0,$s3,4
		lw $t3,A($t0)			#pos

		blt $s1,$s3,TRUE		#left<pos, nhay den nhan TRUE

		jr $ra				#Ket thuc QuickSort

	TRUE:
		subi $sp,$sp,4
		sw   $ra,0($sp)
		jal partition
		lw   $ra,0($sp)
		addi $sp,$sp,4

	j QuickSort


partition:
	addi $s1,$s1,0				#s1=left
	addi $t8,$s1,0				#t8-> luu left ban dau

	mulo  $t0,$s1,4		
	lw   $t1,A($t0)				#t1=A[left]

	subi $s2,$s2,0				#s2=right
	addi $t9,$s2,0				#t9->luu right ban dau

	mulo $t0,$s2,4
	lw   $t2,A($t0)				#t2=A[right]

	addi $s3,$s3,0				#s3=pos

	mulo $t0,$s3,4
	lw $t3,A($t0)				#t3=A[pos]

	LoopTRUE:
	Loop1:

		bge $s1,$s3,Done2Loop	#left>=pos, ket thuc 2 vong lap
		ble $s1,$s2,TRUE1		#left<=right, nhay den nhan TRUE1
				
	Loop2:

		bgt  $s2,$s1,TRUE2	#right>left, nhay den nhan TRUE2
				
	Done2Loop:
		bge $s1,$s2,ExitLoopTRUE	#left>=right, break khoi LoopTRUE

		subi $sp,$sp,12
		sw   $ra,8($sp)
		sw   $s5,4($sp) 
		sw   $s6,0($sp)
		jal SwapLR			#Sap A[left], A[right]
		lw   $s6,0($sp)
		lw   $s5,4($sp)
		lw $ra,8($sp)
		addi $sp,$sp,12

		addi $s1,$s1,1			#left++
		mulo $t0,$s1,4		
		lw $t1,A($t0)			#new A[left]

		subi $s2,$s2,1			#right--
		mulo $t0,$s2,4
		lw $t2,A($t0)			#new A[right]
	j LoopTRUE


	TRUE1:
		blt $t1,$t3,LEFT		#A[left]<A[pos], Nhay den nhan LEFT
	j Loop2					#Else tiep tuc chay Loop2

	TRUE2:
		bgt $t2,$t3,RIGHT		#A[right]>A[pos], Nhay den nhan RIGHT
	j Done2Loop				#Else, ket thuc 2 vong lap

	LEFT:
		addi $s1,$s1,1			#left++
		mulo $t0,$s1,4		
		lw $t1,A($t0)			#new A[left]
	j Loop1					#Lap lai Loop1

	RIGHT:
		subi $s2,$s2,1			#right--
		mulo $t0,$s2,4
		lw $t2,A($t0)			#new A[right]
	j Loop2

SwapLR:						#swap A[left], A[right]
	mulo $t5,$s1,4
	lw  $s5,A($t5)				#Load A[left] vao s5

	mulo $t6,$s2,4
	lw  $s6,A($t6)				#Load A[right] vao s6

	sw $s5,A($t6)
	sw $s6,A($t5)
	jr $ra


ExitLoopTRUE:				#-> swap A[left], A[pos], Return Left

	mulo $t5,$s1,4
	lw  $s5,A($t5)				#Load A[left] vao s5

	mulo $t6,$s3,4
	lw  $s6,A($t6)				#Load A[pos] vao s6

	sw $s5,A($t6)
	sw $s6,A($t5)


	addi $v0,$s1,0				#return v0=left

	addi $s1,$t8,0				#Dat lai left
	addi $s2,$t9,0				#Dat lai right


jr $ra


