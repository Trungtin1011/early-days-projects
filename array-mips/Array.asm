	.data

A: .word 0:1000 # int A[1000]
Menutop: 	.asciiz "\n=================================================="
Select1: 		.asciiz "\n1. Xuat cac phan tu mang."
Select2: 		.asciiz "\n2. Tinh tong cac phan tu mang."
Select3: 		.asciiz "\n3. Liet ke cac phan tu la so nguyen to."
Select4: 		.asciiz "\n4. Tim max."
Select5: 		.asciiz "\n5. Tim phan tu co gia tri x"
Select6: 		.asciiz "\n6. Thoat!"
Menubot:	.asciiz "\n=================================================="

NhapPT: 		.asciiz "Nhap n: "			# Thong bao nhap so phan tu mang
openNGOACVUONG: .asciiz "["
closeNGOACVUONG: .asciiz "] = "
Select:     	.asciiz "\nNhap lua chon: "	# Thong bao nhap lua chon trong menu

Xuat: 		.asciiz"\nCac phan tu trong mang: "
Tong:      	.asciiz "\nTong cac phan tu: "
PrintSNT: 	.asciiz "\nPhan tu la so nguyen to trong mang: "
PrintMAX:	.asciiz "\nPhan tu lon nhat: "
inpX: 		.asciiz "\nNhap gia tri can tim: "
foundX:		.asciiz "\nDa tim thay "
notX:		.asciiz "\nGia tri can tim khong ton tai trong mang!!!"
KhoangTrang: .asciiz " "

	.text
	.globl main

main:
	jal inpN			#Nhap so phan tu n
	move $s0, $t0		# $s0 = n
	move $s1, $s0		# $s1 = $s0 (Tinh toan dung cai nay)
	move $t0, $s0		

	li $t8, 0
	la $a1, A			#Khai bao mang luu trong thanh ghi $a1

	jal NhapMang		#Nhap mang
	jal MENU			#Chay menu

################################## Nhap so phan tu n
inpN:		
	li $v0, 4
	la $a0, NhapPT		# Xuat ra man hinh thong bao nhap so
	syscall

	li $v0, 5				# Nhap so phan tu n
	syscall

	blez $v0, inpN			# if n <= 0, goto inpN
	addi $t0, $v0, 0  		# $t0 = n
	jr $ra

################################# Nhap mang
NhapMang:
	beqz $s1, KetThucNhap # Sau moi lan lap thi $s1--, khi $s1=0 thi ket thuc 

	li $v0, 4				# xuat dau ngoac vuong
	la $a0, openNGOACVUONG  		# [...
	syscall
	
	addi $a0, $t8, 0
	li $v0, 1   
	syscall

	li $v0, 4
	la $a0, closeNGOACVUONG		# ...]
	syscall    				# =>>> [...]

	li $v0, 5				# Nhap so nguyen va luu vao A[i]
	syscall
	sw $v0, ($a1)  

	addi $t8, $t8, 1
	subi $s1, $s1, 1  		# $s1--
	addi $a1, $a1, 4		# A[i+1]
	b NhapMang			# Tiep tuc vong lap
KetThucNhap:
	la $a1, A				# Cap nhat lai dia chi mang
	move $s1, $s0
	jr $ra

################################# Xuat mang
XuatMang:				# choice number one
	li $v0, 4
	la $a0, Xuat
	syscall
	j XuLiXuat

XuLiXuat:
	beqz $s1, KetThucXuat	# Sau moi lan xuat thi $s1--, khi $s1=0 thi ket thuc
	
	lw $t6, ($a1)			# Xuat phan tu A[i]
	li $v0, 1
	move $a0, $t6 
	syscall

	li $v0, 4
	la $a0, KhoangTrang	# Phan cach giua cac phan tu		
	syscall

	subi $s1, $s1, 1		# $s1--
	addi $a1, $a1, 4
	j XuLiXuat			# Tiep tuc vong lap
KetThucXuat:
	la $a1, A				# Cap nhat lai dia chi mang
	move $s1, $s0
	j MENU

################################# Tinh tong cac phan tu trong mang
TinhTong:
	beqz $s1, XuatTong	# Moi lan tinh thi $s1-- cho den khi =0

	lw $t6, ($a1)			# Lay gia tri trong mang cong don vao $t1
	add $t1, $t1, $t6 

	subi $s1, $s1, 1		# $s1--
	addi $a1, $a1, 4
	j TinhTong
XuatTong:
	li $v0, 4
	la $a0, Tong			# Thong bao xuat tong - Choice number two
	syscall

	li $v0, 1
	move $a0, $t1			# Xuat tong
	syscall

	la $a1, A
	move $s1, $s0
	j MENU

################################# Liet ke cac so nguyen to trong mang
XuatSNT:				# Choice number three
	li $v0, 4
	la $a0, PrintSNT
	syscall 
	j XuLiSNT

XuLiSNT:
	beqz $s1, KetThucXuLi	# Sau moi lan lap thi $s1--, khi $s1=0 thi ket thuc
	lw $t6, ($a1)
	move $t1, $t6			# Luu gia tri vua lay ra tu mang vao $t1
	addi $t2, $zero, 2		# $t2 = 2
	addi $t3, $zero, 3		# Cho i bat dau tu 3
 
	subi $s1, $s1, 1		# $s1--
	addi $a1, $a1, 4

			# Kiem tra so nguyen to
	beq $t1, 2, TRUE	# Neu $t1 == 2 => SNT
	beq $t1, 3, TRUE	# Neu $t1 == 3 => SNT
	blt $t1, 2,  FALSE	# Neu $t1 < 2 => Khong phai SNT
		
	div $t1, $t2
	mfhi $t4
	beqz $t4, FALSE 	# Neu $t1 la so chan => Khong phai SNT		

	Check:      # for ($t3 =3, $t3 < $t1, $t3 += 2)
		beq $t3,  $t1, TRUE	
		div $t1, $t3		
		mfhi $t5			#  $t5 = $t1 mod $t3
		beqz $t5, FALSE	# $t5 == 0 => khong phai SNT
		addi $t3, $t3, 2 	# $t3 += 2
		j Check			#Tiep tuc kiem tra
	TRUE: 				# NEU LA SNT
		li $v0, 1
		move $a0, $t1		# XUAT RA
		syscall 

		li $v0, 4
		la $a0, KhoangTrang # Xuat khoang trong
		syscall

		j XuLiSNT		# Quay lai vong lap
	FALSE:				# SAI THI KHONG IN RA
		j XuLiSNT
KetThucXuLi:
	la $a1, A				# Cap nhat
	move $s1, $s0
	j MENU

################################# Tim so lon nhat trong mang
MAX:
	beqz $s1,XuatMax		# Sau moi lan lap thi $s1--, khi $s1=0 thi xuat
	lw $t6, ($a1)
	bgt $t6, $t1, Swap		# Phan tu dau tien ma > max = 0 thi swap chung
	subi $s1, $s1, 1		# $s1--
	addi $a1, $a1, 4
	j MAX				# TIep tuc lap
Swap:
	move $t1, $t6			#SWAP
	j MAX
XuatMax:
	li $v0,4
	la $a0, PrintMAX			# Thong bao xuat so lon nhat - Choice number four
	syscall

	li $v0, 1
	move $a0, $t1 			# XUAT
	syscall

	la $a1, A
	move $s1, $s0			# Cap nhat
	j MENU

################################# Tim so co gia tri X trong mang
FindX:
	li $v0,4
	la $a0, inpX			# Thong bao nhap gia tri can tim
	syscall

	li $v0, 5
	syscall 
	move $t1, $v0 			# $t1 = x
	
	Loop:
		beqz $s1, NOTFOUND	# Sau moi lan lap thi $s1--, khi $s1=0 (Het mang) ma van chua tim ra thi ket thuc
		lw $t6, ($a1)
		move $t2, $t6			# Luu gia tri vua lay ra tu mang vao $t2
 
		subi $s1, $s1, 1		# $s1--
		addi $a1, $a1, 4

		beq $t1, $t2, FOUND	# if $t2 = x
		j Loop
	FOUND:					# Neu tim thay phan tu co gia tri x roi
		li $v0, 4
		la $a0, foundX			# Xuat thong bao
		syscall

		li $v0, 1
		move $a0, $t2			# Xuat phan tu
		syscall		

		la $a1, A			# Cap nhat
		move $s1, $s0
		j MENU
	NOTFOUND:				# Neu khong tim thay
		li $v0, 4
		la $a0, notX			# Xuat thong bao
		syscall

		la $a1, A			# Cap nhat
		move $s1, $s0
		j MENU

MENU:
	li $v0, 4 				# TOP
	la $a0, Menutop
	syscall

	li $v0, 4 				# XUAT CAC PHAN TU MANG
	la $a0, Select1
	syscall

	li $v0, 4 				# TONG CAC PHAN TU MANG
	la $a0, Select2
	syscall

	li $v0, 4				# LIET KE CAC PHAN TU SO NGUYEN TO
	la $a0, Select3
	syscall

	li $v0, 4 				# TIM MAX
	la $a0, Select4
	syscall

	li $v0, 4 				# TIM VI TRI CUA X
	la $a0, Select5
	syscall

	li $v0, 4 				# THOAT
	la $a0, Select6
	syscall

	li $v0, 4 				# BOT
	la $a0, Menubot
	syscall	

	li $v0, 4 				# NHAP LUA CHON
	la $a0, Select
	syscall

	li $v0, 5 				# SCAN LUA CHON
	syscall
	move $t7, $v0

	blez $t7, MENU 		# if choice <=0, go to MENU
	bgt $t7, 6, MENU 		# if choice >6, goto MENU
	
	addi $t1, $zero, 0  		# Khoi tao lai cac thanh ghi can thiet
	la $a1, A


	beq $t7, 1, XuatMang
	beq $t7, 2, TinhTong
	beq $t7, 3, XuatSNT
	beq $t7, 4, MAX
	beq $t7, 5, FindX
	beq $t7, 6, Exit

Exit:
	li $v0, 10
	syscall



