// CSE 20211
//
// Nicholas LaRosa
//
// Lab #9
//
// travel.c
//
// This program allows the user to create an itinerary of flights
// throughout the course of a single day
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define INITIAL 100		// we will begin with 100 elements in our array

struct flight				// structure to hold individual flight information
{
	char origin[4];
	char destination[4];
	int departure;
	int arrival;
	int cost;
};

typedef struct flight Flight;		// create a type for our flight structures

int timeToInt(char timeString[])					// returns the raw time string in integer format for easier use
{
	int i;
	int j;
	int size = strlen(timeString);
	int currentExp = size - 2;					// the position of each number will be based on powers of 10
	int currentTime = 0;						// keep current count of the time
	int currentDigit;						// get each digit from the character array
	int currentPower = 1;						// we will multiply the current digit by this to place correctly

	for( i = 0; i < size; i++ )
	{
		if( timeString[i] != ':' )
		{
			currentDigit = timeString[i] - 48;		// conversion from ASCII to integer

			for( j = 0; j < currentExp; j++ )		// raise 10 to the "currentExp" power
			{
				currentPower *= 10;
			}

			currentTime = currentTime + (currentDigit * currentPower);
			currentPower = 1;
			currentExp--;
		}
	}
		
	return currentTime;						// returns an integer that will allow for time comparison
}

void timeToString(int timeInt, char stringHolder[])			// returns the time integer in string format for printing
{
	int i;
	int measure;
	int currentExp;				// this will store the power of ten currently being examined (decimal place)
	int mayContinue = 0;			// this boolean tells us when we have added a colon to the string

	if( timeInt >= 1000 )
	{ 		
		measure = 6;			// store the size of the future string, which includes a colon	
		currentExp = 1000;		
	}
	else
	{	
		measure = 5;		
		currentExp = 100;
	}

	const int size = measure;
	char ourString[size];						// this will hold the final time string

	for( i = 0; i < size; i++ )
	{
		if( i == size - 1)					// the last character must be a null character
		{
			ourString[i] = '\0';
		}
		else if( currentExp != 10 || mayContinue )		// when the exponent is 10, we know that a colon is needed
		{
			ourString[i] = (char)(((timeInt % (currentExp*10)) / currentExp)+48);
			currentExp /= 10;				// conversion to ASCII value
		}
		else
		{
			ourString[i] = ':';
			mayContinue = 1;
		}
	}

	strcpy(stringHolder, ourString);				// replace the string given with the final time string
}

int costToInt(char costString[])					// returns the raw cost string in integer format for easier use
{
	int i;
	int j;
	int size = strlen(costString);
	int currentExp = size - 2;					// the position of each number will be based on powers of 10
	int currentCost = 0;						// keep current count of the cost
	int currentDigit;						// get each digit from the character array
	int currentPower = 1;						// we will multiply the current digit by this to place correctly

	for( i = 0; i < size; i++ )
	{
		if( costString[i] != '$' )
		{
			currentDigit = costString[i] - 48;		// conversion from ASCII to integer

			for( j = 0; j < currentExp; j++ )		// raise 10 to the "currentExp" power
			{
				currentPower *= 10;
			}

			currentCost = currentCost + (currentDigit * currentPower);
			currentPower = 1;
			currentExp--;
		}
	}
		
	return currentCost;						// returns an integer that will allow for time comparison
}

void costToString(int costInt, char stringHolder[])			// returns the time integer in string format for printing
{
	int i;
	int measure;
	int currentExp;				// this will store the power of ten currently being examined (decimal place)

	if( costInt >= 1000 )
	{
		measure = 6;
		currentExp = 1000;
	}
	else if( costInt >= 100 )		// we will assume the tickets are between $0 and $9999
	{ 		
		measure = 5;			// store the size of the future string, which includes a colon	
		currentExp = 100;		
	}
	else
	{	
		measure = 4;		
		currentExp = 10;
	}

	const int size = measure;
	char ourString[size];						// this will hold the final time string

	ourString[0] = '$';						// we will add the dollar sign right away

	for( i = 1; i < size; i++ )
	{
		if( i == size - 1)					// the last character must be a null character
		{
			ourString[i] = '\0';
		}
		else							// we know a dollar sign is needed at the first position
		{
			ourString[i] = (char)(((costInt % (currentExp*10)) / currentExp)+48);
			currentExp /= 10;				// conversion to ASCII value
		}
	}

	strcpy(stringHolder, ourString);				// replace the string given with the final time string
}

Flight getFlight(char currentString[])					// organizes a string of flight information into a structure
{
	Flight tempFlight;
	
	char originT[4];						// each piece of information is originally a string
	char destinationT[4];
	char departureT[6];
	char arrivalT[6];
	char costT[6];

	sscanf(currentString, "%s %s %s %s %s", originT, destinationT, departureT, arrivalT, costT);
									
	strcpy(tempFlight.origin, originT);				// after picking out individual information from the string using sscanf...
	strcpy(tempFlight.destination, destinationT);			// store each piece of information in its respective place in the structure
	tempFlight.departure = timeToInt(departureT);
	tempFlight.arrival = timeToInt(arrivalT);
	tempFlight.cost = costToInt(costT);					
	
	return tempFlight;						// this flight structure contains all the corresponding information
}

void printFlight(Flight flightArray[], int ourIndex)			// prints the flight at the specified index from the specified array
{
	char originT[4];
	char destinationT[4];
	char departureT[6];
	char arrivalT[6];
	char costT[6];

	strcpy(originT, flightArray[ourIndex].origin);			// use string copy for information already in string format	
	strcpy(destinationT, flightArray[ourIndex].destination);	
	timeToString(flightArray[ourIndex].departure, departureT);	// store each string in temporary arrays
	timeToString(flightArray[ourIndex].arrival, arrivalT);
	costToString(flightArray[ourIndex].cost, costT);

	printf("(%d)	%s		%s		%s		%s		%s\n", ourIndex, originT, destinationT, departureT, arrivalT, costT);
}	

void printFlights(Flight flightArray[], int size)			// prints an array of flights with labeled columns
{
	int i;
	
	printf("\n	Origin		Destination	Departure	Arrival		Cost\n\n");

	for( i = 0; i < size; i++ )
	{
		printFlight(flightArray, i);
	}

	printf("\n");
}

void copyFlight(Flight *target, Flight original)			// puts the contents of original into the target
{									// so we are basically modifying the target array (by reference)
	strcpy( target -> origin, original.origin);		
	strcpy( target -> destination, original.destination);
	target -> departure = original.departure;
	target -> arrival = original.arrival;
	target -> cost = original.cost;
}

int readFile(Flight arrayFlights[], char fileName[], int size)		// stores file contents in provided array
{									// and returns the number of flights stored
	char buffer[4096];
	int index = 0;

	FILE *ourFile = fopen(fileName, "r");
	
	if( ourFile == NULL )		return 0;			// file could not be opened, return 0 stored lines

	while( fgets(buffer, sizeof(buffer), ourFile) != NULL )
	{
		copyFlight( &arrayFlights[index], getFlight(buffer) );	// puts flight structure generated from this current string into array
		index++;

		//printf("%s\n", buffer);		

		/*
		if( index == size )					// when we have reached the end of the current array
		{							// add more space with realloc
			arrayFlights = realloc( arrayFlights, (size+INCR)*sizeof(Flight) );
			size += INCR;
		}
		*/
	}

	fclose(ourFile);

	return size;
}

int countFlights(Flight arrayFlights[], int size, char userOrigin[4])	// counts the number of flights that match the user's criteria
{
	int i;
        int count = 0;

        for( i = 0; i < size; i++ )
        {
                if( strcmp(arrayFlights[i].origin, userOrigin) == 0 )
                {
                        count++;
                }
        }

	return count;
}

Flight *findFlights(Flight arrayFlights[], int size, int count, char userOrigin[] )		// finds the flights within the array Flights that share the same
{												// origin and leave at the time specified (given user preference)
	int i;
	int subIndex = 0;

	Flight *subArray = malloc(count*sizeof(Flight));		// this array will hold all of the flights that meet requirements

	for( i = 0; i < size; i++ )
	{
		if( strcmp(arrayFlights[i].origin, userOrigin) == 0 )
		{
			copyFlight( &subArray[subIndex], arrayFlights[i] );		// again find all flights, this time storing them in new array
			subIndex++;
		}
	}

	return subArray;
}	

int countOptions(Flight arrayFlights[], Flight chosenOne, int size)		// find all flights leaving from destination of chosen flight
{										// and that leave later than the arrival time of chosen flight
	int i;
	int timeOut = chosenOne.arrival;		// hold the arrival time that next flight must leave after
	char optionOrigin[4];				// hold the destination airport	that next flight must leave
	int count = 0;

	strcpy( optionOrigin, chosenOne.destination );

	for( i = 0; i < size; i++ )
	{
		if( strcmp(arrayFlights[i].origin, optionOrigin) == 0 && arrayFlights[i].departure >= timeOut )
		{
			count++;	
		}
	}

	return count;
} 

Flight *findOptions(Flight arrayFlights[], Flight chosenOne, int size, int count)	// finds the flights within the array that would be available
{											// given a specific first flight chosen by the user
        int i;
        int subIndex = 0;
	int timeOut = chosenOne.arrival;                // hold the arrival time that next flight must leave after
        char optionOrigin[4];                           // hold the destination airport that next flight must leave

	strcpy( optionOrigin, chosenOne.destination );

        Flight *subArray = malloc(count*sizeof(Flight));                // this array will hold all of the flights that meet requirements

        for( i = 0; i < size; i++ )
        {
                if( strcmp(arrayFlights[i].origin, optionOrigin) == 0 && arrayFlights[i].departure >= timeOut )
                {
                        copyFlight( &subArray[subIndex], arrayFlights[i] );             // again find all flights, this time storing them in new array
                	subIndex++;
		}
        }

        return subArray;
}

int airportExists(Flight arrayFlights[], int size, char userAirport[])		// returns boolean true if array contains a flight from the specified airport
{
	int i;
	
	for( i = 0; i < size; i++ )
	{
		if( strcmp(arrayFlights[i].origin, userAirport) == 0 )
		{
			return 1;
		}
	}

	return 0;							// return false if there were no occurences
}	

void getAirport(Flight arrayFlights[], int size, char storeChoice[])		// ends only if user enters a valid airport, stores choice 
{			
	int i;									// in the provided array storeChoice
	int length;
	char tempString[100];	

	printf("\nPlease enter your origin airport's three-character code: ");

	if( scanf("%s", tempString) == 1 )					// got correct input (string), continue
	{
		length = strlen(tempString);

		if( length != 3 )
		{
			printf("That is not a three-character code. Please try again.\n");
			while ( getchar() != '\n' );
			getAirport(arrayFlights, size, storeChoice);
		}
		else
		{
			for( i = 0; i < length; i++ )
			{
				tempString[i] = toupper(tempString[i]);
			}

			if( !airportExists(arrayFlights, size, tempString) )				// the specified airport does not exist
			{
				printf("This airport does not exist. Please try again.\n");
				while ( getchar() != '\n' );
				getAirport(arrayFlights, size, storeChoice);
			}
			else
			{
				strcpy( storeChoice, tempString );					// we have checked for errors, now store final choice
				while ( getchar() != '\n' );
				return;
			}
		}
	}
	else
	{
		printf("This is not a three-character code. Please try again.\n");
		while ( getchar() != '\n' );
		getAirport(arrayFlights, size, storeChoice);
	}
}

void buildItinerary(Flight currentItin[], int sizeI)
{
	int i;
	int totalCost = 0;
	FILE *writeF = fopen("itinerary.txt", "w");
	
	if( writeF == NULL )
	{
		printf("File cannot be opened for writing.\n");
		return;
	}

	char originT[4];
        char destinationT[4];
        char departureT[6];
        char arrivalT[6];
        char costT[6];

	fprintf(writeF, "\nThe LaRosa Travel Agency Presents...\n");
	fprintf(writeF, "\n\tYour Itinerary:\n\n");
	fprintf(writeF, "\tOrigin\t\tDestination\tDeparture\tArrival\t\tCost\n\n");

	for( i = 0; i < sizeI; i++ )
	{
        	strcpy(originT, currentItin[i].origin);                  	// use string copy for information already in string format
        	strcpy(destinationT, currentItin[i].destination);
        	timeToString(currentItin[i].departure, departureT);      	// store each string in temporary arrays
       		timeToString(currentItin[i].arrival, arrivalT);
        	costToString(currentItin[i].cost, costT);

	        fprintf(writeF, "\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", originT, destinationT, departureT, arrivalT, costT);
	
		totalCost = totalCost + currentItin[i].cost;
	}
	
	fprintf(writeF, "\n\tTotal Cost: $%d\n\n", totalCost);
	fclose(writeF);	

	printf("Your itinerary has been printed to 'itinerary.txt'\n\n");
	return;
}
	
void getFirstChoice(Flight arrayFlights[], int size, Flight currentItin[]);

void getNextChoice(Flight arrayFlights[], int size, Flight currentItin[], int sizeI, Flight userChoice)	
{										// this function takes in the user's last choice, generates a list of options
	char tempString[100];							// and asks for the next user input
	int i;	
	int inputSize;
	int count;
	Flight *optionList;

	count = countOptions(arrayFlights, userChoice, size);			// this is the number of options available to the user
	
	if( count == 0 )
	{
		printf("There are no available flights from %s on the same day. Ending session...\n", userChoice.destination);
		buildItinerary(currentItin, sizeI);
		return;
	} 

	optionList = findOptions(arrayFlights, userChoice, size, count);	
	printFlights( optionList, count );

	printf("Please select your next flight out of the options listed.\nOtherwise, build your itinerary with 'end'");
	printf(" or replace previous selected flight with 'cancel': ");
	
	if( scanf("%s", tempString) == 1 )
	{
		inputSize = strlen(tempString);

		if( inputSize != 1 && inputSize != 3 && inputSize != 6 )
		{
			printf("You have not entered a valid command.\n");
			while ( getchar() != '\n' );
			getNextChoice(arrayFlights, size, currentItin, sizeI, userChoice);
		}
		else	
		{
			if( inputSize == 1 )
			{
				copyFlight(&currentItin[sizeI], optionList[tempString[0]-48]);				// conversion from ASCII to integer
				getNextChoice(arrayFlights, size, currentItin, sizeI+1, optionList[tempString[0]-48]);	// recursively get options
			}
			for( i = 0; i < size; i++ )
			{
				tempString[i] = tolower(tempString[i]);		// convert string to lower case for easier comparison
			}
			if( strcmp( tempString, "cancel" ) == 0 )		// restart if user cancels
			{
				if( sizeI == 1 )	getFirstChoice(arrayFlights, size, currentItin);
				else			getNextChoice(arrayFlights, size, currentItin, sizeI-1, currentItin[sizeI-2]);
			}
			else if( strcmp( tempString, "end" ) == 0 )		// build itinerary if user ends
			{
				buildItinerary(currentItin, sizeI);
			}
		}
	}
}

void getFirstChoice(Flight arrayFlights[], int size, Flight currentItin[])	// takes user-defined airport and makes first call to getNextChoice
{
	char userChoice[4];
	int userIndex;
	int count;
	Flight *optionList;							// this will contain our list of flight options

	getAirport(arrayFlights, size, userChoice);				// first get the airport, then we will prepare list of options

	count = countFlights(arrayFlights, size, userChoice);			// count the number of options the user will have after specifying airport
	optionList = findFlights(arrayFlights, size, count, userChoice);	// obtain a pointer to an array of flight options

	printf("\nAvailable flights:\n");	
	printFlights( optionList, count );
	
	printf("Please select your first flight by index: ");
	scanf("%d", &userIndex);

	copyFlight( &currentItin[0], optionList[userIndex] );			// add this selected indexed element to our array of flights

	getNextChoice(arrayFlights, size, currentItin, 1, optionList[userIndex]);	// initial size of our itinerary (guaranteed to select one flight)
}

int main(void)
{
	char fileName[] = "flights.txt";
	int size = INITIAL;
	Flight *flights = malloc(INITIAL*sizeof(Flight));				
	Flight *itinerary = malloc(INITIAL*sizeof(Flight));

	if( !readFile(flights, fileName, size) )
	{
		printf("File 'flights.txt' not present in current directory.\n");
		return 1;
	}
	
	getFirstChoice(flights, size, itinerary);

	free(flights);
	
	return 0;
}

