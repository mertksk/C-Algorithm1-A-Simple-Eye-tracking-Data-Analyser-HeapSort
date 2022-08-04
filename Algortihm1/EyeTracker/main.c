#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* I could not handle some input parts because 
when i get the path as string input all the time
the compiler gave an error.This is the only functionality that 
does not work correctly.


*/

/*AOI struct*/
struct AOI{
	
	char name[150];
	int topleftx;
	int width;
	int toplefty;
	int height;
	int fixationIncrement=0;
	int dwellTime=0;
	
};
/*function list*/
void heapify(int Parent , AOI arr[] , int size,int sortingCriteria);
void buildHeap(AOI x[],int size,int sortingCriteria);
void printAOIs(AOI arr[],int size);
void heapSort(AOI arr[],int sortingCriteria,int size);
void computeDwellTime(AOI arr[],int size,char path[350]);
void computeFixationCount(AOI arr[],int size,char path[350]);


/*main function*/
int main(){

	
	char eyeAnalyser[300]; //1st Input is okay
	int sortingCriteria; // 2th Input is okay
	
	char param[350];
	struct AOI aois[500];
	
	printf("------------------\n");
	printf("WELCOME:\n");
	printf("------------------\n");
	printf("Please Enter The Name of Program:");
	scanf("%s",eyeAnalyser);
	printf("\n------------------\n\n");
	/*Initial AOI upload*/
	FILE *file;
	file = fopen("C:\\Users\\mert_\\OneDrive\\Masaüstü\\algoritma\\testdata\\aois.txt", "r");
	char a[150];
	int x=0;
	int y=0;
	int z=0;
	int c=0;
	int size=0;
  
  //Initial loads of AOIs
	while(!feof(file)){
	
		
		fscanf (file, "%s %d %d %d %d", a, &x, &y, &z,&c);

   		strcpy(aois[size].name,a);
   		aois[size].topleftx=x;
   		aois[size].width=y;
   		aois[size].toplefty=z;
   		aois[size].height=c;
   			
		size++;   
	}
	fclose(file);		//close the file
	
	
	// Initial load of User Data
	strcpy(param,"C:\\Users\\mert_\\OneDrive\\Masaüstü\\algoritma\\testdata\\data\\1.txt");
	computeFixationCount(aois,size,param);
	computeDwellTime(aois,size,param);
	strcpy(param,"C:\\Users\\mert_\\OneDrive\\Masaüstü\\algoritma\\testdata\\data\\2.txt");
	computeFixationCount(aois,size,param);
	computeDwellTime(aois,size,param);
	strcpy(param,"C:\\Users\\mert_\\OneDrive\\Masaüstü\\algoritma\\testdata\\data\\3.txt");
	computeFixationCount(aois,size,param);
	computeDwellTime(aois,size,param);
	printf("FILES UPLOADED");
	printf("\n-------------------------------");
	printf("\nWhat is your Sorting Criteria?\n1)Fixation Count\n2)Dwell Time\nAnswer:");
	scanf("%d",&sortingCriteria);

	
	heapSort(aois, sortingCriteria, size);

	printAOIs(aois,size);
	
	
	return 0;
}

//Heapify Function
void heapify(int Parent , AOI arr[] , int size,int sortingCriteria){
	


	AOI temp1,temp2;
	int Left=Parent*2+1;
	int Right=Parent*2+2;
	int largest;
	//printf("\n\n1)Parent: %d Right: %d Left: %d\n\n",arr[Parent],arr[Right],arr[Left]);
	
	if(sortingCriteria==1){

	if(arr[Left].fixationIncrement>arr[Parent].fixationIncrement && Left<=size-1 ){
		largest=Left;

	}
	else{
		largest=Parent;

	}
	if(arr[Right].fixationIncrement>arr[largest].fixationIncrement && Right<=size-1){
		largest=Right;
	
	}
	
	if(largest != Parent){
		/*Swap operation*/
		temp1=arr[Parent];
		arr[Parent]=arr[largest];
		arr[largest]=temp1;
	
		
		heapify(largest,arr,size,1);
	}	}
	else if(sortingCriteria==2){
	
		if(arr[Left].dwellTime>arr[Parent].dwellTime && Left<=size-1 ){
			largest=Left;
	
		}
		else{
			largest=Parent;
	
		}
		if(arr[Right].dwellTime>arr[largest].dwellTime && Right<=size-1){
			largest=Right;
		
		}
		
		if(largest != Parent){
			/*Swap operation*/
			temp1=arr[Parent];
			arr[Parent]=arr[largest];
			arr[largest]=temp1;
		
			
			heapify(largest,arr,size,2);
		}	}

}

/*Build Heap Function*/
void buildHeap(AOI x[],int size,int sortingCriteria){
	
	int stop=0;
	int hold=size;
	
	for(int i=size/2;i!=stop;i--){
		heapify(i-1,x,size,sortingCriteria);
		
	}
	
	
	
}

/*Print Function for All AOIs*/
void printAOIs(AOI arr[],int size){
		
	   	printf("\nAOI | Fixation-count | Dwell-time\n");
	   	size--;
	   	while(size!=-1){
			printf ("%s    %d times    %d ms\n", arr[size].name,arr[size].fixationIncrement,arr[size].dwellTime);
			size--;

}
}
/*Heap Sort Function*/
void heapSort(AOI arr[],int sortingCriteria,int size){
	AOI temp;
	buildHeap(arr,size,sortingCriteria);
	
	for(int i=size-1;i!=0;i--){

		temp=arr[i];
		arr[i]=arr[0];
		arr[0]=temp;
		heapify(0,arr,i-1,sortingCriteria);

}
	
}	
	
/*Dwell Time Adder*/
void computeDwellTime(AOI arr[],int size,char path[350]){
	
	FILE *file;
	file = fopen(path, "r");
	int temp;
	char dummy[4][150];
	int activeLow=0;
	int index;
	int x;
	int y;
	int duration;
	
	while(!feof(file)){
		temp=size;
		if(activeLow==0){
			fscanf (file, "%s %s %s %s", &dummy[0],&dummy[1],&dummy[2],&dummy[3]);
	  		activeLow++;
			continue;
			
		}
		
		fscanf (file, "%d %d %d %d", &index,&x,&y,&duration);
		
		while(temp!=-1){
	
			if((x>=arr[temp].topleftx and x<=arr[temp].topleftx+arr[temp].width ) and (y>=arr[temp].toplefty and y<=arr[temp].toplefty+arr[temp].height)){
				arr[temp].dwellTime=arr[temp].dwellTime+duration;
					}
			temp--;
		}
	
		

	}
	fclose(file);
}

/*Fixation Time Adder*/
void computeFixationCount(AOI arr[],int size,char path[350]){
	//Reads any.txt
	FILE *file;
	file = fopen(path, "r");
	int temp;
	char dummy[4][150];
	int activeLow=0;
	int index;
	int x;
	int y;
	int duration;
	
	while(!feof(file)){
		temp=size;
		if(activeLow==0){
			fscanf (file, "%s %s %s %s", &dummy[0],&dummy[1],&dummy[2],&dummy[3]);
			activeLow++;
			continue;
			
		}
		
		fscanf (file, "%d %d %d %d", &index,&x,&y,&duration);
		
		while(temp!=-1){
	
			if((x>=arr[temp-1].topleftx and x<=arr[temp-1].topleftx+arr[temp-1].width ) and (y>=arr[temp-1].toplefty and y<=arr[temp-1].toplefty+arr[temp-1].height)){
				arr[temp-1].fixationIncrement++;
		
					}
			temp--;
		}
	
		


	}
	fclose(file);		//close the file
}
