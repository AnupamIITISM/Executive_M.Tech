/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<math.h>

int main()
{
	int f,choice1,choice2;
	float d,At,Ar,tag,rag,Ldb;
	printf("\n*****=====Free Space Loss Calculations=====*****");
	printf("\n[User Input] Enter frequency of transmitted signal(in GHz) : "); scanf("%d",&f);
	printf("\n[User Input] Amount of distance to be covered (in KMs) ? : "); scanf("%f",&d);
	printf("\n[User Choice] Choose from the below mentioned options to calculate the free space loss : "); 
	printf("\n1- Without considering transmitting and receiving antennas.\t2 - Considering antennas.");
	printf("\n[User Choice] Choose : ");
	scanf("%d",&choice1);
	switch(choice1){
		case 1:
			Ldb = (20*log10(f*pow(10,9)))+(20*log10(d*pow(10,3)))-147.56;
			printf("\n[User Output] The free space loss in the given parameters is : %f dbW",Ldb);
			break;
		case 2:
			printf("\n[User Choice] Choose from the below mentioned options : "); 
			printf("\n1- Know antenna gains.\t2 - Know effective areas of antennas."); 
			printf("\n[User Choice] Choose : ");
			scanf("%d",&choice2);
			switch(choice2){
				case 1:
					printf("\n[User Input] Transmitting antenna's gain(in dbW) ? : ");scanf("%f",&tag);
					printf("\n[User Input] Receiving antenna's gain(in dbW) ? : ");scanf("%f",&rag);
					Ldb = ((20*log10(f*pow(10,9)))+(20*log10(d*pow(10,3)))-147.56)-tag-rag;
					printf("\n[User Output] The free space loss in the given parameters is : %f dbW",Ldb);
					break;
				case 2:
					printf("\n[User Input] Transmitting antenna's effective area(in meters) ? : ");scanf("%f",&At);
					printf("\n[User Input] Receiving antenna's effective area(in meters) ? : ");scanf("%f",&Ar);
					Ldb = -(20*log10(f*pow(10,9)))+(20*log10(d*pow(10,3)))-(10*log10(At*Ar))+169.54;
					printf("\n[User Output] The free space loss in the given parameters is : %f dbW",Ldb);
					break;
				default:
					printf("\n[Warning] Invalid Choice!!!");
					break;
			}
			break;
		default:
			printf("\n[Warning] Invalid Choice!!!");
			break;
	}
	return 0;
}