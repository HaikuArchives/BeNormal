//BeNormal - Noramlises WAV files
//Copyright(C) 2000 David Burnett
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "BeNormal.h"

int main(int argc, char *argv[])
{

	FILE *fWav;
	char *pData, *pDataStart, *pDataEnd;
	short iMaxValue;
	double dFactor;
	short *pTemp;
	long iRead;
 	struct stat input_fstat;


	typedef struct
	{   
	    char            RiffID[4];
        u_long          RiffSize;
        char            WaveID[4];
        char            FmtID[4];
        u_long          FmtSize;
        u_short         wFormatTag;
        u_short         nChannels;
        u_long          nSamplesPerSec;
        u_long          nAvgBytesPerSec;
        u_short         nBlockAlign;
        u_short         wBitsPerSample;
        char            DataID[4];
        u_long          nDataBytes;
	} WAVE_HEADER;


	if((fWav = fopen(argv[1],"rb" )) == NULL )
	{
		printf("Failed to open %s", argv[1]);
		return(99);
	}

	fstat(fileno(fWav),&input_fstat);
	pData = (char *)malloc(input_fstat.st_size);
	
	iRead = fread(pData, 1, input_fstat.st_size, fWav);		
	WAVE_HEADER *wheader = (WAVE_HEADER *)pData;

   if (strncmp(wheader->RiffID,"RIFF",4) != 0)
   {
         printf(".wav header dont have RIFF\n");
   }

   /* if (verbose) printf("RiffSize is %ld\n",wheader->RiffSize); */

   /* next 4 bytes should be WAVE */
   if (strncmp(wheader->WaveID,"WAVE",4) != 0)
   {
      printf("header dont have WAVE\n");
   }          

   /* next 4 bytes should be "fmt " */
   if (strncmp(wheader->FmtID,"fmt ",4) != 0)
   {
         printf("header dont have fmt\n");
   }           

   if (wheader->FmtSize != 16)
   {
         printf("this program only deals with 16 bit audio data\n");
   }

   if (wheader->wFormatTag != 1)
   {
         printf("This wav is not PCM, we cant deal with it\n");
   }

   if (wheader->nChannels != 2)
   {
          printf("Presently we only deal with two channels, this has %d\n",
             wheader->nChannels);
   }        
   if (wheader->nSamplesPerSec != 44100)
   {
         printf("Presently we only deal with 44100 hz, this has %ld\n",
            wheader->nSamplesPerSec);
   }  

   /* next 4 bytes should be "data" */
   if (strncmp(wheader->DataID,"data",4) != 0)
   {
	printf("header dont have data\n");
   }           

	pDataEnd = pData + input_fstat.st_size;
	pDataStart = pData + 44;  // add on the header size
	iMaxValue = 0;
	
	for(pTemp = (short *)pDataStart; pTemp < (short *)pDataEnd; pTemp++)
	{
		if (abs(*pTemp) > iMaxValue)
		{
			iMaxValue = *pTemp; 
		} 
	}

	dFactor = 0.5 * ((double)SHRT_MAX / iMaxValue);
	if (dFactor != 0.5)
	{
		fwrite("wav file needs normalising\n", 28, 1, stderr);
		for(pTemp = (short *)pDataStart; pTemp < (short *)pDataEnd; pTemp++)
		{
//			*pTemp *=  dFactor;
			*pTemp = (int)((double)*pTemp * dFactor);
		}
	}
	else
	{
		fwrite("wav file already equivalent to normalised\n", 42, 1, stderr);
	}

	fwrite(pData, input_fstat.st_size, 1, stdout);

//	iRead = 20;
//	while(!feof(stdin))
//	{
//		iRead = fread(pData, 1, 20, stdin);	
//		printf("%ld-%s\n", iRead, pData);
//	}
}
