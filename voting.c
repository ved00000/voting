#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 200

struct candid{
	char cnames[MAXLEN];
}; candidates[MAXLEN];

struct profile{
	char profLine[MAXLEN];
}; lines[MAXLEN];

struct list{
	char votediD[MAXLEN];
	char regisiD[MAXLEN];
	char admsiD[MAXLEN];
}; idList[MAXLEN];

struct tally{
	int score[MAXLEN];
}; votes[MAXLEN];

int main(){
	//variables
	FILE *candi, *receipt, *vlist, *reg, *rlist, *tally, *admns;
	/*Register*/
		/*ID Generator*/ int lower = 1, upper = 1000000;
		/*List of Registered IDs*/ struct list regisiD[MAXLEN];
		/*Name*/ char fname[MAXLEN], lname[MAXLEN], mname[MAXLEN];
		/*Address*/	char street[MAXLEN], zone[MAXLEN], barangay[MAXLEN], municipal[MAXLEN], province[MAXLEN]; 
		/*Other Info*/ char gender[MAXLEN], email[MAXLEN], cpno[MAXLEN], profile[MAXLEN], birthday[MAXLEN];
	/*Vote*/
		/*Name Extension*/ char reci[MAXLEN];
		/*Printing the Registered Profile*/ struct profile lines[MAXLEN];
		/*List of Voted IDs*/ struct list idList[MAXLEN];
	/*Admin*/
		/*Name Extension*/ char adm[MAXLEN];
		/*New Admin ID*/  char addm[MAXLEN];
		/*Struct*/ struct list admsiD[MAXLEN];
		char dfa = "admin_00001";
	/*Candidates*/
		/*Struct*/ struct candid candidates[MAXLEN];
		/*Candidates*/ char candidate[MAXLEN];
	/*Tally*/
		/*Struct*/ struct tally votes[MAXLEN];
	/*Loops*/
		/*Counters*/ int i, voted, numOfVoters, numOfrVoters, num, didnotVote, numOfCandidates, numOfAdmns;
		/*Switch*/ char opt, opt1;
	
	while(opt != EOF){
		
		printf("Services:\n\tA. Register");
		printf("\n\tB. Login");
		printf("\n\tC. Exit");
		printf("\n\t\tChoice: ");
		scanf("%s", &opt);
		printf("\n");
		
		switch (opt){
			case 'A': /*Voting Registration*/
			case 'a':{
				
				printf("\tRegistration\n");
			
				/*Getting the Personal Information*/
				printf("\t\tEnter First Name: "); scanf(" %[^\n]%*c", fname);
    			printf("\t\tEnter Middle Name: "); scanf(" %[^\n]%*c", mname);
   				printf("\t\tEnter Last Name: "); scanf(" %[^\n]%*c", lname);
  				printf("\t\tAddress:\n");{
  					printf("\t\t\tZone Number: "); scanf("%s", zone);
 		 			printf("\t\t\tStreet: "); scanf(" %[^\n]%*c", street);
  					printf("\t\t\tBarangay: "); scanf(" %[^\n]%*c", barangay);
		  			printf("\t\t\tMunicipal: "); scanf(" %[^\n]%*c", municipal);
  					printf("\t\t\tProvince: "); scanf(" %[^\n]%*c", province);
					}
  				printf("\t\tGender: "); scanf("%s", gender);
 		 		printf("\t\tBirthday (MM/DD/YYYY): "); scanf(" %[^\n]%*c", birthday);
 		 		printf("\t\tCellphone Number: "); scanf("%s", cpno);
  				printf("\t\tPersonal Email: "); scanf("%s", email);
  			
  				/*Generate Random ID*/
  				srand(time(0));
  				num = (rand() % (upper - lower + 1)) + lower;
     		   	sprintf(profile, "%d", num);
				printf("\n\t\tYour Voters ID is: %s", profile);
   			
   				/*Putting the ID at the Registered List*/
   				rlist = fopen("registered id list.txt", "r");
				if(rlist == NULL){
					rlist = fopen("registered id list.txt", "w");
					fprintf(rlist,"%d\n%s - %s, %s, %s", numOfrVoters+1, profile, &lname, &fname, &mname);
					}
				else{
					fscanf(rlist, "%d", &numOfrVoters);
  					for(i = 0; i < numOfrVoters; i++){
   						fscanf(rlist, " %[^\n]%*c", &idList[i].regisiD);
						}
					fscanf(rlist, "%d", &numOfrVoters);
					rlist = fopen("registered id list.txt", "w");
					fprintf(rlist, "%d\n", numOfrVoters+1);
					for(i = 0; i < numOfrVoters; i++){
   						fprintf(rlist, "%s\n", &idList[i].regisiD);
						}
					fprintf(rlist, "%s - %s, %s, %s", &profile, &lname, &fname, &mname);
					}
   			
   				/*Creating Profile*/
    			reg = fopen(profile, "w");
  				fprintf(reg, "Name: %s, %s, %s", &lname, &fname, &mname);
    			fprintf(reg, "\nAddress: Zone %s. %s St. %s, %s, %s", &zone, &street, &barangay, &municipal, &province);
   		 		fprintf(reg, "\nGender: %s", &gender);
   				fprintf(reg, "\nBirthday: %s", &birthday);
    			fprintf(reg, "\nCellphone Number: %s", &cpno);
   				fprintf(reg, "\nPresonal Email: %s", &email);
				
   				/*Checking if Profile is Successfully Created*/
   				reg = fopen(profile, "r");
    			if (reg == NULL){
					printf("\tFailed to Register.\n");
					}
				else{
   					printf("\n\t\tRegistration is Complete.");
   					printf("\n\t\tPlease Don't Forget Your Voters Number!\n");
					}
			
				fclose(reg);
				fclose(rlist);
				return 0;
				}
			
			case 'B': /*Login*/
			case 'b':{
				
				printf("\tEnter ID: ");
    			scanf("%s", profile);
				
				/*IF ADMIN OR NOT*/
				strcpy(adm, "admin_");
				strcat(adm, profile);
				admns = fopen("admin list.txt", "r");
  				fscanf(admns, "%d", &numOfAdmns);
  				for(i = 0; i < numOfAdmns; i++){
   					fscanf(admns, " %[^\n]%*c", &idList[i].admsiD);
   					if(strcmp(adm, idList[i].admsiD) == 0){
  						 
  						/*ADMIN OPTIONS*/
					   	printf("\n\tWELCOME ADMIN!\n");

					   	while (opt1 != EOF){
   							printf("\t\tA. Assign Candidates");
							printf("\n\t\tB. Show Candidates");
							printf("\n\t\tC. Tally");
							printf("\n\t\tD. List of Registered ID's");
							printf("\n\t\tE. Search Profile");
							printf("\n\t\tF. Assign Additional Admin");
							printf("\n\t\tG. Exit");
							printf("\n\t\t\tChoice: ");
							scanf("%s", &opt1);
						
							switch(opt1){
								case 'A': /*Assign Candidates*/
								case 'a':{
									printf("\n\t\tAssigning New Candidates will Automatically Reset the Votes! You've Been Warned!\n");
									/*Presidential*/
									printf("\n\t\t\tPresidential Candidates: ");
									printf("\n\t\t\tHow many candidates do you want to add? ");
									scanf("%d", &numOfCandidates);
										
									candi = fopen("pcandidates.txt", "w");
									tally = fopen("ptally.txt", "w");
									fprintf(candi, "%d\n", numOfCandidates);
									for(i = 0; i < numOfCandidates; i++){
										printf("\t\t\t\tCandidate No.%i: ", i+1);
										scanf(" %[^\n]%*c", &candidate[i]);
										fprintf(candi, "%s\n", &candidate[i]);
										fprintf(tally, "0\n", &candidate[i]);
										}
									fclose(candi);
				
									/*Checking if Candidates are Successfully Assigned*/
									candi = fopen("pcandidates.txt", "r");
   									 if (candi == NULL){
										printf("\n\t\t\t\tAssigning Failed.\n\n");
										break;
										}
									else{
   										printf("\n\t\t\t\tCandidates Successfully Assigned.\n");
										}
			
									/*Vice Presidential*/
									printf("\n\t\t\tVice Presidential Candidates: ");
									printf("\n\t\t\tHow many candidates do you want to add? ");
									scanf("%d", &numOfCandidates);
				
									candi = fopen("vpcandidates.txt", "w");
									tally = fopen("vptally.txt", "w");
									fprintf(candi, "%d\n", numOfCandidates);
									for(i = 0; i < numOfCandidates; i++){
										printf("\t\t\t\tCandidate No.%i: ", i+1);
										scanf(" %[^\n]%*c", &candidate[i]);
										fprintf(candi, "%s\n", &candidate[i]);
										fprintf(tally, "0\n");
										}
									fclose(candi);
				
									candi = fopen("vpcandidates.txt", "r");
   									 if (candi == NULL){
										printf("\n\t\t\t\tAssigning Failed.\n\n");
										break;
										}
									else{
   										printf("\n\t\t\t\tCandidates Successfully Assigned.\n");
										}
									fclose(candi);
									printf("\n\t\t\tSenatorial Candidates: ");
									printf("\n\t\t\tHow many candidates do you want to add? ");
									scanf("%d", &numOfCandidates);
			
									/*Senatorial*/
									candi = fopen("scandidates.txt", "w");
									tally = fopen("stally.txt", "w");
									fprintf(candi, "%d\n", numOfCandidates);
									for(i = 0; i < numOfCandidates; i++){
										printf("\t\t\t\tCandidate No.%i: ", i+1);
										scanf(" %[^\n]%*c", &candidate[i]);
										fprintf(candi, "%s\n", &candidate[i]);
										fprintf(tally, "0\n");
										}
									fclose(candi);
				
									/*Checking if Candidates are Successfully Assigned*/
									candi = fopen("scandidates.txt", "r");
   									 if (candi == NULL){
										printf("\n\t\t\t\tAssigning Failed.\n\n");
										break;
										}
									else{
   										printf("\n\t\t\t\tCandidates Successfully Assigned.\n");
										}
			
									fclose(tally);
									fclose(candi);
									return 0;
									}
					
								case 'B': /*Show Candidates*/
								case 'b':{
									/*Presidential*/
									candi = fopen("pcandidates.txt", "r");
									printf("\n\t\t\tPresidential Candidates: ");
		   							if (candi == NULL){
		   								printf("\n\t\t\t\tThere are no assigned candidates.\n");
										}
									else{
										fscanf(candi, "%d", &numOfCandidates);
   										for(i = 0; i < numOfCandidates; i++){
   											fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
											printf("\n\t\t\t\t%d. %s", i+1, &candidates[i].cnames);
											}
										printf("\n");
										}
										
									/*Vice Presidential*/
									candi = fopen("vpcandidates.txt", "r");
									printf("\n\t\t\tVice Presidential Candidates: ");
		  						 	if (candi == NULL){
		   								printf("\n\t\t\t\tThere are no assigned candidates.\n");
										}
									else{
										fscanf(candi, "%d", &numOfCandidates);
   										for(i = 0; i < numOfCandidates; i++){
   											fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
											printf("\n\t\t\t\t%d. %s", i+1, &candidates[i].cnames);
											}
									printf("\n");
										}
			
									/*Senatorial*/
									candi = fopen("scandidates.txt", "r");
									printf("\n\t\t\tSenatorial Candidates: ");
		   							if (candi == NULL){
		   								printf("\n\t\t\t\tThere are no assigned candidates.\n");
										}
									else{
										fscanf(candi, "%d", &numOfCandidates);
   										for(i = 0; i < numOfCandidates; i++){
   											fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
											printf("\n\t\t\t\t%d. %s", i+1, &candidates[i].cnames);
											}
										printf("\n");
										}
				
									fclose(candi);
									break;
									}
					
								case 'C': /*Tally*/
								case 'c':{
									/*Searching for Candidates and Votes*/
									candi = fopen("pcandidates.txt", "r");
   									if (candi == NULL){
										printf("\n\t\t\t\tThere are No Votes to Display.\n\n");
										break;
										}
									printf("\n\t\t\tPresidential Tally: ");
									fscanf(candi, "%d", &numOfCandidates);	
									for(i = 0; i < numOfCandidates; i++){
   										fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
										}
									tally = fopen("ptally.txt","r");
									for(i = 0; i < numOfCandidates; i++){
										fscanf(tally, "%s", &votes[i].score[i]);
										}
									/*Printing*/
									printf("\n");
									for(i = 0; i < numOfCandidates; i++){
										printf("\t\t\t\t%s Voted for %s\n", &votes[i].score[i], &candidates[i].cnames);
										}
									
									printf("\n\t\t\tVice Presidential Tally: ");
									candi = fopen("vpcandidates.txt", "r");
   									if (candi == NULL){
										printf("\n\t\tThere are No Votes to Display.\n\n");
										break;
										}
									fscanf(candi, "%d", &numOfCandidates);	
									for(i = 0; i < numOfCandidates; i++){
   										fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
										}
									tally = fopen("vptally.txt","r");
									for(i = 0; i < numOfCandidates; i++){
										fscanf(tally, "%s", &votes[i].score[i]);
										}
									/*Printing*/
									printf("\n");
									for(i = 0; i < numOfCandidates; i++){
										printf("\t\t\t\t%s Voted for %s\n", &votes[i].score[i], &candidates[i].cnames);
										}
									
									printf("\n\t\t\tSenatorial Tally: ");
									candi = fopen("scandidates.txt", "r");
   									if (candi == NULL){
										printf("\n\t\tThere are No Votes to Display.\n\n");
										break;
										}
									fscanf(candi, "%d", &numOfCandidates);	
									for(i = 0; i < numOfCandidates; i++){
   										fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
										}
									tally = fopen("stally.txt","r");
									for(i = 0; i < numOfCandidates; i++){
										fscanf(tally, "%s", &votes[i].score[i]);
										}
									/*Printing*/
									printf("\n");
									for(i = 0; i < numOfCandidates; i++){
										printf("\t\t\t\t%s Voted for %s\n", &votes[i].score[i], &candidates[i].cnames);
										}
									
									vlist = fopen("voted id list.txt", "r");
  									fscanf(vlist, "%d", &numOfVoters);
									printf("\n\t\t\t\tCast Their Votes: %d", numOfVoters);
									rlist = fopen("registered id list.txt", "r");
  									fscanf(rlist, "%d", &numOfrVoters);
  									printf("\n\t\t\t\tTotal Number of Registered Voters: %d", numOfrVoters);
  						
  									didnotVote = numOfrVoters - numOfVoters;
  									printf("\n\t\t\t\tDidn't Cast Their Votes: %d\n\n", didnotVote);
			
									fclose(tally);
									fclose(vlist);
									fclose(rlist);
									break;
									}
									
								case 'D': /*Registered ID's*/
								case 'd':{
									/*Printing the Registered ID's*/
									rlist = fopen("registered id list.txt", "r");
		    						if (rlist == NULL){
		    							printf("\n\t\t\tThere are NO Registered ID's.\n");
										}
									else{
										printf("\n\t\tRegistered ID's:");
										fscanf(rlist, "%d", &numOfrVoters);
   										for(i = 0; i < numOfrVoters; i++){
   											fscanf(rlist, " %[^\n]%*c", &idList[i].regisiD);
											printf("\n\t\t\t%s", idList[i].regisiD);
											}
										}
									printf("\n");
									fclose(rlist);
									break;
									}				
						
								case 'E': /*Print Profile*/
								case 'e':{

									printf("\n\t\tEnter Voters ID: ");
    								scanf("%s", profile);
    						
    								/*Printing*/
    								reg = fopen(profile, "r");
    								if (reg == NULL){
										printf("\n\t\t\t'%s' Profile is not currently registered.\n", profile);
										break;
										}
									else{
										for(i = 0; i < 6 ; i++){
   											fscanf(reg, " %[^\n]%*c", &lines[i].profLine);
											printf("\n\t\t\t%s", lines[i].profLine);
											}
										}
								
									printf("\n");
									break;
									}
								
								case 'F': /*Assign Additional Admin*/
								case 'f':{
									if (strcmp(adm, idList[0].admsiD) == dfa){
										printf("\n\t\t\tEnter New Admin ID: ");
										scanf("%s", &addm);
										
										admns = fopen("admin list.txt", "r");
										fscanf(admns, "%d", &numOfAdmns);
  										for(i = 0; i < numOfAdmns; i++){
   											fscanf(admns, " %[^\n]%*c", &idList[i].admsiD);
											}
										fscanf(admns, "%d", &numOfAdmns);
										admns = fopen("admin list.txt", "w");
										fprintf(admns, "%d\n", numOfAdmns+1);
										for(i = 0; i < numOfAdmns; i++){
   											fprintf(admns, "%s\n", &idList[i].admsiD);
											}
										strcpy(adm, "admin_");
										strcat(adm, addm);
										fprintf(admns, "%s\n", &adm);
										printf("\n\t\t\tNew Admin Successfully Assigned!");
										return 0;
										}
									else{
										printf("\n\t\t\tYou Don't Have the Rights to Assign New Admin!\n");
										break;
										}
							 		}
							 		
								case 'G': /*Exit*/
								case 'g':{
									
									printf("\n\t\t\tTHANK YOU FOR USING OUR SERVICES!");
									return 0;
									}	
															
								default:
									printf("\n\t\t\t'%c' - Invalid Character\n\n", opt1);
									
								}
							printf("\n");
			  				}
						}
					}
				
				/*Checking if the ID is already in the Voted ID LIst*/
    			vlist = fopen("voted id list.txt", "r");
  				fscanf(vlist, "%d", &numOfVoters);
  				for(i = 0; i < numOfVoters; i++){
   					fscanf(vlist, " %[^\n]%*c", &idList[i].votediD);
   					if(strcmp(profile, idList[i].votediD) == 0){
   						printf("\n\t\tYou Already Voted!");
   						printf("\n\t\tProgram will end automatically to Preserve the Integrity of this Election.\n\t\tThank you for understanding.\n");
   						return 0;
			  			}
					}
				
				/*Checking if the ID is registered or not*/
				reg = fopen(profile, "r");
				if (reg == NULL){
					printf("\t\t'%s' Profile is not currently registered.\n", profile);
					printf("\t\tRegister first and try again later.\n\n");
					break;
					}
				else{
  					for(i = 0; i < 6 ; i++){
   						fscanf(reg, " %[^\n]%*c", &lines[i].profLine);
						printf("\n\t%s", lines[i].profLine);
						}
					}
				
				/*Printing the Candidates*/
				candi = fopen("pcandidates.txt", "r");
			   	if (candi == NULL){
			    	printf("\n\n\t\tThere are no assigned candidates!\n\n");
			    	break;
					}
				else{
					fscanf(candi, "%d", &numOfCandidates);
					printf("\n\n\tPresidential Candidates:");
   					for(i = 0; i < numOfCandidates; i++){
   						fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
						printf("\n\t\t%d. %s", i+1, candidates[i].cnames);
						}
					}
				printf("\n\n\tVote for: ");
				scanf("%d", &voted);
				printf("\t\tVoted for %d. %s\n", voted, candidates[voted-1].cnames);
			
				/*Tallying*/
				tally = fopen("ptally.txt","r");
				for(i = 0; i < numOfCandidates; i++){
					fscanf(tally, "%s", &votes[i].score[i]);
					}
				tally = fopen("ptally.txt","w");
				for(i = 0; i < numOfCandidates; i++){
					if(i == voted-1){
						(votes[i].score[i])++;
						}
					fprintf(tally,"%s\n", &votes[i].score[i]);
					}
					
				/*Printing the Receipt*/
				strcpy(reci, "receipt_");
				strcat(reci, profile);
				receipt = fopen(reci, "w");
				for(i = 0; i < 6 ; i++){
   					fscanf(reg, " %[^\n]%*c", &lines[i].profLine);
					fprintf(receipt,"%s\n", lines[i].profLine);
					}
				fprintf(receipt,"\n\tPresidential: Voted for %d. %s", voted, candidates[voted-1].cnames);
				
				candi = fopen("vpcandidates.txt", "r");
			   	if (candi == NULL){
			    	printf("\n\n\t\tThere are no assigned candidates!\n\n");
			    	break;
					}
				else{
					fscanf(candi, "%d", &numOfCandidates);
					printf("\n\n\tVice Presidential Candidates:");
   					for(i = 0; i < numOfCandidates; i++){
   						fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
						printf("\n\t\t%d. %s", i+1, candidates[i].cnames);
						}
					}
				printf("\n\n\tVote for: ");
				scanf("%d", &voted);
				printf("\t\tVoted for %d. %s\n", voted, candidates[voted-1].cnames);
				fprintf(receipt,"\n\tVice Presidential: Voted for %d. %s", voted, candidates[voted-1].cnames);
			
				/*Tallying*/
				tally = fopen("vptally.txt","r");
				for(i = 0; i < numOfCandidates; i++){
					fscanf(tally, "%s", &votes[i].score[i]);
					}
				tally = fopen("vptally.txt","w");
				for(i = 0; i < numOfCandidates; i++){
					if(i == voted-1){
						(votes[i].score[i])++;
						}
					fprintf(tally,"%s\n", &votes[i].score[i]);
					}
				
				candi = fopen("scandidates.txt", "r");
			   	if (candi == NULL){
			    	printf("\n\n\t\tThere are no assigned candidates!\n\n");
			    	break;
					}
				else{
					fscanf(candi, "%d", &numOfCandidates);
					printf("\n\n\tSenatorial Candidates:");
   					for(i = 0; i < numOfCandidates; i++){
   						fscanf(candi, " %[^\n]%*c", &candidates[i].cnames);
						printf("\n\t\t%d. %s", i+1, candidates[i].cnames);
						}
					}
				printf("\n\n\tVote for: ");
				scanf("%d", &voted);
				printf("\t\tVoted for %d. %s\n", voted, candidates[voted-1].cnames);
			
				/*Tallying*/
				tally = fopen("stally.txt","r");
				for(i = 0; i < numOfCandidates; i++){
					fscanf(tally, "%s", &votes[i].score[i]);
					}
				tally = fopen("stally.txt","w");
				for(i = 0; i < numOfCandidates; i++){
					if(i == voted-1){
						(votes[i].score[i])++;
						}
					fprintf(tally,"%s\n", &votes[i].score[i]);
					}
				fprintf(receipt,"\n\tSenatorial: Voted for %d. %s", voted, candidates[voted-1].cnames);
			
				/*Putting the ID in the List*/
				vlist = fopen("voted id list.txt", "r");
				if(vlist == NULL){
					vlist = fopen("voted id list.txt", "w");
					fprintf(vlist,"%d\n%s", numOfVoters+1, profile);
					}
				else{
					fscanf(vlist, "%d", &numOfVoters);
  					for(i = 0; i < numOfVoters; i++){
   						fscanf(vlist, " %[^\n]%*c", &idList[i].votediD);
						}
					fscanf(vlist, "%d", &numOfVoters);
					vlist = fopen("voted id list.txt", "w");
					fprintf(vlist, "%d\n", numOfVoters+1);
					for(i = 0; i < numOfVoters; i++){
   						fprintf(vlist, "%s\n", &idList[i].votediD);
						}
					fprintf(vlist, "%s", &profile);
					}
				printf("\n\tYour Vote has been Cast, Print Your Reciept with a file name: reciept_(VOTERS ID)!\n\tTHANK YOU!\n");
			
				fclose(reg);
				fclose(candi);
				fclose(tally);
				fclose(receipt);
				fclose(vlist);
			
				return 0;
				}
			
			case 'C': /*Exit*/
			case 'c':{
				printf("\t\tTHANK YOU FOR USING OUR SERVICES!");
				return 0;
				}
			
			default: printf("\t\t'%c' - Invalid Character\n\n", opt);
				
			}
		}
	
	return 0;	
	}
	
	
