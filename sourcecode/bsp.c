if (gu8SCIDataFlag == 1)
{
	if (gu8SCIRx_i == 0)
	{	//Empfang des Start-Bytes
		if (gu8SCIData[0] > 0x0F)
		{	//ungültiges Start-Byte erhalten
			gu8SCIDataFlag = 0;
			continue;
		}
		gsTxPacket.u8DataLength = gu8SCIData[0];
	}
	else if (gu8SCIRx_i <= gsTxPacket.u8DataLength)
	{	//Empfang der CAN-Telegramm-Daten
		gau8TxDataBuffer[gu8SCIRx_i-1] = gu8SCIData[0];
	}
	else if (gu8SCIRx_i == gsTxPacket.u8DataLength + 1)
	{	//Empfang des Stoppbytes
		valid = (gu8SCIData[0] == 0x7E) ? 1 : 0;
		//Ende der Übertragung
		gi8AppStatus = TRANSMIT_DATA;
		gu8SCIRx_i = -1;
		LED4 ^= 1;
	}
	gu8SCIRx_i++;
	gu8SCIDataFlag = 0;
}