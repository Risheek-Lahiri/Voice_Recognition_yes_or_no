// Yes_No_classifier.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	FILE *fp = fopen("ys2.txt", "r");
	
	if (fp==NULL)
        printf("This file is not available");
    else
    {
	
		char mystring[150];		

		int i=0;				

		double zcr[2400]={0};	
		double xi[2]={0};		
		double max=0;			
		double dat=0;			
	
		int set=0;
		int count=0;			
		double dc_sum=0;		

		while(!feof(fp))		
		{
			for(i=0;i<100;i++)	
			{
				fgets(mystring, 150, fp);
				if(feof(fp)) break;			

				dat=atoi(mystring);			
											

				count++;					
				dc_sum += dat;				

				xi[1]=dat;					
											

				if( (xi[0]>=0 && xi[1]<0) || (xi[0]<0 && xi[1]>=0) )	
					zcr[set]++;

				xi[0]=xi[1];				

				if(abs(dat)>max)			
					max=abs(dat);
			}
			set++;							

			xi[0]=0;						
			xi[1]=0;
		}

		double dc_shift = dc_sum/count;

		rewind(fp);							

		double energy[2400]={0};			
		double e_sum=0;						

		set=0;
		while(!feof(fp))
		{
			for(i=0;i<100;i++)
			{
				fgets(mystring, 150, fp);
				if(feof(fp)) break;

				dat = atoi(mystring);

				dat -= dc_shift;			
				dat *= 5000/max;			

				e_sum += (dat*dat);
			}

			energy[set] = e_sum/i;			//energy = avg of squares of amplitude
			
			e_sum=0;						
			set++;
		}
		
		double threshold = 0;	//energy threshold = avg of first 25 sets

		for(i=0;i<25;i++)
			threshold += energy[i];

		threshold /= 25;

		int start=0,end=0;

		i=0;
		while(i<count)
		{
			if(energy[i]>threshold*5)		
			{
				start=i;					
				break;
			}
			i++;
		}
		while(1)
		{
			if(energy[i]<threshold*5)		
			{
				end = --i;					
				break;
			}
			i++;
		}

		if(start==0 || end==0)				
		{
			printf("No word found.");
			return 0;
		}

		printf("The word starts at: %d and ends at: %d\n",start,end);

		

		int zcr_avg=0;						

		for(i=end;i>(end-40);i--)
			zcr_avg+=zcr[i];

		zcr_avg /= 40;
		

		if(zcr_avg>40)						
			printf("The word is YES.");
		else
			printf("The word is NO.");
	}

	system("PAUSE");						

	return 0;
}
