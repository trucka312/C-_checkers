# CỜ CARO

1. ***Vẽ bàn cờ***

Bàn cờ thực tế mà người chơi tương tác có kích thước 20 x 20. Tuy nhiên, việc biểu diễn bàn cờ trên màn hình console có chút khác biệt. Vì chúng ta vừa phải in phần không gian trống cho mỗi ô, cùng với phần viền của ô, nên 1 ô vuông 1x1 thực tế lại có kích thước trên màn hình là 5 x 3 (chiều rộng: 2 thanh đứng | và 3 khoảng trắng; chiều cao: 2 thanh ngang ── và 1 khoảng trắng). Có thể các bạn sẽ đặt câu hỏi, tại sao chiều rộng có 3 khoảng trắng, còn chiều cao chỉ có 1 khoảng trắng. Câu trả lời là do mỗi kí tự in trên mang hình console có chiều cao lớn hơn chiều rộng.

```c
void veBanCo(){
	int i,j;
	gotoXY(LEFT+1,TOP);					//TOP
	for (i=0;i<(2*SIZE);i++)
		if (i%2)	printf("%c",194);	else	printf("%c%c%c",196,196,196);
	gotoXY(LEFT+1,BOT);					//BOT
	for (i=0;i<2*SIZE;i++)
		if (i%2)	printf("%c",193);	else	printf("%c%c%c",196,196,196);
	for (i=0;i<2*SIZE;i++){
		gotoXY(LEFT,TOP+i);	
		if (i%2)	printf("%c",179);	else	printf("%c",195);
		gotoXY(RIGHT,TOP+i);
		if (i%2)	printf("%c",179);	else	printf("%c",180);
	}
	char S0[200], S1[200];
	for (int j=0;j<4*SIZE-1;j++)
		if (j%4==0)		S0[j]=179;		else S0[j]=' ';
	for (int j=0;j<4*SIZE-1;j++)
		if ((j+1)%4==0)	S1[j]=197;		else S1[j]=196;
	S1[4*SIZE-1]='\0';	S0[4*SIZE-1]='\0';
	i=1;
	while (i<2*SIZE-1){
		gotoXY(LEFT,TOP+i++);	printf("%s",S0);
		gotoXY(LEFT+1,TOP+i++);	printf("%s",S1);
	}
	gotoXY(LEFT,TOP+i);	printf("%s",S0);
	gotoXY(LEFT,TOP);	printf("%c",218);
	gotoXY(RIGHT,TOP);	printf("%c",191);
	gotoXY(LEFT,BOT);	printf("%c",192);
	gotoXY(RIGHT,BOT);	printf("%c",217);
}
```

