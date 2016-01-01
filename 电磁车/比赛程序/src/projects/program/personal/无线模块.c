
#include "include.h"

#define Payload_Width        30         // 单次发送数据量，不建议太大

unsigned char Communicate_Address[5]={0x34,0x43,0x10,0x10,0x02};

/**********************************************************/
/********************     无线模块     ********************/
/**********************************************************/

//----------------------无线模块命令----------------------// 

#define READ_REG        0x00  
#define WRITE_REG       0x20 
#define RD_RX_PLOAD     0x61 
#define WR_TX_PLOAD     0xA0  
#define FLUSH_TX        0xE1 
#define FLUSH_RX        0xE2 
#define REUSE_TX_PL     0xE3  
#define NOP             0xFF

//-----------------------寄存器地址-----------------------// 

#define CONFIG          0x00 
#define EN_AA           0x01 
#define EN_RXADDR       0x02 
#define SETUP_AW        0x03 
#define SETUP_RETR      0x04 
#define RF_CH           0x05
#define RF_SETUP        0x06  
#define STATUS          0x07 
#define OBSERVE_TX      0x08  
#define CD              0x09 
#define RX_ADDR_P0      0x0A 
#define RX_ADDR_P1      0x0B 
#define RX_ADDR_P2      0x0C 
#define RX_ADDR_P3      0x0D  
#define RX_ADDR_P4      0x0E 
#define RX_ADDR_P5      0x0F 
#define TX_ADDR         0x10
#define RX_PW_P0        0x11  
#define RX_PW_P1        0x12 
#define RX_PW_P2        0x13 
#define RX_PW_P3        0x14 
#define RX_PW_P4        0x15 
#define RX_PW_P5        0x16 
#define FIFO_STATUS     0x17 


void nRF2401_IO_Init(void)  
{
  gpio_init  (PORTB,1,GPO,1);
  gpio_init  (PORTB,3,GPO,1);
  gpio_init  (PORTB,7,GPO,1);
  gpio_init  (PORTB,9,GPO,1);
  gpio_init  (PORTB,5,GPI,1);
  gpio_init  (PORTB,11,GPI,1);
}


/**********************************************************/
/*******************     这有五个字     *******************/
/**********************************************************/

//-----------------------SPI读写函数----------------------// 

unsigned char SPI_RW(unsigned char SPI_Temp_Char)
{
  unsigned char Temp_i;
  for(Temp_i=0;Temp_i<8;Temp_i++) 
  {
    if(SPI_Temp_Char&0x80)
      nRF_MOSI=1;
    else
      nRF_MOSI=0;
    SPI_Temp_Char=(SPI_Temp_Char<<1);
    nRF_SCK=1;
    SPI_Temp_Char|=nRF_MISO;
    nRF_SCK=0;
  }
  return(SPI_Temp_Char);
}

//-----------------------SPI写寄存器----------------------// 

void SPI_RW_Reg(unsigned char nRF_Address,unsigned char nRF_Write_Char)
{
  unsigned char Status;
  nRF_CSN=0;
  Status=SPI_RW(nRF_Address);
  (void)SPI_RW(nRF_Write_Char);
  nRF_CSN=1;
}

//-----------------------SPI读寄存器----------------------// 

unsigned char SPI_Read(unsigned char nRF_Address)
{
  unsigned char Temp_Value;
  nRF_CSN=0;
  (void)SPI_RW(nRF_Address);
  Temp_Value=SPI_RW(0);
  nRF_CSN=1;
  return(Temp_Value);
}

//----------------------SPI批量写数据---------------------// 

void SPI_Write_Buf(unsigned char nRF_Address,unsigned char *nRF_Write_Buf,unsigned char Write_Number)
{
  unsigned char Status,Temp_Count;
  nRF_CSN=0;
  Status=SPI_RW(nRF_Address);
  for(Temp_Count=0;Temp_Count<Write_Number;Temp_Count++) 
  SPI_RW(*nRF_Write_Buf++);
  nRF_CSN=1;
}

//--------------------无线模块发数据包--------------------// 

void nRF_Send_Pacage(unsigned char *nRF_Write_String) 
{
  SPI_Write_Buf(WR_TX_PLOAD,nRF_Write_String,Payload_Width);    
  while(nRF_IRQ);
  (void)SPI_RW_Reg(WRITE_REG+STATUS,0xff);
}

/**********************************************************/
/********************     无线模块     ********************/
/**********************************************************/

//------------------------修改模式------------------------// 

void Send_Init(void)
{
  nRF2401_IO_Init();
  nRF_CE=0;
  nRF_CSN=1;
  nRF_SCK=0;
  
	nRF_CE=0;
	SPI_Write_Buf(WRITE_REG+TX_ADDR,Communicate_Address,5);    // 写入发送地址
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,Communicate_Address,5); // 为了应答接收设备，接收通道0地址和发送地址相同
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);      // 使能接收通道0自动应答
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);  // 使能接收通道0
	SPI_RW_Reg(WRITE_REG+SETUP_AW,0x03);
	SPI_RW_Reg(WRITE_REG+SETUP_RETR,0x01);//0a); // 自动重发延时等待250us+86us，自动重发10次
	SPI_RW_Reg(WRITE_REG+RF_CH,41);        // 选择射频通道0x40
	SPI_RW_Reg(WRITE_REG+RF_SETUP,0x07);   // 数据传输率2Mbps，发射功率0dBm，低噪声放大器增益
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);     // CRC使能，16位CRC校验，上电
	nRF_CE=1;
}



int error_send;
void Send_Data(void)
{
 unsigned char Temp_Send_List[30];
 
 Temp_Send_List[0]=pulse;
 Temp_Send_List[1]=(left[0])>>8;
 Temp_Send_List[2]=(left[0]);
 Temp_Send_List[3]=(right[0])>>8;
 Temp_Send_List[4]=(right[0]);
 Temp_Send_List[5]=(middle[0])>>8;
 Temp_Send_List[6]=(middle[0]);
 Temp_Send_List[7]=(middle_new[0])>>8;
 Temp_Send_List[8]=(middle_new[0]);
 /*
  error_send=error*10000;
 
 
  
  Temp_Send_List[1]=speed;
  Temp_Send_List[2]=read_left>>8;
  Temp_Send_List[3]=read_left;
  Temp_Send_List[4]=read_right>>8;
  Temp_Send_List[5]=read_right;
  Temp_Send_List[6]=read_middle>>8;
  Temp_Send_List[7]=read_middle; 
  Temp_Send_List[8]=error_send>>8;
  Temp_Send_List[9]=error_send;
  if(error > 0 || error==0)
    Temp_Send_List[10]=1;
  else if(error<0)
    Temp_Send_List[10]=0;*/
  
  nRF_Send_Pacage(Temp_Send_List);  //将数组里的30个数据全部发送出去
}

