# Nhập môn hệ thống nhúng
Nhập môn hệ thống nhúng
<br>GPIO
<br>Exercise 1: Write a program to blink green led on NUCLEO-F401RE board (using register)
<br>Exercise 2: Write a program to turn on green led on NUCLEO-F401RE board when pressing user button and vice versa (using register)
<br>Exercise 3 : Write a program to turn on a led when pressing a button and vice versa
<br>Exercise 4 : Write a program to turn on 3 led when pressing 3 button and vice versa 
<br>
<br>Interrupt
<br>Iterrupt 1:Write a program to toggle green led (on PA5) using user button (on PC13) on NUCLEO – F401RE board
<br>Exercise 1: Viết chương trình cấu hình ngắt ngoài cho nút nhấn trên Board STM32401RE Cho Led PC5(Đỏ) sáng nhấp nháy. Khi có ngắt xảy ra trên chân PC13 thì led trên chân PA5(Xanh) sẽ sáng trong một khoảng thời gian rồi chương trình trở lại trang thái ban đầu.
<br>Exercise 2: Yêu cầu 2: Viết chương trình cấu hình ngắt ngoài cho nút nhấn trên Board STM32401RE Cho Led PC5(Đỏ) sáng nhấp nháy. Khi có ngắt xảy ra trên chân PC6 thì khi có vật cản đến gần thì led trên chân PC8(Xanh) sẽ sáng đến  khi không còn vật cản. Sử dụng IR sensor.
<br>Yêu cầu 3: Viết chương trình cấu hình ngắt ngoài cho nút nhấn trên Board STM32401RE Cho Led PC5(Đỏ) sáng nhấp nháy.  Khi có ngắt xảy ra trên chân PC13 thì led trên chân PA5(Xanh) sẽ sáng trong một khoảng thời gian. Khi có ngắt xảy ra trên chân PA9 thì led trên chân PC8(Vàng) sẽ sáng trong một khoảng thời gian. Set cho PA9 chế độ ngắt ưu tiên cao nhất. TH1: Nhấn PC13 xong ấn PA9 TH2: Nhấn PA9 xong ấn PC13
<br>
<br>Timer
<br>Exercise 1: Cấu hình tần số hoạt động của Timer 1 là 1 KHz với tần số dao động của hệ thống là 16 MHz sẽ tạo ra sự kiện ngắt. Thiết kế 1 bộ Upcounter Timer để cho đèn LED PA5 nháy 1s,2s 
