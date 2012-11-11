;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;					汇编语言大型课程设计：计算器
;										         开发者：刘畅
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		.486
		.model flat, stdcall
		option casemap :none
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; include 头文件
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
include		windows.inc
include		user32.inc
include		comdlg32.inc
include		kernel32.inc
include    D:\masm32\INCLUDE\masm32.inc

includelib	user32.lib
includelib	kernel32.lib
includelib	comdlg32.lib
includelib    D:\masm32\LIB\masm32.lib
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; Equ 等值定义
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
ICO_MAIN	                		equ		   1000
IDD_DIALOG1           		equ         101
IDD_DIALOG2           		equ         102
IDD_DIALOG3           		equ         103
IDR_MENU1             		equ         102
IDC_EDIT1                		equ         1000
IDC_EDIT2        		  		equ 		   1002
IDC_BACKSPACE 	  		equ 		   1003
IDC_CE                     		equ 		   1004
IDC_C                		   		equ 		   1005
IDC_MC                     		equ 		   1006
IDC_MR					   		equ 		   1007
IDC_MS					   		equ 		   1008
IDC_M                        	equ         1009          ; "M+"
IDC_7                        		equ         1010
IDC_8                        		equ		   1011
IDC_9         	                  equ          1012      
IDC_chu                    		equ          1013
IDC_sqrt                     	equ			1014
IDC_4  	                 			equ			1015
IDC_5  	                			equ			1016
IDC_6 	                 			equ			1017
IDC_cheng  						equ			1018
IDC_mod  						equ			1019
IDC_1  								equ			1020
IDC_2  								equ			1021
IDC_3  								equ			1022
IDC_jian 							equ			1023
IDC_daoshu  					equ			1024
IDC_0  								equ			1030
IDC_jiajian  						equ			1031
IDC_dian  						equ			1032
IDC_jia  							equ			1033
IDC_equ  							equ			1034
ID_MENUCOPY      			equ     		40001
ID_MENUPASTE      		equ    		40002
ID_MENUSTANDARD    	equ    		40003
ID_MENUSCIENCE       	equ    		40004
ID_MENUDEVIDE        	equ     		40005
ID_MENUHELP         		equ    		40006
ID_MENUABOUT       		equ  			40007

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; 数据段
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		.data?

hInstance 	dd	?
hWinMain	dd	?
hGlobal		dd	?
pGlobal		dd	?
pText			dd	?
hMenu			dd	?
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>数值常量部分>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 		.const
iNum0       db      '0',0
iNum1       db	    '1',0
iNum2		  db	    '2',0
iNum3		  db		'3',0
iNum4			db	'4',0
iNum5			db	'5',0
iNum6			db	'6',0
iNum7			db	'7',0
iNum8			db	'8',0
iNum9			db	'9',0
iPoint			db	'.',0
iNeg				db	'-',0                            ;变换正负号的时候用上。
iFlag				db	'M',0								;用于设置存储计算的时候用上
iNull				db	0
iCalfor			dq			100.0
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		.data
iDisplay				    db		'0',100 dup(?),0                 ;显示的字符串
iStore						  db		100 dup(?),0			 ;字符缓冲区，存放从标题栏得到的字符
iCopy						    db		20 dup(?)
ilength			        dd	  0						;用于存储字符串的长度
imov								db		'0'
iNumber1      			dq  	     0.0                      ;8个字节的浮点型数字,第一个运算数
iNumber2		  			dq		     0.0                      ;8个字节的浮点型数字,第二个运算数
iResult		  			    dq		 0.0                      ;8个字节的浮点型数字,运算结果
iMemory					dq			 0.0						;用于存储内存中的数据，即MS的使用需要

;----------------------------设置几个标志--------------------------------------------------------------
iImPoint		db		0            ;标志着之前是否输入过小数点，用以检测忽略多个输入小数点的错误
iEqual			db		0            ;检测之前是否输入过等号，用来检测连续等号运算的问题
iCal				db		0			   ;检测之前是否有运算符，同时记录的是运算符，用来检测连续运算符计算的问题
iAlready		db		0				;如果非0表示两个运算数收集完毕，可以运算了。
;------------------------------------------------------------------------------------------
;--------------------------设置提示信息-------------------------------------------------
szCaption 		    db		'除数不能为0，重新输入计算!',0
szCaption2			db		'0没有倒数！',0
szText				    db		'出错了',0
szText2				db		'Sorry',0
szScience				db		'暂未实现科学型',0
;------------------------------------------------------------------------------------------
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; 代码段
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		.code
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
_ProcHelp  	proc	uses ebx edi esi hWnd,wMsg,wParam,lParam

		mov	eax,wMsg
		.if	eax ==	WM_CLOSE
			       invoke	EndDialog,hWnd,NULL
		.else
			mov	eax,FALSE
			ret 
		.endif
		mov	eax,TRUE
		ret
_ProcHelp	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
_ProcAbout 	proc	uses ebx edi esi hWnd,wMsg,wParam,lParam
		mov	eax,wMsg
		.if	eax ==	WM_CLOSE
			       invoke	EndDialog,hWnd,NULL
		.else
			mov	eax,FALSE
			ret 
		.endif
		mov	eax,TRUE
		ret
_ProcAbout	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>			
;-------------------------------------------------------------------------------------------	
_ProcDlgMain	proc	uses ebx edi esi hWnd,wMsg,wParam,lParam

		mov	eax,wMsg
		.if	eax ==	WM_CLOSE
			       invoke	EndDialog,hWnd,NULL
		.elseif	eax ==	WM_INITDIALOG
			push	hWnd
			pop	hWinMain
			invoke	LoadIcon,hInstance,ICO_MAIN
			invoke	SendMessage,hWnd,WM_SETICON,ICON_BIG,eax
			invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iNum0
			invoke GetMenu,hWnd     ;初始化得到菜单句柄hMenu
			mov	hMenu,eax
			;下面的这句是将开始的时候设置成默认的为标准型计算器，即让菜单上的该项被选上。
			invoke	SendMessage,hWnd,WM_COMMAND,ID_MENUSTANDARD,NULL
			mov iDisplay[0],0 	
		.elseif	eax ==	WM_COMMAND
			mov	eax,wParam
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_0
			        .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum0
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum0
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif          
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_1
			      .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum1
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum1
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_2
			       .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum2
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum2
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_3
			       .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum3
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum3
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_4
			       .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum4
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum4
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_5
			         .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum5
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum5
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_6
			       .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum6
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum6
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_7
			       .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum7
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum7
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_8
			       .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum8
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum8
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_9
			         .if   iEqual ==0
			                invoke   lstrcat,addr iDisplay,addr iNum9
			                invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         .endif
			         .if  iEqual !=0
			         		  mov iDisplay[0],0
			         		  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         		  invoke   lstrcat,addr iDisplay,addr iNum9
			                 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			                 mov iEqual,0
			         .endif         
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_dian
			       			 invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			       			 invoke StrToFloat,addr iStore,addr iResult
			       			 finit
			       			 fld  iResult
			       			 ftst		;与0.0比较，如果为0则C3,C2,C1为1，0，0	
			       			 fstsw ax
			       			 and ax,4500h	
			       			 .if ax==4000h
			       					mov iDisplay[0],'0'
			       					invoke   lstrcat,addr iDisplay,addr iPoint
			        				invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay		
			       			 .else				
			       			 invoke   lstrcat,addr iDisplay,addr iPoint
			        		 invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			        		 .endif
			       		
			        
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_jia            
			               mov iCal , 1      ;设置运算符为加，标志位对应为1
			               ;从显示栏中读取20个字符，转化成对应的数据。
			       			invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			       			invoke StrToFloat,addr iStore,addr iNumber1
			       			;将iDisplay置空，便于下一个数的读入
			       			mov iDisplay[0],0
			       			
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_jian           
			                mov iCal ,2       ;设置运算符为加，标志位对应为2
			               ;从显示栏中读取20个字符，转化成对应的数据。
			       			invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			       			invoke StrToFloat,addr iStore,addr iNumber1
			       			mov iDisplay[0],0 
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_cheng            
			               mov iCal ,3       ;设置运算符为加，标志位对应为3
			               ;从显示栏中读取20个字符，转化成对应的数据。
			       			invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			       			invoke StrToFloat,addr iStore,addr iNumber1
			       			mov iDisplay[0],0
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_chu             
			               mov iCal , 4        ;设置运算符为加，标志位对应为4
			               ;从显示栏中读取20个字符，转化成对应的数据。
			       			invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			       			invoke StrToFloat,addr iStore,addr iNumber1	
;如果这里测试下，每次点击运算符后换种方式清零。这样每次除法的时候显示除数前面都会多一个0
			       			;mov iDisplay[0],'0'
			       			;mov iDisplay[1],0
			       			mov iDisplay[0],0
			       			
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_sqrt  ;直接将当前的计算结果马上显示出来
			     			invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			     			invoke StrToFloat,addr iStore,addr iResult
			     			finit
			     			fld iResult
			     			fsqrt
			     			fst iResult
			     			finit
			     			invoke FloatToStr,iResult,addr iDisplay
			     			invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			     			mov iEqual,2               ;取平方时将其置为非0
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_BACKSPACE
			      			invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			      			invoke lstrlen,addr iStore
			      			.if eax>1
			      			mov  iStore[eax-1],0
			      			mov  iDisplay[eax-1],0
			      			invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iStore
			      			.else
			      		   invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iNum0  ;显示清零
			      		   mov iDisplay[0],0			;将缓冲区的置空
			      		   .endif
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_CE
			      mov iDisplay[0],'0'
			      mov iDisplay[1],0
			      invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			      mov iDisplay[0],0
			      finit
			      fldz
			      fst iNumber2        ;将当前的数据清空
			      finit
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_C        ;所有的运算都清零，全部重新开始
			       mov iDisplay[0],'0'
			       mov iDisplay[1],0
			       invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			       mov iDisplay[0],0
			       finit
			       fldz  ;清零
			       fst iNumber1
			       fst iNumber2
			       finit
			       mov iEqual,0
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_mod
			      	;百分数的运算，其实就是单击这个按钮，使得显示的数字的百分之和前面的数字相乘
			      	invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			      	invoke StrToFloat,addr iStore,addr iResult
			      	finit
			      	fld iCalfor
			      	fld iNumber1
			      	fld iResult
			       fmul ST(0),ST(1)
			       fdiv	ST(0),ST(2)
			       fst iResult			;计算出某数的百分之某，得到的结果
			      	invoke FloatToStr,iResult,addr iDisplay
			      	invoke  SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_daoshu
			      	  invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			     	  invoke StrToFloat,addr iStore,addr iResult
			     	  finit
			       	  fld  iResult
			       	  ftst		     ;与0.0比较，如果为0则C3,C2,C1为1，0，0	
			       	  fstsw ax
			       	  and ax,4500h
			       	  finit	
			       	 .if ax==4000h
			       					invoke MessageBox,NULL,addr szCaption2,addr szText,MB_OK
			       	 .elseif		
			     	  finit 
			     	  fld iResult 
			     	  fld1
			     	  fdiv ST(0),ST(1)
			     	  fst iResult 
			     	  finit 
			     	  invoke FloatToStr,iResult,addr iDisplay 
			     	  invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			         mov iEqual,3               ;取倒数时将其置为非0
			         .endif
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_jiajian
			           invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			     	    invoke StrToFloat,addr iStore,addr iResult
			     	    finit
			     	    fld iResult
			     	    ftst		;比较和0的大小
			     	    fstsw ax
			     	    and ax,4500h
			     	    finit
			     	    .if ax==0   					;iResult>0,也就是显示的数字是一个正数
			     	    		mov iDisplay[0],'-'
			     	    		mov iDisplay[1],0
			     	    		invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iNull
			     	    		invoke lstrcat ,addr iDisplay,addr iStore
			     	    		invoke   SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			     	    .elseif  ax ==100h		;iResult<0,也就是显示的数字是一个负数
			     	    		mov iStore[0],'+' 
			     	    		invoke StrToFloat,addr iStore,addr iResult 	;将对应的正数转化成字符串即可
			     	    		invoke FloatToStr,iResult,addr iDisplay 
			     	    		invoke  SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			     	    .endif		
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_equ
							.if iEqual == 1    ;处理连续的等号运算,就是将当前的结果置为第一个数
								invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			       				invoke StrToFloat,addr iStore,addr iNumber1
							.else
								mov iEqual,1
			               	;得到第二个运算数
			               	invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			       				invoke StrToFloat,addr iStore,addr iNumber2
			       			.endif		
			       				.if   iCal ==1
			       					finit
			       					fld	iNumber2		;第二个数为ST(1)
			       					fld	iNumber1    ;第一个数为ST(0)
			       					fadd  ST(0),ST(1)    
			       					fst	iResult      ;ST(0)即为结果存放到iResult中
			       					finit
			       					invoke FloatToStr,iResult,addr iDisplay
			       					invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			       				.endif		
			       				.if   iCal ==2
			       					finit
			       					fld	iNumber2		;第二个数为ST(1)
			       					fld	iNumber1    ;第一个数为ST(0)
			       					fsub  ST(0),ST(1)
			       					fst	iResult      ;ST(0)即为结果存放到iResult中
			       					finit
			       					invoke FloatToStr,iResult,addr iDisplay
			       					invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			       				.endif			
			       				.if   iCal ==3
			       					finit
			       					fld	iNumber2		;第二个数为ST(1)
			       					fld	iNumber1    ;第一个数为ST(0)
			       					fmul  ST(0),ST(1)
			       					fst	iResult      ;ST(0)即为结果存放到iResult中
			       					finit
			       					invoke FloatToStr,iResult, addr iDisplay
			       					invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			       				.endif			
			       				.if   iCal == 4
			       					finit
			       					fld  iNumber2
			       					ftst		;与0.0比较，如果为0则C3,C2,C1为1，0，0	
			       					fstsw ax
			       					and ax,4500h	
			       					.if ax==4000h
			       							invoke MessageBox,NULL,addr szCaption,addr szText,MB_OK
			       					.elseif		
			       					finit
			       					fld	iNumber2		;第二个数为ST(1)
			       					fld	iNumber1    ;第一个数为ST(0)
			       					fdiv  ST(0),ST(1)
			       					fst	iResult      ;ST(0)即为结果存放到iResult中
			       					finit
			       					invoke FloatToStr,iResult, addr iDisplay
			       					invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay
			       					.endif
			       				.endif		             
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_MC
			         finit
			         fldz
			         fst iMemory
			         mov iDisplay[0],0
			         finit
			         invoke SetDlgItemText,hWnd,IDC_EDIT2,addr iDisplay  
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_MR
			              invoke FloatToStr,iMemory,addr iDisplay
			       		   invoke SetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay 
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_MS
			          invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			     	  invoke StrToFloat,addr iStore,addr iMemory
			     	  invoke SetDlgItemText,hWnd,IDC_EDIT2,addr iFlag  
			.endif
;-------------------------------------------------------------------------------------------				
			.if	ax ==	IDC_M
			          ;针对M+的操作，如果先前存储了，就累加并存入，否则将当前数存储下来
			          invoke GetDlgItemText,hWnd,IDC_EDIT2,addr iStore,20+1
			          .if  iStore[0]!='M'        ;如果开始没有存储数据，这个就存储下显示的数据
			                 invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iDisplay,20+1
			                 invoke StrToFloat,addr iDisplay,addr iMemory
			                 invoke SetDlgItemText,hWnd,IDC_EDIT2,addr iFlag  
			          .else       
			                invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
			                invoke StrToFloat,addr iStore,addr iResult
			                finit
			          		 fld iResult
			          		 fld iMemory
			         		 fadd ST(0),ST(1)
			          		 fst  iMemory
			          .endif
			.endif
;--------------------------------------------------------------------------------------------
			.if ax ==ID_MENUCOPY
				invoke GetDlgItemText,hWnd,IDC_EDIT1,addr iStore,20+1
				invoke lstrlen,addr iStore
				add eax,1
				mov ecx,GHND
				or ecx,GMEM_SHARE
				invoke GlobalAlloc,ecx,eax
               mov hGlobal,eax
               invoke GlobalLock , hGlobal
               mov pGlobal,eax       ;如果成功的话，GlobalLock的返回值就是指针，所以下面的不需要
               invoke lstrcpy ,pGlobal,addr iStore 
               invoke GlobalUnlock ,hGlobal
               invoke OpenClipboard, hWnd 
               invoke EmptyClipboard 
               invoke SetClipboardData, CF_TEXT, hGlobal 
               invoke CloseClipboard 
			.endif 
;--------------------------------------------------------------------------------------------				
			.if ax==ID_MENUPASTE      		
			 		invoke OpenClipboard ,hWnd
            		invoke GetClipboardData,CF_TEXT
            		mov hGlobal,eax
            		.if hGlobal!=0
           				invoke GlobalLock ,hGlobal			;定位到剪贴板的数据
          			    mov pGlobal,eax
          			    .if pText!=NULL                ;如果非空则置空
          			    		mov pText[0],0 
          			    		mov pText[1],0
          			    .endif
          			    mov pText,offset iDisplay			;pText作为指针，所以取地址
                       invoke lstrcpy,pText,pGlobal
                       invoke SetDlgItemText,hWnd,IDC_EDIT1,pText
                 .endif
               invoke CloseClipboard 
            .endif   
;-------------------------------------------------------------------------------------------	
			.if ax==ID_MENUSTANDARD
					movzx eax,ax
					mov ebx,eax
					invoke GetMenuState,hMenu,ebx,MF_BYCOMMAND
					.if eax & MF_CHECKED
							mov eax,MF_UNCHECKED
					.else
							mov eax,MF_CHECKED
					.endif
					;下面的这个代码是实现将某个选上或者不选上，与其他的菜单项无关，前面是对勾！		
					;invoke	CheckMenuItem,hMenu,ebx,eax		;eax为选中状态，ebx为命令，即ID
					;下面的这个代码是将第一个设置成RadioItem,这样两个中就只能选择一个了，只能取一。
					invoke	CheckMenuRadioItem,hMenu,\					
					ID_MENUSTANDARD,ID_MENUSCIENCE,ID_MENUSTANDARD,MF_BYCOMMAND				
			.endif
;-------------------------------------------------------------------------------------------	
			.if ax==ID_MENUSCIENCE
					movzx eax,ax
					mov ebx,eax
					invoke GetMenuState,hMenu,ebx,MF_BYCOMMAND
					.if eax & MF_CHECKED
							mov eax,MF_UNCHECKED
					.else
							mov eax,MF_CHECKED
					.endif
					;下面的这个代码是实现将某个选上或者不选上，与其他的菜单项无关，前面是对勾！		
				    ;invoke	CheckMenuItem,hMenu,ebx,eax		;eax为选中状态，ebx为命令，即ID
					;下面的这个代码是将第二个也设置成RadioItem,这样两个中就只能选择一个了，只能取一。
					invoke	CheckMenuRadioItem,hMenu,\					
					ID_MENUSTANDARD,ID_MENUSCIENCE,ID_MENUSCIENCE,MF_BYCOMMAND				
			.endif
;-------------------------------------------------------------------------------------------			
			.if ax==ID_MENUDEVIDE
					movzx eax,ax
					mov ebx,eax
					invoke GetMenuState,hMenu,ebx,MF_BYCOMMAND
					.if eax & MF_CHECKED
							mov eax,MF_UNCHECKED
					.else
							mov eax,MF_CHECKED
					.endif
					invoke	CheckMenuItem,hMenu,ebx,eax
			.endif
;-------------------------------------------------------------------------------------------			
			.if ax==ID_MENUHELP
					invoke	DialogBoxParam,hInstance,IDD_DIALOG3,NULL,offset _ProcHelp,NULL
			.endif 
;-------------------------------------------------------------------------------------------			        		
  			.if ax==ID_MENUABOUT
  					invoke	DialogBoxParam,hInstance,IDD_DIALOG2,NULL,offset _ProcAbout,NULL
  			.endif
;-------------------------------------------------------------------------------------------				
		.else
			mov	eax,FALSE
			ret 
		.endif
		mov	eax,TRUE
		ret

_ProcDlgMain	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
		invoke	GetModuleHandle,NULL
		mov	hInstance,eax
		invoke	DialogBoxParam,hInstance,IDD_DIALOG1,NULL,offset _ProcDlgMain,NULL
		invoke	ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		end	start