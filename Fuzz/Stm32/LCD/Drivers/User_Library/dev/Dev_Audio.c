#include "Dev_Audio.h"
#include "Biquad.h"
#include "Op_HeaderVariable.h"
#include "Filter_reverb.h"
#include "Effect_Chorus.h"

int16_t RecordBuffer[RECORD_BUFFER_SIZE];
int16_t PlaybackBuffer[RECORD_BUFFER_SIZE];
volatile BUFFER_StateTypeDef  audio_rec_buffer_state;
volatile uint32_t  audio_tx_buffer_state = 0;

extern SAI_HandleTypeDef haudio_out_sai, haudio_in_sai;
static AUDIO_DrvTypeDef  *audio_drv;

static void SAIx_In_Init(uint32_t AudioFreq);
static void SAI_AUDIO_IN_MspInit(SAI_HandleTypeDef *hsai, void *Params);
static void SAIx_In_DeInit(void);
static void CopyChannel(int16_t * pData);
static void ApplyEffect(int16_t * pData);
static uint8_t BSP_AUDIO_IN_OUT_Init(uint32_t AudioFreq);
static uint8_t _BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size);

void get_max_val(int16_t *buf, uint32_t size, int16_t amp[]);
static void CopyBuffer(int16_t *pbuffer1, int16_t *pbuffer2, uint16_t BufferSize);
/*--- Test low pass ---*/
float gain = 8.37111;
float filter_alpha = 0.05;
int16_t data_temp = 0;

/*---------------------*/
void Dev_AudioInit(void)
{
	BSP_AUDIO_IN_Init(BSP_AUDIO_FREQUENCY_44K, DEFAULT_AUDIO_IN_BIT_RESOLUTION, DEFAULT_AUDIO_IN_CHANNEL_NBR);
	BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, DEFAULT_VOL, BSP_AUDIO_FREQUENCY_44K);
	/* Initialize Audio Recorder with 4 channels to be used */
	if (BSP_AUDIO_IN_OUT_Init(BSP_AUDIO_FREQUENCY_44K) == AUDIO_OK)
	{
	
	} 
	else 
	{
		
	}
	/* Start Recording */
	HAL_StatusTypeDef res = HAL_SAI_Receive_DMA(&haudio_in_sai, (uint8_t*)RecordBuffer, RECORD_BUFFER_SIZE);
	if (HAL_OK == res)
	{

	} else {

	}

	/* Play the recorded buffer */
	if (_BSP_AUDIO_OUT_Play((uint16_t *) &PlaybackBuffer[0], RECORD_BUFFER_SIZE) == AUDIO_OK)
	{

	} 
	else 
	{

	}

	audio_rec_buffer_state = BUFFER_OFFSET_NONE;
}

void Dev_AudioHandler(void)
{
	/* 1st or 2nd half of the record buffer ready for being copied
	to the Playback buffer */
	if (audio_rec_buffer_state != BUFFER_OFFSET_NONE)
	{
		 /* Copy half of the record buffer to the playback buffer */
		 if (audio_rec_buffer_state == BUFFER_OFFSET_HALF)
		 {
				ApplyEffect(RecordBuffer);
				//CopyChannel(RecordBuffer);
			 
			 	if(APPLY_CHORUS_FLAG == C_ON)
				{
					Effect_ChorusProcess(RecordBuffer, RecordBuffer, (RECORD_BUFFER_SIZE / 2), audio_rec_buffer_state);
				}
				CopyBuffer(&PlaybackBuffer[0], &RecordBuffer[0], RECORD_BUFFER_SIZE / 2);
		 } 
		 else 
		 {
				ApplyEffect(RecordBuffer);
				//CopyChannel(RecordBuffer);
			 
			  if(APPLY_CHORUS_FLAG == C_ON)
				{
					Effect_ChorusProcess(&RecordBuffer[RECORD_BUFFER_SIZE / 2], &RecordBuffer[RECORD_BUFFER_SIZE / 2], (RECORD_BUFFER_SIZE / 2), audio_rec_buffer_state);
				}
				
				CopyBuffer(&PlaybackBuffer[RECORD_BUFFER_SIZE / 2], &RecordBuffer[RECORD_BUFFER_SIZE / 2], RECORD_BUFFER_SIZE / 2);
		 }
		 /* Wait for next data */
		 audio_rec_buffer_state = BUFFER_OFFSET_NONE;
	}
	if (audio_tx_buffer_state)
	{
		 audio_tx_buffer_state = 0;
	}
}

static void ApplyEffect(int16_t * pData)
{
	float sum = 0;
	if(audio_rec_buffer_state == BUFFER_OFFSET_HALF)
	{
		for(uint16_t i = 0 ; i < RECORD_BUFFER_SIZE / 2 ; i+=2)
		{
			sum = (float)(pData[i] + pData[i+1]);
			sum = bq_process(bq, sum);
						
			if(APPLY_REVERS_FLAG == C_ON)
			{
				sum = (1.0f-g_wlSetWet)*sum + g_wlSetWet*Do_Reverb(sum);
			}
			
			pData[i] = (int)sum;
			pData[i+1] = pData[i];
		}
	}
	else if(audio_rec_buffer_state == BUFFER_OFFSET_FULL)
	{
		for(uint16_t i = 0 ; i < RECORD_BUFFER_SIZE / 2 ; i+=2)
		{
			sum = (float)(pData[(RECORD_BUFFER_SIZE / 2) + i] + pData[(RECORD_BUFFER_SIZE / 2) + i+1]);
			sum = bq_process(bq, sum);
			
			if(APPLY_REVERS_FLAG == C_ON)
			{
				sum = (1.0f-g_wlSetWet)*sum + g_wlSetWet*Do_Reverb(sum);
			}
			
			pData[(RECORD_BUFFER_SIZE / 2)+ i] = (int)sum;
			pData[(RECORD_BUFFER_SIZE / 2)+ i+1] = pData[(RECORD_BUFFER_SIZE / 2) + i];
		}
	}
}

static void CopyChannel(int16_t * pData)
{
	float sum = 0;
	if(audio_rec_buffer_state == BUFFER_OFFSET_HALF)
	{
		for(uint16_t i = 0 ; i < RECORD_BUFFER_SIZE / 2 ; i+=2)
		{
			sum = (float)(pData[i] + pData[i+1]);
			sum = bq_process(bq, sum);
			
			//sum = (1.0f-g_wlSetWet)*sum + g_wlSetWet*Do_Reverb(sum);
			
			pData[i] = (int)sum;
			pData[i+1] = pData[i];
			
			//data_temp = pData[i] * gain;
			//pData[i] = filter_alpha * data_temp + (1.0 - filter_alpha) * pData[i];
		}
	}
	else if(audio_rec_buffer_state == BUFFER_OFFSET_FULL)
	{
		for(uint16_t i = 0 ; i < RECORD_BUFFER_SIZE / 2 ; i+=2)
		{
			sum = (float)(pData[(RECORD_BUFFER_SIZE / 2) + i] + pData[(RECORD_BUFFER_SIZE / 2) + i+1]);
			sum = bq_process(bq, sum);
			
			//sum = (1.0f-g_wlSetWet)*sum + g_wlSetWet*Do_Reverb(sum);
			
			pData[(RECORD_BUFFER_SIZE / 2)+ i] = (int)sum;
			pData[(RECORD_BUFFER_SIZE / 2)+ i+1] = pData[(RECORD_BUFFER_SIZE / 2) + i];
			//pData[(RECORD_BUFFER_SIZE / 2) + i] = bq_process(bq, pData[(RECORD_BUFFER_SIZE / 2) + i]);
			//data_temp = pData[(RECORD_BUFFER_SIZE / 2) + i] * gain;
			//pData[(RECORD_BUFFER_SIZE / 2) + i] = filter_alpha * data_temp + (1.0 - filter_alpha) * pData[(RECORD_BUFFER_SIZE / 2) + i];
		}
	}
}

void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
	audio_rec_buffer_state = BUFFER_OFFSET_FULL;
}

void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{ 
	audio_rec_buffer_state = BUFFER_OFFSET_HALF;
}



static void SAIx_In_Init(uint32_t AudioFreq)
{
	 /* Initialize SAI1 block A in MASTER TX */
	 /* Initialize the haudio_out_sai Instance parameter */
	 haudio_out_sai.Instance = AUDIO_OUT_SAIx;

	 /* Disable SAI peripheral to allow access to SAI internal registers */
	 __HAL_SAI_DISABLE(&haudio_out_sai);

	 /* Configure SAI_Block_x */
	 haudio_out_sai.Init.MonoStereoMode = SAI_STEREOMODE;
	 haudio_out_sai.Init.AudioFrequency = AudioFreq;
	 haudio_out_sai.Init.AudioMode      = SAI_MODEMASTER_TX;
	 haudio_out_sai.Init.NoDivider      = SAI_MASTERDIVIDER_ENABLE;
	 haudio_out_sai.Init.Protocol       = SAI_FREE_PROTOCOL;
	 haudio_out_sai.Init.DataSize       = SAI_DATASIZE_16;
	 haudio_out_sai.Init.FirstBit       = SAI_FIRSTBIT_MSB;
	 haudio_out_sai.Init.ClockStrobing  = SAI_CLOCKSTROBING_FALLINGEDGE;
	 haudio_out_sai.Init.Synchro        = SAI_ASYNCHRONOUS;
	 haudio_out_sai.Init.OutputDrive    = SAI_OUTPUTDRIVE_ENABLE;
	 haudio_out_sai.Init.FIFOThreshold  = SAI_FIFOTHRESHOLD_1QF;
	 haudio_out_sai.Init.SynchroExt     = SAI_SYNCEXT_DISABLE;
	 haudio_out_sai.Init.CompandingMode = SAI_NOCOMPANDING;
	 haudio_out_sai.Init.TriState       = SAI_OUTPUT_NOTRELEASED;
	 haudio_out_sai.Init.Mckdiv         = 0;

	 /* Configure SAI_Block_x Frame */
	 haudio_out_sai.FrameInit.FrameLength       = 64;
	 haudio_out_sai.FrameInit.ActiveFrameLength = 32;
	 haudio_out_sai.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
	 haudio_out_sai.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
	 haudio_out_sai.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

	 /* Configure SAI Block_x Slot */
	 haudio_out_sai.SlotInit.FirstBitOffset = 0;
	 haudio_out_sai.SlotInit.SlotSize       = SAI_SLOTSIZE_DATASIZE;
	 haudio_out_sai.SlotInit.SlotNumber     = 4;
	 haudio_out_sai.SlotInit.SlotActive     = CODEC_AUDIOFRAME_SLOT_0123;

	 HAL_SAI_Init(&haudio_out_sai);



	 /* Initialize SAI1 block B in SLAVE RX synchronous from SAI1 block A */
	 /* Initialize the haudio_in_sai Instance parameter */
	 haudio_in_sai.Instance = AUDIO_IN_SAIx;

	 /* Disable SAI peripheral to allow access to SAI internal registers */
	 __HAL_SAI_DISABLE(&haudio_in_sai);

	 /* Configure SAI_Block_x */
	 haudio_in_sai.Init.MonoStereoMode = SAI_STEREOMODE;
	 haudio_in_sai.Init.AudioFrequency = AudioFreq;
	 haudio_in_sai.Init.AudioMode      = SAI_MODESLAVE_RX;
	 haudio_in_sai.Init.NoDivider      = SAI_MASTERDIVIDER_ENABLE;
	 haudio_in_sai.Init.Protocol       = SAI_FREE_PROTOCOL;
	 haudio_in_sai.Init.DataSize       = SAI_DATASIZE_16;
	 haudio_in_sai.Init.FirstBit       = SAI_FIRSTBIT_MSB;
	 haudio_in_sai.Init.ClockStrobing  = SAI_CLOCKSTROBING_FALLINGEDGE;
	 haudio_in_sai.Init.Synchro        = SAI_SYNCHRONOUS;
	 haudio_in_sai.Init.OutputDrive    = SAI_OUTPUTDRIVE_DISABLE;
	 haudio_in_sai.Init.FIFOThreshold  = SAI_FIFOTHRESHOLD_1QF;
	 haudio_in_sai.Init.SynchroExt     = SAI_SYNCEXT_DISABLE;
	 haudio_in_sai.Init.CompandingMode = SAI_NOCOMPANDING;
	 haudio_in_sai.Init.TriState       = SAI_OUTPUT_RELEASED;
	 haudio_in_sai.Init.Mckdiv         = 0;

	 /* Configure SAI_Block_x Frame */
	 haudio_in_sai.FrameInit.FrameLength       = 64;
	 haudio_in_sai.FrameInit.ActiveFrameLength = 32;
	 haudio_in_sai.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
	 haudio_in_sai.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
	 haudio_in_sai.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

	 /* Configure SAI Block_x Slot */
	 haudio_in_sai.SlotInit.FirstBitOffset = 0;
	 haudio_in_sai.SlotInit.SlotSize       = SAI_SLOTSIZE_DATASIZE;
	 haudio_in_sai.SlotInit.SlotNumber     = 4;
	 haudio_in_sai.SlotInit.SlotActive     = CODEC_AUDIOFRAME_SLOT_0123;

	 HAL_SAI_Init(&haudio_in_sai);

	 /* Enable SAI peripheral */
	 __HAL_SAI_ENABLE(&haudio_in_sai);

	 /* Enable SAI peripheral to generate MCLK */
	 __HAL_SAI_ENABLE(&haudio_out_sai);
}

static void SAI_AUDIO_IN_MspInit(SAI_HandleTypeDef *hsai, void *Params)
{
	 static DMA_HandleTypeDef hdma_sai_rx;
	 GPIO_InitTypeDef  gpio_init_structure;

	 /* Enable SAI clock */
	 AUDIO_IN_SAIx_CLK_ENABLE();

	 /* Enable SD GPIO clock */
	 AUDIO_IN_SAIx_SD_ENABLE();
	 /* CODEC_SAI pin configuration: SD pin */
	 gpio_init_structure.Pin = AUDIO_IN_SAIx_SD_PIN;
	 gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	 gpio_init_structure.Pull = GPIO_NOPULL;
	 gpio_init_structure.Speed = GPIO_SPEED_FAST;
	 gpio_init_structure.Alternate = AUDIO_IN_SAIx_AF;
	 HAL_GPIO_Init(AUDIO_IN_SAIx_SD_GPIO_PORT, &gpio_init_structure);

	 /* Enable Audio INT GPIO clock */
	 AUDIO_IN_INT_GPIO_ENABLE();
	 /* Audio INT pin configuration: input */
	 gpio_init_structure.Pin = AUDIO_IN_INT_GPIO_PIN;
	 gpio_init_structure.Mode = GPIO_MODE_INPUT;
	 gpio_init_structure.Pull = GPIO_NOPULL;
	 gpio_init_structure.Speed = GPIO_SPEED_FAST;
	 HAL_GPIO_Init(AUDIO_IN_INT_GPIO_PORT, &gpio_init_structure);

	 /* Enable the DMA clock */
	 AUDIO_IN_SAIx_DMAx_CLK_ENABLE();

	 if (hsai->Instance == AUDIO_IN_SAIx)
	 {
			 /* Configure the hdma_sai_rx handle parameters */
			 hdma_sai_rx.Init.Channel             = AUDIO_IN_SAIx_DMAx_CHANNEL;
			 hdma_sai_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
			 hdma_sai_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
			 hdma_sai_rx.Init.MemInc              = DMA_MINC_ENABLE;
			 hdma_sai_rx.Init.PeriphDataAlignment = AUDIO_IN_SAIx_DMAx_PERIPH_DATA_SIZE;
			 hdma_sai_rx.Init.MemDataAlignment    = AUDIO_IN_SAIx_DMAx_MEM_DATA_SIZE;
			 hdma_sai_rx.Init.Mode                = DMA_CIRCULAR;
			 hdma_sai_rx.Init.Priority            = DMA_PRIORITY_HIGH;
			 hdma_sai_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
			 hdma_sai_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
			 hdma_sai_rx.Init.MemBurst            = DMA_MBURST_SINGLE;
			 hdma_sai_rx.Init.PeriphBurst         = DMA_MBURST_SINGLE;

			 hdma_sai_rx.Instance = AUDIO_IN_SAIx_DMAx_STREAM;

			 /* Associate the DMA handle */
			 __HAL_LINKDMA(hsai, hdmarx, hdma_sai_rx);

			 /* Deinitialize the Stream for new transfer */
			 HAL_DMA_DeInit(&hdma_sai_rx);

			 /* Configure the DMA Stream */
			 HAL_DMA_Init(&hdma_sai_rx);
	 }

	 /* SAI DMA IRQ Channel configuration */
	 HAL_NVIC_SetPriority(AUDIO_IN_SAIx_DMAx_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
	 HAL_NVIC_EnableIRQ(AUDIO_IN_SAIx_DMAx_IRQ);

	 /* Audio INT IRQ Channel configuration */
	 HAL_NVIC_SetPriority(AUDIO_IN_INT_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
	 HAL_NVIC_EnableIRQ(AUDIO_IN_INT_IRQ);
}

static void SAIx_In_DeInit(void)
{
	 /* Initialize the haudio_in_sai Instance parameter */
	 haudio_in_sai.Instance = AUDIO_IN_SAIx;
	 haudio_out_sai.Instance = AUDIO_OUT_SAIx;
	 /* Disable SAI peripheral */
	 __HAL_SAI_DISABLE(&haudio_in_sai);

	 HAL_SAI_DeInit(&haudio_in_sai);
	 HAL_SAI_DeInit(&haudio_out_sai);
}

static uint8_t BSP_AUDIO_IN_OUT_Init(uint32_t AudioFreq)
{
	 uint8_t ret = AUDIO_ERROR;

	 /* Disable SAI */
	 SAIx_In_DeInit();

	 /* PLL clock is set depending by the AudioFreq (44.1khz vs 48khz groups) */
	 BSP_AUDIO_OUT_ClockConfig(&haudio_in_sai, AudioFreq, NULL);
	 haudio_out_sai.Instance = AUDIO_OUT_SAIx;
	 haudio_in_sai.Instance = AUDIO_IN_SAIx;
	 if (HAL_SAI_GetState(&haudio_in_sai) == HAL_SAI_STATE_RESET)
	 {
			 BSP_AUDIO_OUT_MspInit(&haudio_out_sai, NULL);
			 SAI_AUDIO_IN_MspInit(&haudio_in_sai, NULL);
	 }


	 SAIx_In_Init(AudioFreq); // inclu déja le code de SAIx_Out_Init()


	 if ((wm8994_drv.ReadID(AUDIO_I2C_ADDRESS)) == WM8994_ID)
	 {
			 /* Reset the Codec Registers */
			 wm8994_drv.Reset(AUDIO_I2C_ADDRESS);
			 /* Initialize the audio driver structure */
			 audio_drv = &wm8994_drv;
			 ret = AUDIO_OK;
	 } else {
			 ret = AUDIO_ERROR;
	 }

	 if (ret == AUDIO_OK)
	 {
			 /* Initialize the codec internal registers */
			 audio_drv->Init(AUDIO_I2C_ADDRESS, INPUT_DEVICE_ANALOG_MIC | OUTPUT_DEVICE_HEADPHONE , 100, AudioFreq);
	 }

	 /* Return AUDIO_OK when all operations are correctly done */
	 return ret;
}

static uint8_t _BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size)
{
	 /* Call the audio Codec Play function */
	 if (audio_drv->Play(AUDIO_I2C_ADDRESS, (uint16_t *)pBuffer, Size) != 0)
	 {
			 return AUDIO_ERROR;
	 }
	 else
	 {
			 /* Update the Media layer and enable it for play */
			 if (HAL_SAI_Transmit_DMA(&haudio_out_sai, (uint8_t*) pBuffer, Size) !=  HAL_OK)
			 {
					 return AUDIO_ERROR;
			 }
			 return AUDIO_OK;
	 }
}


void get_max_val(int16_t *buf, uint32_t size, int16_t amp[])
{
	 int16_t maxval[4] = { -32768, -32768, -32768, -32768};
	 uint32_t idx;
	 for (idx = 0 ; idx < size ; idx += 4) {
			 if (buf[idx] > maxval[0])
					 maxval[0] = buf[idx];
			 if (buf[idx + 1] > maxval[1])
					 maxval[1] = buf[idx + 1];
			 if (buf[idx + 2] > maxval[2])
					 maxval[2] = buf[idx + 2];
			 if (buf[idx + 3] > maxval[3])
					 maxval[3] = buf[idx + 3];
	 }
	 memcpy(amp, maxval, sizeof(maxval));
}
static void CopyBuffer(int16_t *pbuffer1, int16_t *pbuffer2, uint16_t BufferSize)
{
	 uint32_t i = 0;
	 for (i = 0; i < BufferSize; i++)
	 {
			 pbuffer1[i] = pbuffer2[i];
	 }
}
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
	 audio_tx_buffer_state = 1;
}
