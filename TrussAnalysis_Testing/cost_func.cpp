/*
*This function accepts a bridge as an input and returns a cost estimate as a double
*SoftSysPowerPlants Project
*Joseph Lee
*/

double cost_func(bridge){

	double cost = 0.0;
	for (each beam in bridge){
		cost = cost + (beam->material look up cost of material * beam_length)
	}
	return cost
}