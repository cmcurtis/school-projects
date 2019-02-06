#include <stdio.h>
int main () {
	double lengthInFeet, lengthInMeters, areaInFeet, areaInMeters;
	double volumeInFeet, volumeInMeters, volumeInLiters, volumeInGallons;
	double mass, weight, areaInAcres;
	printf("Enter a length in feet:\n");
	scanf("%lf", &lengthInFeet);
	lengthInMeters = lengthInFeet / 3.28084;
	
	printf("%lfmeters\n\n", lengthInMeters);
	
	areaInFeet = lengthInFeet * lengthInFeet;
	areaInMeters = lengthInMeters * lengthInMeters;
	areaInAcres = areaInFeet * 2.29568e-5;
	volumeInFeet = lengthInFeet * lengthInFeet * lengthInFeet;
	volumeInMeters = areaInMeters * lengthInMeters;
	volumeInLiters = volumeInMeters * 1000;
	volumeInGallons = volumeInFeet * 7.48052; 	
	mass = volumeInFeet * 28316.8467117;
	weight = mass * .00220462;

	printf("Area of square:\n");
	printf("%lf square feet\n", areaInFeet);
	printf("%lf square meters\n", areaInMeters);
	printf("%lf acres\n\n", areaInAcres);
	printf("Volume of a cube:\n");
	printf("%lf cubic feet\n", volumeInFeet);
	printf("%lf cubic meters\n", volumeInMeters);
	printf("%lf liters\n", volumeInLiters);
	printf("%lf gallons\n\n", volumeInGallons);
	printf("Mass of a cube of water:\n");
	printf("%lf grams\n\n", mass);
	printf("Weight of cube of water:\n");
	printf("%lf pounds\n", weight);
	return 0;
}

	
