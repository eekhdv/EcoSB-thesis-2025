/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoUART1Device
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoUART1Device
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoUART1Device.h"
//#include <avr/io.h>
//#include <avr/interrupt.h>

extern bool_t ECOCALLMETHOD IsEqualUGUIDB40E129B56624BD7B5F8339C025F3EF0(/* in */ const UGUID* rguid1, /* in */ const UGUID* rguid2);
#define IsEqualUGUID(rguid1, rguid2) IsEqualUGUIDB40E129B56624BD7B5F8339C025F3EF0(rguid1, rguid2)

#ifdef ECO_WIN32
#include "windows.h"
typedef struct CEcoUART1Win32Device {
    void* m_Device;

} CEcoUART1Win32Device, *CEcoUART1Win32DevicePtr;
#elif ECO_AVR8
#define SERIAL_IMPLEMENT_RX_INT 1
#define SERIAL_RX_RING_SIZE 30
#define SERIAL_TX_RING_SIZE 30

typedef struct _t_buffer {
    /// data storage space for the ring buffer
    volatile unsigned char ring[SERIAL_RX_RING_SIZE];

    /// head index
    volatile unsigned char head;

    /// tail index
    volatile unsigned char tail;

} t_buffer;


static volatile t_buffer g_rx_buff;
static volatile t_buffer g_tx_buff;

void __vector_18 (void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_18 (void) {

    //if (received == '0')
    //received++;
      //  (*(volatile uint8_t *)(0x25)) ^= 0B00000001;
    //else {
    //PORTB ^= (1 << 1);
    
    //}
    // no frame error
    // UCSR0A must be read before UDR0 !!!
    if (!((*(volatile uint8_t *)(0xC0)) & (1<<4))) {
    //if (bit_is_clear(UCSR0A, FE0)) {
        /// must read the data in order to clear the interrupt flag
        volatile unsigned char data = (*(volatile uint8_t *)(0xC6));

        /// calculate the next available ring buffer data bucket index
        volatile unsigned char next =
        ((g_rx_buff.head + 1) % SERIAL_RX_RING_SIZE);

        /// do not overflow the buffer
        if (next != g_rx_buff.tail) {
            g_rx_buff.ring[g_rx_buff.head] = data;
            g_rx_buff.head = next;
        }
    }
    else {
        /// must read the data in order to clear the interrupt flag
        volatile unsigned char data __attribute__((unused)) = (*(volatile uint8_t *)(0xC6));
    }
}

unsigned char serial_getc(unsigned char *a_data) {
    
    if (g_rx_buff.head == g_rx_buff.tail)
    return 1;

    *a_data = g_rx_buff.ring[g_rx_buff.tail];
    g_rx_buff.tail = (g_rx_buff.tail + 1) % SERIAL_RX_RING_SIZE;
    return 0;
}

void __vector_19 (void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_19 (void) {
    
    // proceed if there still is data to be send
    if (g_tx_buff.head != g_tx_buff.tail) {
        
        (*(volatile uint8_t *)(0xC6)) = g_tx_buff.ring[g_tx_buff.tail];
        //UDR0 = g_tx_buff.ring[g_tx_buff.tail];
        g_tx_buff.tail = (g_tx_buff.tail + 1) % SERIAL_TX_RING_SIZE;
    }
    else {
        // mask the interrupt everything has been send
         (*(volatile uint8_t *)(0xC1)) &= ~(1 << (5));
    }
}


unsigned char serial_sendc(unsigned char a_data) {

    uint8_t n = 0x00;
    uint8_t next =
    ((g_tx_buff.head + 1) % SERIAL_TX_RING_SIZE);

    /// do not overflow the buffer
    if (next != g_tx_buff.tail) {
        g_tx_buff.ring[g_tx_buff.head] = a_data;
        g_tx_buff.head = next;
        n = 1;

        // enable data register empty interrupt
         (*(volatile uint8_t *)(0xC1)) |= ~(1 << (5));
         //        UCSR0B |= _BV(UDRIE0);
    }

    return n;
}
byte_t startBeep2[10] = { 0x06, 0x00, 0x00, 0x00, 0x80, 0x03, 0x0B, 0x02, 0xF4, 0x01 };
byte_t startBeep[17] = { 0x0f, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x94, 0x01, 0x81, 0x01, 0x82, 0x0b, 0x02, 0x82, 0xf4, 0x01};

#elif ECO_LINUX
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#endif

CEcoUART1Device_025F3EF0 g_xB40E129B56624BD7B5F8339C025F3EF0UART1Device[3] = {0};


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoUART1Device
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_QueryInterface(/* in */ struct IEcoUART1Device* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoUART1Device) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#ifdef ECO_WIN32
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1WIN32Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_AVR8
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1AVR8Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_BCM283X
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_RISCV64
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCCU1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblICCUConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_LINUX

#elif ECO_STM32
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1STM32F4Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#endif

    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoUART1Device
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_AddRef(/* in */ struct IEcoUART1Device* me) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoUART1Device
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Release(/* in */ struct IEcoUART1Device* me) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoUART1Device_025F3EF0((IEcoUART1Device*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Connect
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Connect(/* in */ struct IEcoUART1Device* me, /* in */ ECO_UART_1_CONFIG* config) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)me;
#ifdef ECO_WIN32
    COMMCONFIG xCC = {0};
    uint16_t baudrate = 0;
#elif ECO_AVR8
    uint16_t baudrate = 103;
#elif ECO_BCM283X
    float_t baudrate = 0.0F;
    register unsigned int r;
#elif ECO_RISCV64
    uint32_t uart_clk;
    uint32_t indx;
    uint32_t reg;
#elif ECO_LINUX
    int16_t ptsNum = -1;
#elif ECO_STM32
#endif
    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

#ifdef ECO_WIN32
    pCMe->m_Device = CreateFileA(pCMe->m_config->lpszName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (pCMe->m_Device == INVALID_HANDLE_VALUE) {
        return -1;
    }

    if (pCMe->m_config->lpCC == 0) {
        pCMe->m_config->lpCC = &xCC;
        GetCommConfig(pCMe->m_Device, (LPCOMMCONFIG)pCMe->m_config->lpCC, (LPDWORD)&pCMe->m_config->dwSize);
    }
    if (config != 0 && pCMe->m_config->lpCC != 0) {
        ((LPCOMMCONFIG)pCMe->m_config->lpCC)->dcb.BaudRate = config->BaudRate;
        ((LPCOMMCONFIG)pCMe->m_config->lpCC)->dcb.ByteSize = 8;
        ((LPCOMMCONFIG)pCMe->m_config->lpCC)->dcb.StopBits = ONESTOPBIT;
        ((LPCOMMCONFIG)pCMe->m_config->lpCC)->dcb.Parity = NOPARITY;
        SetCommState(pCMe->m_Device, &((LPCOMMCONFIG)pCMe->m_config->lpCC)->dcb);
    }
#elif ECO_AVR8
    if (config != 0) {
        baudrate = pCMe->m_UARTConfig->Fosc/16/config->BaudRate-1;
    }
    *((volatile uint8_t*)&pCMe->m_UARTConfig->Register.Map->UBRRnH) = (uint8_t)(baudrate>>8);
    *((volatile uint8_t*)&pCMe->m_UARTConfig->Register.Map->UBRRnL) = (uint8_t)baudrate;
    *((volatile uint8_t*)&pCMe->m_UARTConfig->Register.Map->UCSRnB) = ( ( 1 << 4 ) | ( 1 << 3 ) );
    *((volatile uint8_t*)&pCMe->m_UARTConfig->Register.Map->UCSRnC) = (1<<3) | (3<<1);
#elif ECO_BCM283X
    /* Ожидание завершения передачи */
   // while ( !((*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->FR)) & (1<<3 /* BUSY */)) );
    /* Отключение UART */
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->CR) = 0;

    /* Настройка UART0 для pin14-RX и pin15-TX */
    r = *((volatile uint32_t*)&pCMe->m_GPIOConfig->Register.Map->GPFSEL1);
    r  &= ~((7<<12)|(7<<15));
    /* Альтернативный режим */
    r |= (4<<12)|(4<<15);
    *((volatile uint32_t*)&pCMe->m_GPIOConfig->Register.Map->GPFSEL1) = r;
    /* Активация пинов */
    *((volatile uint32_t*)&pCMe->m_GPIOConfig->Register.Map->GPPUD) = 0;
    r=150; while(r--) { asm volatile("nop"); }
    *((volatile uint32_t*)&pCMe->m_GPIOConfig->Register.Map->GPPUDCLK0) = (1<<14)|(1<<15);
    r=150; while(r--) { asm volatile("nop"); }
    *((volatile uint32_t*)&pCMe->m_GPIOConfig->Register.Map->GPPUDCLK0) = 0;        // flush GPIO setup

    /* Очистка очереди передачи FIFO */
   // *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LCRH) &= ~(1<<4 /* FEN */);
   // if (config != 0) {
   //     baudrate = (float_t)pCMe->m_UARTConfig->Fclk/((float_t)16 * (float_t)config->BaudRate);
   // }
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->ICR) = 0x7FF;
    /* Установка скорости передачи как целой и дробной частей */
    /* Baud rate divisor BAUDDIV = (FUARTCLK/(16 Baud rate)) */
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->IBRD) = 2;//(uint32_t)baudrate;
    //baudrate = ((baudrate - (uint32_t)baudrate) * 64) + 0.5F;
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->FBRD) = 0xB;//(uint32_t)baudrate;
    /* Очистка очереди передачи FIFO */
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LCRH) &= ~(1<<4 /* FEN */);
    /* Активация очереди передачи FIFO 8 бит данных (1 stop bit, no parity) */
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LCRH) = (1<<4 /* FEN */) | (3<<5 /* WLEN8 */);

    // set FIFO interrupts to fire at half full
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->IFLS) = (2<<3 /* RX_1_2 */) | (2<<0 /* TX_1_2 */);
    
    // Clear pending interrupts.
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->IFLS) =  0x7F2;

    // Mask all interrupts.
    //*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->IMSC) =  0x7F2;

    // Enable UART0, receive & transfer part of UART.
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->CR) =(1<<0 /* UARTEN */) | (1<<8 /* TXW */) | (1<<9 /* RXE */);
#elif ECO_RISCV64

    /* reset */
    reg = *((volatile uint32_t*)&pCMe->m_CCUConfig->Register.Map->UART_BGR_REG);
    reg &= ~(1<<16);
    *((volatile uint32_t*)&pCMe->m_CCUConfig->Register.Map->UART_BGR_REG) = reg;
    for (indx = 0; indx < 100; indx++)
        ;
    reg |= (1 << 16);
    *((volatile uint32_t*)&pCMe->m_CCUConfig->Register.Map->UART_BGR_REG) = reg;
    /* gate */
    reg = *((volatile uint32_t*)&pCMe->m_CCUConfig->Register.Map->UART_BGR_REG);
    reg &= ~(1<<0);
    *((volatile uint32_t*)&pCMe->m_CCUConfig->Register.Map->UART_BGR_REG) = reg;
    for (indx = 0; indx < 100; indx++)
        ;
    reg |= (1 << 0);
    *((volatile uint32_t*)&pCMe->m_CCUConfig->Register.Map->UART_BGR_REG) = reg;
  

    *((volatile uint32_t*)&pCMe->m_GPIOConfig->Register.Map->PB_CFG1) = 0x000FFF66;
    *((volatile uint32_t*)&pCMe->m_GPIOConfig->Register.Map->PB_PULL0) = (1<<16)|(1<<18);

    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->MCR) = 0x3;
    /* Baud rate for UART,Compute the divisor factor */
    //#define   UART_BAUD    115200   
    uart_clk = (24000000 + 8 * 115200)/(16 * 115200);
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LCR) |= 0x80;
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->Offset0x0004.DLH) = uart_clk>>8;
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->Offset0x0000.DLL) = uart_clk&0xff;
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LCR) &= ~0x80;
    /* UART Line Control Parameter */
    /* Parity: 0,2 - no parity; 1 - odd parity; 3 - even parity */
    //#define   PARITY       0 
    /* Number of Stop Bit: 0 - 1bit; 1 - 2(or 1.5)bits */
    //#define   STOP         0
    /* Data Length: 0 - 5bits; 1 - 6bits; 2 - 7bits; 3 - 8bit */
    //#define   DLEN         3 
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LCR) = ((0&0x03)<<3) | ((0&0x01)<<2) | (3&0x03);
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->Offset0x0008.FCR) = 0x7;
#elif ECO_LINUX
    pCMe->m_Fd = open("/dev/ptmx", O_RDWR | O_NOCTTY);
    ioctl(pCMe->m_Fd, TIOCSBRK, &config->BaudRate); // Set baudrate
    ioctl(pCMe->m_Fd, TIOCSPTLCK, &(int){0}); // Unlock pt
    ioctl(pCMe->m_Fd, TIOCGPTN, &ptsNum); // get pts number
    snprintf(pCMe->m_UARTConfig->devName, pCMe->m_UARTConfig->devNameLen, "/dev/pts/%d", ptsNum); // Set up pts name
  
#elif ECO_STM32
    /* RCC_APB2ENR_USART1EN = (0x1UL << 4U) */
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->APB2ENR) |= (0x1UL << 4U);
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->BRR) = config->BaudRate; 
    /* USART_CR1_TE = (0x1UL << 3U) */
    /* USART_CR1_RE = (0x1UL << 2U) */
    /* USART_CR1_UE = (0x1UL << 13U) */
    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->CR1) = (0x1UL << 3U) | (0x1UL << 2U) | (0x1UL << 13U);
#endif
    return 0;
}

/*
 *
 * <сводка>
 *   Функция Disconnect
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Disconnect(/* in */ struct IEcoUART1Device* me) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }
#ifdef ECO_WIN32
    CloseHandle(pCMe->m_Device);
#elif ECO_RISCV64
    pCMe->m_UARTConfig->Register.Map = 0;
#elif ECO_LINUX
    close(pCMe->m_Fd);
#elif ECO_STM32
    pCMe->m_UARTConfig->Register.Map->CR1 &= ~(0x1UL << 13U);
    pCMe->m_UARTConfig->Register.Map->APB2ENR &= ~(0x1UL << 4U);
#endif

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Transmit
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Transmit(/* in */ struct IEcoUART1Device* me, /* in */ byte_t data) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)me;

#ifdef ECO_WIN32
    char_t lpBuffer[] = "A";
    DWORD dNoOFBytestoWrite = 1;
    DWORD dNoOfBytesWritten = 0;
#endif

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

#ifdef ECO_WIN32
    lpBuffer[0] = data;
    WriteFile(pCMe->m_Device, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
#elif ECO_AVR8
    while ( !((*((volatile uint8_t*)&pCMe->m_UARTConfig->Register.Map->UCSRnA)) & (1<<5)) );
    *((volatile uint8_t*)&pCMe->m_UARTConfig->Register.Map->UDRn) = data;
#elif ECO_BCM283X
   // while ( ((*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->FR)) & (1 << 6)) ){ asm volatile("nop"); };
do{asm volatile("nop");}while(*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->FR)&0x20);

    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->DR) = data;
#elif ECO_RISCV64
    while( (*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LSR)&(1<< 6)) == 0);

    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->Offset0x0000.THR) = data;
#elif ECO_LINUX
    write(pCMe->m_Fd, &data, 1);
#elif ECO_STM32
    /* USART_SR_TXE =  (0x1UL << 7U)*/
    while( (*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->SR)&(0x1UL << 7U)) == 0);

    *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->DR) = data;
#endif

    return 0;
}

//#ifdef ECO_WIN32
//#else
//int delay_count = 65000;
//void delay(uint8_t ms)
//{
//    uint16_t cnt;
//    asm volatile(
//    "\n"
//    "L_dl1%=:" "\n\t"
//    "mov %A0, %A2" "\n\t"
//    "mov %B0, %B2" "\n"
//    "L_dl2%=:" "\n\t"
//    "sbiw %A0, 1" "\n\t"
//    "brne L_dl2%=" "\n\t"
//    "dec %1" "\n\t"
//    "brne L_dl1%=" "\n\t"
//    : "=&w" (cnt)
//    : "r" (ms), "r" (delay_count)
//    );
//}
//#endif
/*
 *
 * <сводка>
 *   Функция Receive
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Receive(/* in */ struct IEcoUART1Device* me, /* out */ byte_t* data) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)me;
#ifdef ECO_WIN32
    char_t TempChar = 0; //Temporary character used for reading
//char SerialBuffer[256];//Buffer for storing Rxed Data
    DWORD NoBytesRead = 0;
    DWORD dwCommEvent;
#elif ECO_LINUX
    char_t TempChar = 0; //Temporary character used for reading
    int16_t NoBytesRead = 0;
#endif

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

#ifdef ECO_WIN32
    if (!SetCommMask(pCMe->m_Device, EV_RXCHAR)) {
        return -1;
    }
    for ( ; ; ) {
        if (WaitCommEvent(pcme->m_device, &dwCommEvent, NULL)) {
            if (ReadFile(pCMe->m_Device, &TempChar, sizeof(TempChar), &NoBytesRead, NULL)) {
                *data = TempChar;
            }
            break;
        }
    }
//while (NoBytesRead > 0);
#elif ECO_AVR9
 //   delay(200);
   //     (*(volatile uint8_t *)(0x25)) ^= 0B00000001;
    //return serial_getc(data);

    while ( !((*((volatile uint8_t*)&pCMe->m_config->Register.Map->UCSRnA)) & (1<<7)) );
    *data = *((volatile uint8_t*)&pCMe->m_config->Register.Map->UDRn); //UDR0;
#elif ECO_BCM283X
    //while ( ((*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->FR)) & (1<<4)) ){asm volatile("nop");};
    do{asm volatile("nop");}while( *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->FR)&0x10);
    *data = *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->DR);
#elif ECO_RISCV64
    while( (*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->LSR)&0x01) == 0);
    *data = *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->Offset0x0000.RBR);
#elif ECO_LINUX
    NoBytesRead = read(pCMe->m_Fd, &TempChar, sizeof(TempChar));
    *data = TempChar;
#elif ECO_STM32
    /* USART_SR_RXNE = (0x1UL << 5U)  */
    while( (*((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->SR)&(0x1UL << 5U)) == 0);
    *data = *((volatile uint32_t*)&pCMe->m_UARTConfig->Register.Map->DR);
#endif
    return 0;
}


#ifdef ECO_LINUX
#else
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface
 * </описание>
 *
 */
#ifdef ECO_BCM283X
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_QueryInterface(/* in */ struct IEcoUART1Device* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#elif ECO_RISCV64
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_QueryInterface(/* in */ IEcoUART1RISCV64D1ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#elif ECO_AVR8
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_QueryInterface(/* in */ IEcoUART1AVR8ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#elif ECO_STM32
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_QueryInterface(/* in */ IEcoUART1STM32F4ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - sizeof(struct IEcoUnknown*));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoUART1Device) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#ifdef ECO_WIN32
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1WIN32Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_AVR8
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1AVR8Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_BCM283X
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1BCM283xConfig) ) {
        *ppv = &pCMe->m_UARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_RISCV64
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCCU1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblICCUConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_STM32
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1STM32F4Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#endif
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef
 * </описание>
 *
 */
#ifdef ECO_BCM283X
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_AddRef(/* in */ struct IEcoUART1Device* me) {
#elif ECO_RISCV64
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_AddRef(/* in */ IEcoUART1RISCV64D1ConfigPtr_t me) {
#elif ECO_AVR8
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_AddRef(/* in */ IEcoUART1AVR8ConfigPtr_t me) {
#elif ECO_STM32
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_AddRef(/* in */ IEcoUART1STM32F4ConfigPtr_t me) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release
 * </описание>
 *
 */
#ifdef ECO_BCM283X
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_Release(/* in */ struct IEcoUART1Device* me) {
#elif ECO_RISCV64
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_Release(/* in */ IEcoUART1RISCV64D1ConfigPtr_t me) {
#elif ECO_AVR8
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_Release(/* in */ IEcoUART1AVR8ConfigPtr_t me) {
#elif ECO_STM32
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_Release(/* in */ IEcoUART1STM32F4ConfigPtr_t me) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoUART1Device_025F3EF0((IEcoUART1Device*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
#ifdef ECO_BCM283X
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor(/* in */ struct IEcoUART1Device* me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config) {
#elif ECO_RISCV64
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor(/* in */ IEcoUART1RISCV64D1ConfigPtr_t me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config) {
#elif ECO_AVR8
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor(/* in */ IEcoUART1AVR8ConfigPtr_t me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config) {
#elif ECO_STM32
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor(/* in */ IEcoUART1STM32F4ConfigPtr_t me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0 || config == 0) {
        return -1;
    }

    pCMe->m_UARTConfig = config;
    return 0;
}

/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
#ifdef ECO_BCM283X
ECO_UART_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor(/* in */ struct IEcoUART1Device* me) {
#elif ECO_RISCV64
ECO_UART_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor(/* in */ IEcoUART1RISCV64D1ConfigPtr_t me) {
#elif ECO_AVR8
ECO_UART_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor(/* in */ IEcoUART1AVR8ConfigPtr_t me) {
#elif ECO_STM32
ECO_UART_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor(/* in */ IEcoUART1STM32F4ConfigPtr_t me) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    return pCMe->m_UARTConfig;
}
#endif

#ifdef ECO_WIN32
#elif ECO_LINUX
#elif ECO_STM32

#else
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoGPIO1CustomizeConfig
 * </описание>
 *
 */
#ifdef ECO_BCM283X
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_QueryInterface(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#elif ECO_RISCV64
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_QueryInterface(/* in */ struct IEcoGPIO1RISCV64D1Config* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#elif ECO_AVR8
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_QueryInterface(/* in */ IEcoUART1AVR8ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#elif ECO_STM32
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_QueryInterface(/* in */ IEcoUART1STM32F4ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*2));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoUART1Device) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#ifdef ECO_WIN32
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1WIN32Config) ) {
        *ppv = &pCMe->m_pVTblIConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_AVR8
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1AVR8Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_BCM283X
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_RISCV64
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCCU1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblICCUConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_STM32
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1STM32F4Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#endif
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoGPIO1CustomizeConfig
 * </описание>
 *
 */
#ifdef ECO_BCM283X
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_AddRef(/* in */ struct IEcoGPIO1BCM283xConfig* me) {
#elif ECO_RISCV64
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_AddRef(/* in */ struct IEcoGPIO1RISCV64D1Config* me) {
#elif ECO_AVR8
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_AddRef(/* in */ struct IEcoGPIO1RISCV64D1Config* me) {
#elif ECO_STM32
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_AddRef(/* in */ struct IEcoGPIO1STM32Config* me) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*2));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoGPIO1CustomizeConfig
 * </описание>
 *
 */
#ifdef ECO_BCM283X
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_Release(/* in */ struct IEcoGPIO1BCM283xConfig* me) {
#elif ECO_RISCV64
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_Release(/* in */ struct IEcoGPIO1RISCV64D1Config* me) {
#elif ECO_STM32
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_Release(/* in */ struct IEcoGPIO1STM32Config* me) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*2));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoUART1Device_025F3EF0((IEcoUART1Device*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
#ifdef ECO_BCM283X
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_set_ConfigDescriptor(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config) {
#elif ECO_RISCV64
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_set_ConfigDescriptor(/* in */ struct IEcoGPIO1RISCV64D1Config* me, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config) {
#elif ECO_STM32
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_set_ConfigDescriptor(/* in */ struct IEcoGPIO1STM32Config* me, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*2));

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    pCMe->m_GPIOConfig = config;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
#ifdef ECO_BCM283X
ECO_GPIO_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_get_ConfigDescriptor(/* in */ struct IEcoGPIO1BCM283xConfig* me) {
#elif ECO_RISCV64
ECO_GPIO_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_get_ConfigDescriptor(/* in */ struct IEcoGPIO1RISCV64D1Config* me) {
#elif ECO_STM32
ECO_GPIO_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_get_ConfigDescriptor(/* in */ struct IEcoGPIO1STM32Config* me) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*2));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return (ECO_GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;
}

/*
 *
 * <сводка>
 *   Функция set_LogicalPinNumber
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
#ifdef ECO_BCM283X
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_set_LogicalPinNumber(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t BankNumber, /* in */ uint32_t PinNumber) {
#elif ECO_RISCV64
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_set_LogicalPinNumber(/* in */ struct IEcoGPIO1RISCV64D1Config* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t BankNumber, /* in */ uint32_t PinNumber) {
#elif ECO_STM32
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_GPIOConfig_set_LogicalPinNumber(/* in */ struct IEcoGPIO1STM32Config* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t BankNumber, /* in */ uint32_t PinNumber) {
#endif
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*2));

    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t index = 0;
    int16_t result = -1;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    pDescriptor = (ECO_GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;

    if (pDescriptor != 0) {
        for(index = 0; index < 32; index++) {
            if (PinNumber & (1 << index)) {
                if (BankNumber == 0) {
                    pDescriptor->LogicalPinMask[index] = LogicalPinNumber;
                    result = 0;
                }
                else if (BankNumber == 1) {
                    pDescriptor->LogicalPinMask[32 + index] = LogicalPinNumber;
                    result = 0;
                }
                break;
            }
        }
    }
    return result;
}

#endif

#ifdef ECO_WIN32
#elif ECO_LINUX
#elif ECO_STM32
#else
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCCU1CustomizeConfig
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_CCUConfig_QueryInterface(/* in */ struct IEcoCCU1RISCV64D1Config* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*3));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoUART1Device) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIDevice;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#ifdef ECO_WIN32
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1WIN32Config) ) {
        *ppv = &pCMe->m_pVTblIConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_AVR8
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1AVR8Config) ) {
        *ppv = &pCMe->m_pVTblIConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_BCM283X
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_RISCV64
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIUARTConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCCU1RISCV64D1Config) ) {
        *ppv = &pCMe->m_pVTblICCUConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }
#elif ECO_LINUX
    else if ( IsEqualUGUID(riid, &IID_IEcoUART1LinuxConfig) ) {
        *ppv = &pCMe->m_pVTblIConfig;
        pCMe->m_pVTblIDevice->AddRef((IEcoUART1Device*)pCMe);
    }

#endif
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCCU1CustomizeConfig
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_CCUConfig_AddRef(/* in */ struct IEcoCCU1RISCV64D1Config* me) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*3));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCCU1CustomizeConfig
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_CCUConfig_Release(/* in */ struct IEcoCCU1RISCV64D1Config* me) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*3));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoUART1Device_025F3EF0((IEcoUART1Device*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1Device_025F3EF0_CCUConfig_set_ConfigDescriptor(/* in */ struct IEcoCCU1RISCV64D1Config* me, /* in */ ECO_CCU_CONFIG_DESCRIPTOR* config) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*3));

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    pCMe->m_CCUConfig = config;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
ECO_CCU_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoUART1Device_025F3EF0_CCUConfig_get_ConfigDescriptor(/* in */ struct IEcoCCU1RISCV64D1Config* me) {
    CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)((uint64_t)me - (sizeof(struct IEcoUnknown*)*3));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return (ECO_CCU_CONFIG_DESCRIPTOR*)pCMe->m_CCUConfig;
}
#endif

/* Create Virtual Table */
IEcoUART1DeviceVTbl g_x6B754B247D03435BB5E22165A2041862VTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_QueryInterface,
    CEcoUART1Device_025F3EF0_AddRef,
    CEcoUART1Device_025F3EF0_Release,
    CEcoUART1Device_025F3EF0_Connect,
    CEcoUART1Device_025F3EF0_Disconnect,
    CEcoUART1Device_025F3EF0_Transmit,
    CEcoUART1Device_025F3EF0_Receive
};
#ifdef ECO_WIN32
IEcoUART1WIN32ConfigVTbl g_x5A72857AAEEA4BF5AAB4B692A4BE3FAAVTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_Config_QueryInterface,
    CEcoUART1Device_025F3EF0_Config_AddRef,
    CEcoUART1Device_025F3EF0_Config_Release,
    CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor
};
#elif ECO_AVR8
IEcoUART1AVR8ConfigVTbl g_xC04E2997A52A484897FF8A43EBB1CBCCVTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_Config_QueryInterface,
    CEcoUART1Device_025F3EF0_Config_AddRef,
    CEcoUART1Device_025F3EF0_Config_Release,
    CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor
};
#elif ECO_BCM283X
IEcoUART1BCM283xConfigVTbl g_xA1EC7F566538454BA1866D34922E64DAVTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_Config_QueryInterface,
    CEcoUART1Device_025F3EF0_Config_AddRef,
    CEcoUART1Device_025F3EF0_Config_Release,
    CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor
};

IEcoGPIO1BCM283xConfigVTbl g_x7B844D9CEA994E8695DDCA78668D0B2AVTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_GPIOConfig_QueryInterface,
    CEcoUART1Device_025F3EF0_GPIOConfig_AddRef,
    CEcoUART1Device_025F3EF0_GPIOConfig_Release,
    CEcoUART1Device_025F3EF0_GPIOConfig_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_GPIOConfig_get_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_GPIOConfig_set_LogicalPinNumber
};
#elif ECO_RISCV64
IEcoUART1RISCV64D1ConfigVTbl g_xBCF99D0D02594AE99368D8805C95DB09VTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_Config_QueryInterface,
    CEcoUART1Device_025F3EF0_Config_AddRef,
    CEcoUART1Device_025F3EF0_Config_Release,
    CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor
};

IEcoGPIO1RISCV64D1ConfigVTbl g_x2C25EC2943B44E4583B43375FC35C4D6VTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_GPIOConfig_QueryInterface,
    CEcoUART1Device_025F3EF0_GPIOConfig_AddRef,
    CEcoUART1Device_025F3EF0_GPIOConfig_Release,
    CEcoUART1Device_025F3EF0_GPIOConfig_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_GPIOConfig_get_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_GPIOConfig_set_LogicalPinNumber
};

IEcoCCU1RISCV64D1ConfigVTbl g_xED0950291B1049CCA09349F7CA6B61E0VTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_CCUConfig_QueryInterface,
    CEcoUART1Device_025F3EF0_CCUConfig_AddRef,
    CEcoUART1Device_025F3EF0_CCUConfig_Release,
    CEcoUART1Device_025F3EF0_CCUConfig_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_CCUConfig_get_ConfigDescriptor
};

#elif ECO_STM32
IEcoUART1STM32F4ConfigVTbl g_x45B766B1B8364345BFF269BF659FD3DCVTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_Config_QueryInterface,
    CEcoUART1Device_025F3EF0_Config_AddRef,
    CEcoUART1Device_025F3EF0_Config_Release,
    CEcoUART1Device_025F3EF0_Config_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_Config_get_ConfigDescriptor
};
IEcoGPIO1STM32ConfigVTbl g_xD9671208DCAD444890AA5F4825055DFAVTbl_025F3EF0 = {
    CEcoUART1Device_025F3EF0_GPIOConfig_QueryInterface,
    CEcoUART1Device_025F3EF0_GPIOConfig_AddRef,
    CEcoUART1Device_025F3EF0_GPIOConfig_Release,
    CEcoUART1Device_025F3EF0_GPIOConfig_set_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_GPIOConfig_get_ConfigDescriptor,
    CEcoUART1Device_025F3EF0_GPIOConfig_set_LogicalPinNumber
};

#endif

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoUART1Device_025F3EF0(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoUART1Device** ppIDevice) {
    int16_t result = -1;
    CEcoUART1Device_025F3EF0* pCMe = 0;
    
    /* Проверка указателей */
    if (ppIDevice == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_xB40E129B56624BD7B5F8339C025F3EF0UART1Device[0];
    if (pCMe->m_cRef !=  0) {
        pCMe = &g_xB40E129B56624BD7B5F8339C025F3EF0UART1Device[1];
        if (pCMe->m_cRef !=  0) {
            pCMe = &g_xB40E129B56624BD7B5F8339C025F3EF0UART1Device[2];
            if (pCMe->m_cRef !=  0) {
                return result;
            }
        }
    }

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoUART1Device */
    pCMe->m_pVTblIDevice = &g_x6B754B247D03435BB5E22165A2041862VTbl_025F3EF0;

#ifdef ECO_WIN32
    pCMe->m_pVTblIUARTConfig = &g_x5A72857AAEEA4BF5AAB4B692A4BE3FAAVTbl_025F3EF0;
#elif ECO_AVR8
    pCMe->m_pVTblIUARTConfig = &g_xC04E2997A52A484897FF8A43EBB1CBCCVTbl_025F3EF0;
#elif ECO_BCM283X
    pCMe->m_pVTblIUARTConfig = &g_xA1EC7F566538454BA1866D34922E64DAVTbl_025F3EF0;
    pCMe->m_pVTblIGPIOConfig = &g_7B844D9CEA994E8695DDCA78668D0B2AVTbl_025F3EF0;
#elif ECO_RISCV64
    pCMe->m_pVTblIUARTConfig = &g_xBCF99D0D02594AE99368D8805C95DB09VTbl_025F3EF0;
    pCMe->m_pVTblIGPIOConfig = &g_x2C25EC2943B44E4583B43375FC35C4D6VTbl_025F3EF0;
    pCMe->m_pVTblICCUConfig = &g_xED0950291B1049CCA09349F7CA6B61E0VTbl_025F3EF0;
#elif ECO_STM32
    pCMe->m_pVTblIUARTConfig = &g_x45B766B1B8364345BFF269BF659FD3DCVTbl_025F3EF0;
    pCMe->m_pVTblIGPIOConfig = &g_xD9671208DCAD444890AA5F4825055DFAVTbl_025F3EF0;
#endif

    /* Инициализация данных */

    /* Возврат указателя на интерфейс */
    *ppIDevice = (IEcoUART1Device*)pCMe;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoUART1Device_025F3EF0(/* in */ IEcoUART1Device* pIEcoUART1Device) {
    /*CEcoUART1Device_025F3EF0* pCMe = (CEcoUART1Device_025F3EF0*)pIEcoUART1Device;*/
}
