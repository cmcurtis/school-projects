#include <stdio.h>
int main () {
	double x0 = 0.0, x1 = 0.0, x2 = 0.0, x3 = 0.0, x4 = 0.0, x5 = 0.0, x6 = 0.0, x7 = 0.0, x8 = 0.0, x9 = 0.0, y0 = 0.0, y1 = 0.0, y2 = 0.0, y3 = 0.0, y4 = 0.0, y5 = 0.0, y6 = 0.0, y7 = 0.0, z = 0.0;
	double sidingCost = 0.0, roofingCost = 0.0, deckCost = 0.0, applianceStyle = 0.0;
	double bathroomFlooring = 0.0, bedroomFlooring = 0.0, diningFlooring = 0.0, familyFlooring = 0.0;
	double foyerFlooring = 0.0, hallFlooring = 0.0, kitchenFlooring = 0.0, laundryFlooring = 0.0, livingFlooring = 0.0;
	double lotSize = 0.0, houseArea = 0.0, interiorArea = 0.0, interiorVolume = 0.0, exteriorWallLength = 0.0, exteriorWallArea = 0.0;
	double lotCost = 0.0, sitePrep = 0.0, foundationCost = 0.0, framingCost = 0.0, totalSidingCost = 0.0, totalRoofingCost = 0.0;
	double doorAndWindowsCost = 0.0, plumbingFixturesCost = 0.0, electricAndLightingCost = 0.0, heatAcCost = 0.0;
	double insulationCost = 0.0, drywallCost = 0.0, paintCost = 0.0, cabinentCost = 0.0, applianceCost = 0.0, totalFlooringCost = 0.0;
	double securityCost = 0.0, concreteCost = 0.0, totalDeckCost = 0.0, landscapingCost = 0.0, sprinklerCost = 0.0, subTotal = 0.0;
	double contractorCost = 0.0, total = 0.0;
	double deckArea = 0.0, patioArea = 0.0, bedroomArea = 0.0, bathroomArea = 0.0, diningArea = 0.0, familyArea = 0.0, foyerArea = 0.0;
	double hallArea = 0.0, kitchenArea = 0.0, laundryArea = 0.0, livingArea = 0.0, garageArea = 0.0, porchArea = 0.0, drivewayArea = 0.0;
	double sidewalkArea = 0.0, lawnArea = 0.0;


	scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &x0, &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8, &x9);
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &y0, &y1, &y2, &y3, &y4, &y5, &y6, &y7);
	scanf("%lf", &z);
	scanf("%lf", &sidingCost);
	scanf("%lf", &roofingCost);
	scanf("%lf", &deckCost);
	scanf("%lf", &applianceStyle);
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf", &bathroomFlooring, &bedroomFlooring, &diningFlooring, &familyFlooring, &foyerFlooring, &hallFlooring, &kitchenFlooring, &laundryFlooring, &livingFlooring); 

	deckArea = (x1 + x2 + x3) * y1;
	patioArea = (x5 + x6) * y1;
	bedroomArea = ((x1+x2+x3)*(y2+y3))+((x7+x8)*(y2+y3))+((x7+x8)*(y5+y6));
	bathroomArea = (x1 * y4) + (x8 * y4);
	laundryArea = x2 * y4;
	garageArea = (x1 + x2 + x3) * (y5 + y6);
	hallArea = (x3 * y4) + (x7 * y4);
	kitchenArea = x4 * (y2 + y3 + y4);
	diningArea = x4 * (y5 + y6);
	familyArea = (x5 + x6) * (y3 + y4);
	foyerArea = x5 * y5;
	livingArea = x6 * (y5 + y6);
	porchArea = ((x5 + x6) * y2) + (x5 * y6);
	drivewayArea = (x1 + x2 + x3) * y7;
	sidewalkArea = y7 * 4;
	

	lotSize = (x0+x1+x2+x3+x4+x5+x6+x7+x8+x9) * (y0+y1+y2+y3+y4+y5+y6+y7);
	houseArea = (x1+x2+x3+x4+x5+x6+x7+x8) * (y2+y3+y4+y5+y6);
	interiorArea = houseArea - (garageArea + porchArea);
	interiorVolume = interiorArea * z;
	exteriorWallLength = (x1+x2+x3+x4+x5+x6+x7+x8 + y2+y3+y4+y5+y6) * 2 + (2 * (y2 + y6));
	exteriorWallArea = exteriorWallLength * (z + 2);
	lawnArea = lotSize - (houseArea + drivewayArea + sidewalkArea + deckArea + patioArea);
	lotCost = 4.00 * lotSize;
	sitePrep = 1.00 * lotSize;
	foundationCost = 10.00 * houseArea;
	framingCost = 1.5 * houseArea * (z+2);
	totalSidingCost = sidingCost * exteriorWallArea;
	totalRoofingCost = roofingCost * houseArea;
	doorAndWindowsCost = 8.00 * houseArea;
	plumbingFixturesCost = 5.00 * houseArea;
	electricAndLightingCost = 5.00 * houseArea;
	heatAcCost = .50 * interiorVolume;
	insulationCost = .25 * interiorVolume;
	drywallCost = .50 * interiorVolume;
	paintCost = .40 * interiorVolume;
	cabinentCost = 5.00 * interiorArea;
	applianceCost = 5000 * applianceStyle;
	totalFlooringCost = bathroomArea * bathroomFlooring + bedroomArea * bedroomFlooring + diningArea * diningFlooring + familyArea * familyFlooring + foyerArea * foyerFlooring + hallArea * hallFlooring + kitchenArea * kitchenFlooring + laundryArea * laundryFlooring + livingArea * livingFlooring;
	securityCost = .75 * houseArea;
	concreteCost = 4.00 * (drivewayArea + patioArea + sidewalkArea + porchArea);
	totalDeckCost = deckCost * deckArea;
	landscapingCost = 1.00 * lawnArea;
	sprinklerCost = .3 * lawnArea;
	subTotal = lotCost + sitePrep + foundationCost + framingCost + totalSidingCost + totalRoofingCost + doorAndWindowsCost + plumbingFixturesCost + electricAndLightingCost + heatAcCost + insulationCost + drywallCost + paintCost + cabinentCost + applianceCost + totalFlooringCost + securityCost + concreteCost + totalDeckCost + landscapingCost + sprinklerCost;
	contractorCost = .2 * subTotal;
	total = contractorCost + subTotal;

	printf("Lot size = %0.2lf\n", lotSize);
	printf("House area = %0.2lf\n", houseArea);
	printf("Interior area = %0.2lf\n", interiorArea);
	printf("Interior volume = %0.2lf\n", interiorVolume);
	printf("Exterior wall length = %0.2lf\n", exteriorWallLength);
	printf("Exterior wall area = %0.2lf\n\n", exteriorWallArea);
	printf("Lot cost = %0.2lf\n", lotCost);
	printf("Site prep = %0.2lf\n", sitePrep);
	printf("Foundation = %0.2lf\n", foundationCost);
	printf("Framing = %0.2lf\n", framingCost);
	printf("Siding = %0.2lf\n", totalSidingCost);
	printf("Roofing = %0.2lf\n", totalRoofingCost);
	printf("Doors and windows = %0.2lf\n", doorAndWindowsCost);
	printf("Plumbing = %0.2lf\n", plumbingFixturesCost);
	printf("Electrical = %0.2lf\n", electricAndLightingCost);
	printf("Heating and A/C = %0.2lf\n", heatAcCost);
	printf("Insulation = %0.2lf\n", insulationCost);
	printf("Drywall = %0.2lf\n", drywallCost);
	printf("Painting = %0.2lf\n", paintCost);
	printf("Cabinents = %0.2lf\n", cabinentCost);
	printf("Appliances = %0.2lf\n", applianceCost);
	printf("Flooring = %0.2lf\n", totalFlooringCost);
	printf("Security system = %0.2lf\n", securityCost);
	printf("Concrete = %0.2lf\n", concreteCost);
	printf("Deck = %0.2lf\n", totalDeckCost);
	printf("Landscaping = %0.2lf\n", landscapingCost);
	printf("Sprinkler system = %0.2lf\n", sprinklerCost);
	printf("Subtotal = %0.2lf\n", subTotal);
	printf("Contractor = %0.2lf\n", contractorCost);
	printf("Total = %0.2lf\n", total);

	return 0;
}
