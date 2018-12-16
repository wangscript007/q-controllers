/*���ļ�����һЩ���õ�ϵͳ���������Թ�ϵͳ��ҳ����ã�����ҳ������Ϊ�����뺯��*/

#include "SysDefines.h"

void MemSet(void *Dst,u8 C,u16 Byte)
{
	if(Dst==NULL) return;
	if(!Byte) return;

	for(Byte-=1;Byte;Byte--)
	{
		((u8 *)Dst)[Byte]=C;
	}
	((u8 *)Dst)[0]=C;
}

void MemCpy(void *Dst,const void *Src,u16 Byte)
{
	if(Dst==NULL || Src==NULL || Dst==Src) return;
	if(!Byte) return;
	
	for(Byte-=1;Byte;Byte--)
	{
		((u8 *)Dst)[Byte]=((u8 *)Src)[Byte];
	}
	((u8 *)Dst)[0]=((u8 *)Src)[0];
}

//pStr�����������Ҫ�󣬷���-1
//֧��ʮ����,ʮ������,������
//���Կո���������ȷ�ַ����˳�
u32 StrToUint(const u8 *pStr)         
{
	u32 i=0,sum=0;

	if(pStr == NULL) return 0;
	
	if(pStr[0]=='0'&&pStr[1]=='x')
	{
		i=2;
		while(pStr[i])            //��str[i]��Ϊ\0ʱִ��ѭ��
		{
			if(pStr[i]>='0'&&pStr[i]<='9')
			{
				sum=(sum<<4)+(pStr[i]-'0');
			}
			else if(pStr[i]>='a'&&pStr[i]<='f')
			{
				sum=(sum<<4)+(pStr[i]-'a'+10);
			}
			else if(pStr[i]>='A'&&pStr[i]<='F')
			{
				sum=(sum<<4)+(pStr[i]-'A'+10);
			}
			else if(pStr[i] == ' ')//�ո�������
			{
			}
			else
			{
				break;//str����ȷ�ַ�
			}

			i++;
		}
	}
	if(pStr[0]=='0'&&pStr[1]=='b')
	{
		i=2;
		while(pStr[i])            //��str[i]��Ϊ\0ʱִ��ѭ��
		{
			if(pStr[i]>='0'&&pStr[i]<='1')
			{
				sum=(sum<<1)+(pStr[i]-'0');
			}
			else if(pStr[i] == ' ')//�ո�������
			{
			}			
			else
			{
				break;//str����ȷ�ַ�
			}

			i++;
		}
	}
	else
	{
		while(pStr[i])            //��str[i]��Ϊ\0ʱִ��ѭ��
		{
			if(pStr[i] == ' ')//�ո�������
			{
			}
			else if(pStr[i]<'0'||pStr[i]>'9') 
			{
				break;//str����ȷ�ַ�
			}
			else
				sum=sum*10+(pStr[i]-'0');

			i++;
		}
	}
	
	return(sum);
} 

//�з���ת��
//pStr�����������Ҫ�󣬷���-1
//֧��ʮ����,ʮ������,������
//���Կո���������ȷ�ַ����˳�
//��һ���ַ������ֻ��߸���
s32 StrToSint(const u8 *pStr)
{
	if(pStr[0]=='-')
	{
		return 0-StrToUint(&pStr[1]);
	}
	else
	{
		return StrToUint(pStr);
	}
}

//�ر�ע�⣬���������и��������ʱҪ�ѣ����ֺ������һ��f��
//�������ʽ����4.321�������㡣�����㲻��4.321���fʱ��stm32F405��Ƭ�Ӳ�֪����������������float��FPU�����㣬
//Ĭ�Ͽ����ǵ���double�����㣨�Ҳ�ȷ�����������ٶȻ��Ǻ��������м����и������ֺ������f��������
//��ʱ��keil����ʾwarning:  #1035-D: single-precision operand implicitly converted to double-precision 
//��仰����˼���ǵ�����������ʽת������˫���������ˡ����ʱ���Ҫ�ڵ��������ֺ���Ӹ�f
//��������ת��Ϊ����
int FloatToInt(float f) 
{     
	bool minus=(f<0.0f?TRUE:FALSE); 
	int a;

	if(minus) f*=-1; 
	a=(int)f; 
	if((f-a)>=0.5f) ++a; 
	if(minus)a*=-1; 
	return a; 
}

typedef union                                        
{
   float f;
   u8 b[4];
}DT_FORM_CONVER;

//������תieee��׼
u32 Float2Ieee(float f_num)
{
	u32 Temp32=0;
	u16 i;
	DT_FORM_CONVER DtformConver;

	DtformConver.f=f_num;
	for(i=0;i<4;i++)
	{
		Temp32 |= (u32)(DtformConver.b[i]<<(i*8));
	}

	return Temp32;
}

//ieee��׼ת������
float Ieee2Float(u32 b_num)
{
	u16 i;
	DT_FORM_CONVER DtformConver;

	for(i=0;i<4;i++)
	{
		DtformConver.b[i] = (u8)(b_num>>(i*8));
	}
	return DtformConver.f;
}

//�Ƚ������ڴ�����ֽ��Ƿ���ͬ������TRUE��ʾ��ͬ��Lenָ���Ƚϳ���
bool CompareBuf(u8 *Buf1,u8 *Buf2,u16 Len)
{
	u16 i;

	for(i=0;i<Len;i++)
	{
		if(Buf1[i]!=Buf2[i]) return FALSE;
	}

	return TRUE;
}

//��ӡָ�����ȵ��ַ���
void DisplayStrN(const u8 *Buf,u16 Len)
{
	int i;
	
	for(i=0;i<Len;i++)
	{
		if(Buf[i]==0) break;
		Debug("%c",Buf[i]);
	}
	Debug("\n\r");
}

//Buf Ҫ��ӡ���ڴ�
//Len Ҫ��ӡ���ֽ���
//RawLen ÿ��Ҫ��ӡ���ֽ���
void DisplayBuf(const u8 *Buf,u16 Len,u8 RawLen)
{
	int i;
	
	for(i=0;i<Len;i++)
	{
		Debug("%02x ",Buf[i]);
		if(i%RawLen==(RawLen-1)) Debug("\n\r");
	}
	if(i%RawLen!=(RawLen-1)) Debug("\n\r");
}

void DisplayBufU16(const u16 *Buf,u16 Len,u8 RawLen)
{
	int i;
	
	for(i=0;i<Len;i++)
	{
		Debug("%04x ",Buf[i]);
		if(i%RawLen==(RawLen-1)) Debug("\n\r");
	}
	if(i%RawLen!=(RawLen-1)) Debug("\n\r");
}

void DisplayBufU16_Dec(const u16 *Buf,u16 Len,u8 RawLen)
{
	int i;
	
	for(i=0;i<Len;i++)
	{
		Debug("%5u ",Buf[i]);
		if(i%RawLen==(RawLen-1)) Debug("\n\r");
	}
	if(i%RawLen!=(RawLen-1)) Debug("\n\r");
}

void DisplayBufU32(const u32 *Buf,u16 Len,u8 RawLen)
{
	int i;
	
	for(i=0;i<Len;i++)
	{
		Debug("%08x ",Buf[i]);
		if(i%RawLen==(RawLen-1)) Debug("\n\r");
	}
	if(i%RawLen!=(RawLen-1)) Debug("\n\r");
}

//ģ�����
//������ֵ���
//Tole�����ٷֱ�
//A B����������100 0000
bool FuzzyEqual(u32 A,u32 B,u8 Tole)
{
	if(A==B) return TRUE;
	if(Tole>=100) return TRUE;

	if(A>B)
	{
		if( B*100 > A*(100-Tole)) return TRUE;
	}
	else
	{
		if( A*100 > B*(100-Tole)) return TRUE;
	}
	
	return FALSE;	
}

static char gIpAddrStrBuf[20];
char *Ip2Str(void *pIp)//�����԰�ȫ
{
	u8 *pIpU8=pIp;
	
	sprintf(gIpAddrStrBuf,"%d.%d.%d.%d",pIpU8[0],pIpU8[1],pIpU8[2],pIpU8[3]);

	return gIpAddrStrBuf;
}

//����ip�ַ���
bool Str2Ip(const u8 *pStr,u8 *Ip)
{
	u8 Buf[32];
	u8 *pIp1Str=Buf;
	u8 *pIp2Str;
	u8 *pIp3Str;
	u8 *pIp4Str;

	if(strlen((void *)pStr)>30) return FALSE;
	strcpy((void *)Buf,(void *)pStr);

	if(pStr[0]<'0'||pStr[0]>'9') return FALSE;

	pIp2Str=FindStr(pIp1Str,".",NULL);
	if(pIp2Str == NULL) return FALSE;
	
	pIp3Str=FindStr(pIp2Str,".",NULL);
	if(pIp2Str == NULL) return FALSE;

	pIp4Str=FindStr(pIp3Str,".",NULL);
	if(pIp2Str == NULL) return FALSE;
	
	Ip[0]=StrToUint(pIp1Str);
	Ip[1]=StrToUint(pIp2Str);
	Ip[2]=StrToUint(pIp3Str);
	Ip[3]=StrToUint(pIp4Str);

	return TRUE;
}

//���ַ������Сд
//�ַ������Ȳ�Ҫ����255
void StrToLower(u8 *pStr)
{
	u8 Len=strlen((void *)pStr);
	u8 i;
	
	for(i=0;i<=Len;i++)//�����ַ���ȫ��תСд
	{
		if(pStr[i]<0x80)//ascii
		{
			if(pStr[i]>='A' && pStr[i]<='Z')
				pStr[i]=pStr[i]+32;
		}
		else//����
		{
			i++;
		}
	}
}

//���ַ����Ƿ��
bool IsNullStr(u8 *pStr)
{
	if(pStr==NULL || pStr[0]==0) return TRUE;

	return FALSE;
}

//���ַ����Ƿ��
bool NotNullStr(u8 *p)
{
	if(p==NULL || *p==0) return FALSE;

	return TRUE;
}

//�Ƚ��ַ�����֧��ͨ���*
//��ȷ���0
u16 StrnCmp(const u8 *pStr1,const u8 *pStr2,u16 Bytes)
{
	u16 i;

	for(i=0;i<Bytes;i++)
	{
		if(pStr1[i]!=pStr2[i] && pStr2[i]!='*')
			return i;
	}

	return 0;
}

//��str1������str2��str2��������ͨ���*�������ֽڲ�����*
//�ҵ�����λ�ã�δ�ҵ�����NULL
u8 *ChkStr(const u8 *pStr1, const u8 *pStr2 )
{
	u16 len2=strlen((void *)pStr2);

	if(len2==0) return NULL;
	if(strlen((void *)pStr1)==0) return NULL;

	for(;*pStr1;++pStr1)
	{
		if(*pStr1==*pStr2 && StrnCmp(pStr1,pStr2,len2)==0) 
			return (u8 *)pStr1;
	}
	
	return NULL;
}

//����ͷβѰ���ַ���������β������λ����0
//����pStrEndΪ�գ���pStrEndΪ�գ���ֻ��ͷ
//���ص���ȥ��ͷ�ַ�����ͷ��ָ��
u8 *FindStr(u8 *pStr,u8 *pStrStart,u8 *pStrEnd)
{
	u8 *pStart,*pEnd;
	
	pStart=(void *)strstr((void *)pStr,(void *)pStrStart);
	if(pStart==NULL) return NULL;
	
	pStart+=strlen((void *)pStrStart);
	if(pStrEnd==NULL || pStrEnd[0]==0) return pStart;
	pEnd=(void *)strstr((void *)pStart,(void *)pStrEnd);
	if(pEnd==NULL) return NULL;

	pEnd[0]=0;
	return pStart;
}

//���ݷָ���������ַ���
//idx��1��ʼ
u8 SplitStr(u8 *pStr,u8 GapChar,u8 Idx)
{
	u8 i=0;
	
	while(pStr[i])
	{
		if(pStr[i]==GapChar)
		{
			Idx--;
			if(Idx==0) return i;
		}
	}

	return 0;
}

// 4�ֽڶ���
u32 AlignTo4(u32 v)
{
	if(v&0x03) v=(v&~0x03)+4;
	return v;
}

//����Ƿ�4�ֽڶ���
bool IsAlign4(u32 v)
{
	return (v&0x03)?FALSE:TRUE;
}

// 8�ֽڶ���
u32 AlignTo8(u32 v)
{
	if(v&0x07) v=(v&~0x07)+8;
	return v;
}

//����Ƿ�8�ֽڶ���
bool IsAlign8(u32 v)
{
	return (v&0x07)?FALSE:TRUE;
}

//����hash33ֵ
u32 MakeHash33(u8 *pData,u32 Len)
{
	u32 hash=(u32)-1;
	u32 i=0;

 	if(pData == NULL || Len == 0) return (u32)-1;
 	
	for(;i<Len;i++)
	{
		hash+=pData[i];
		hash+=(hash<<5);
	}

	return hash;
}

//����У���
u32 CheckSum(const u8 *pData,u32 Len)
{
	u32 Sum=0;
	u32 i=0;

 	if(pData == NULL || Len == 0) return 0;
 	
	for(;i<Len;i++)
	{
		Sum+=pData[i];
	}

	return Sum;
}

/*Table of CRC values for high-order byte*/
const static u8 auchCRCHi[]={
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

/*Table of CRC values for low-order byte*/
const static char auchCRCLo[]={
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2,0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6,0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE,0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA,0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62,0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE,0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76,0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A,0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86,0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

//����crc
u16 CRC16(const u8 *pData,u16 Len)
{
	u8 uchCRCHi=0xff; /*У������ֽڳ�ֵ*/
	u8 uchCRCLo=0xff;/* У������ֽڳ�ֵ*/
	u16 uIndex;       

	while(Len--)
	{
		uIndex=uchCRCHi^*pData++;
		uchCRCHi=uchCRCLo^auchCRCHi[uIndex];
		uchCRCLo=auchCRCLo[uIndex];
	}
	
	return(uchCRCHi<<8|uchCRCLo);
}

//����u16�ĸߵ��ֽ�
//0x1234 -> 0x3412
u16 Rev16(u16 Data)
{
	return __REV16(Data);
}

//��תu32���ֽ�˳��
//0x12345678 -> 0x78563412
u32 Rev32(u32 Data)
{
	return __REV(Data);
}

//���ط�0���ֵ
//�����õ�����0�����ֵ������1λ���ɡ�
u32 Rand(u32 Mask)
{
	u32 RandNum=((GetAdcRand()+(*((volatile u32 *)0xE000E018)))*(*((volatile u32 *)0xE000E018)))&Mask;	 //by systick

#if 0
	{
		u32 i;
		Debug("GetAdcRand %u\n\r",GetAdcRand());for(i=0xfffff;i;i--);
	}
#endif



	return (RandNum?RandNum:(0x12345678&Mask));
}

//��ȡӲ��ΨһID
u32 GetHwID(u8 *pID)
{
	static u32 HwID=0;
	u8 i;

	if(pID==NULL)
	{
		if(HwID==0) HwID=MakeHash33((u8 *)0x1FFFF7E8,12);
	}
	else
	{
		HwID=MakeHash33((u8 *)0x1FFFF7E8,12);
	    for(i=0;i<12;i++) pID[i]=*(u8 *)(0x1FFFF7E8+i);
	}
	
	return HwID;
}

//��ȡĬ������
u32 GenerateDefPw(void)
{
	return 888888;
}

#if 0
void PrintChineseCharToCode(const u8 *pChineseStr)
{
	int i;
	u16 Len=strlen(pChineseStr);

	Debug("{");
	for(i=0;i<Len;i++)
	{
		Debug("0x%02x,",pChineseStr[i]);
	}
	Debug("\b}, /\/\%s\n\r",pChineseStr);
}
#endif

#define MAX_SYSCALL_INTERRUPT_PRIORITY 	(1<<4) 

__asm u32 SaveCpuStatus(void)
{
#if 0
	PRESERVE8

	push { r0 }
	mov r0, #MAX_SYSCALL_INTERRUPT_PRIORITY
	msr basepri, r0
	pop { r0 }
	bx r14
#else 
    MRS     R0, PRIMASK 
    CPSID   I
    BX      LR
#endif
}

__asm void RestoreCpuStatus(u32 cpu_sr)
{
#if 0
	PRESERVE8

	push { r0 }
	mov r0, #0
	msr basepri, r0
	pop { r0 }
	bx r14
#else
    MSR     PRIMASK, R0
    BX      LR
#endif
}



