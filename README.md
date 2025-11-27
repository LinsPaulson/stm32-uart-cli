## STM32 USART Communication Demo (RealTerm Serial Monitoring)

A minimal project demonstrating USART communication on the STM32F070RB (Nucleo-F070RB) using low-level register programming (bare-metal).
The project sends characters from the microcontroller to a PC, where the output is viewed using RealTerm, a lightweight serial terminal tool.

* Bare-metal register-level programming
* Understanding of USART peripheral configuration
* Use of an external serial terminal for debugging
* Working with the Nucleo board’s virtual COM port (USART2 → USB)

______________________________________________________________________________________________________________________________________________

🚀 Features

* Bare-metal (no HAL/LL drivers)
* Configures **USART2** for transmission at a chosen baud rate
* Continuously sends data over USB (virtual COM port)
* Compatible with **RealTerm**, PuTTY, CoolTerm, or any serial monitor
* Clean project structure for easy extension

______________________________________________________________________________________________________________________________________________

📁 Project Structure

├── src
│   ├── main.c            
│   └── usart.c/h         
├── inc
│   └── (header files)
├── README.md
└── .gitignore

______________________________________________________________________________________________________________________________________________

🔧 Hardware Used

* Nucleo-F070RB Board
* On-board ST-Link Virtual COM Port (USART2 ↔ USB)
* Micro-USB cable
* PC running Windows + RealTerm (or any serial terminal)

______________________________________________________________________________________________________________________________________________

🖥️ Serial Terminal Setup (RealTerm)

1. Install RealTerm from its official source.
2. Open RealTerm → **Port** tab
3. Select the COM port corresponding to the Nucleo board
4. Baud rate: **9600** (or the value configured in code)
5. Set Data Bits: 8, Parity: None, Stop Bits: 1
6. Click **Open** to start monitoring incoming data

______________________________________________________________________________________________________________________________________________

🛠️ Build & Flash

1. Import project into **STM32CubeIDE**
2. Build the project
3. Flash to board using the Run/Debug button
4. Open RealTerm and observe USART output

______________________________________________________________________________________________________________________________________________

📚 Learning Outcomes

* Understanding USART registers (BRR, CR1, ISR, TDR)
* Polling-based transmission
* Working with PC serial monitors
* Seeing how low-level register writes map to real hardware behavior

______________________________________________________________________________________________________________________________________________

📜 License

This project is released under the MIT License.

