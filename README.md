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
<br>BT2 : Cấu hình tần số hoạt động của Timer 1 là 1 KHz với tần số dao động của hệ thống là 16 MHz sẽ tạo ra sự kiện ngắt. Thiết kế 1 bộ Downcounter Timer để cho đèn LED PA5 nháy 1s,2s
<br>BT3 : Cấu hình tần số hoạt động của Timer 1 là 1 KHz với tần số dao động của hệ thống là 16 MHz sẽ tạo ra sự kiện ngắt. Thiết kế 1 bộ Timer để cho đèn LED PA5,PB6,PC7 nháy Lần lượt 1s,2s,4s
<br>
<br>PWM
<br>Bài tập: Tạo tín hiệu PWM trên chân PA5 (nối với led xanh) của STM32F401RE để bật và tắt led dần dần.
Sử dụng TIM2 để tạo tín hiệu PWM trên PA5.
Sử dụng TIM3 để tạo hàm delay void delay_ms(int ms) để tạo độ trễ ngắn giữa các mức tín hiệu PWM khác nhau (tương ứng với các chu kỳ nhiệm vụ khác nhau) để thấy rõ hơn hiệu ứng LED bật và tắt dần dần.
<br>
<br>UART
<br>Bài 1: In chữ “Hello Stm32” ra màn hình phần mềm PUTTY sử dụng Kênh UART2 PA2, PA3 làm TX,RX 
<br>Bài 2: Đọc giá trị của cảm biến IR sensor gửi giá trị lên màn hình PUTTY (Sử dụng UART2 PA2,PA3, chân cảm biến sử dụng PC1)
<br>Bài 3: Đọc giá trị của biến trở gửi giá trị lên màn hình PUTTY(Sử dụng UART2 PA2,PA3, chân cảm biến sử dụng PC1)
<br>
<br>I2C:Sử dụng giao tiếp I2C hiển thị dòng chữ bất ký lên màn hình oled SSD1306
<br>ADC:Thực hành thay đổi giá trị sáng của đèn led bằng việc sử dụng biến trở và hiển thị giá trị đọc được từ chân của biến trở và hiển thị lên màn hình oled.

