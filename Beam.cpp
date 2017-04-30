#include "Beam.h"

// Constructor for beam. Takes two points and the maximum allowed
// length for beams.
Beam::Beam(Point* _p1, Point* _p2, double _r) {
  p1 = _p1;
  p2 = _p2;
  k = 100000.0;
  r = _r;
  yield_strength = 0.02;
}

// Alternate constructor for beam that allows for defining beamtype.
Beam::Beam(Point* _p1, Point* _p2, double _r, short _beamType)
{
	p1 = _p1;
	p2 = _p2;
	k = 100000.0;
	r = _r;
	beamType = _beamType;
	yield_strength = 0.02;
}

// Alternate constructor with material properties
Beam::Beam(Point* _p1, Point* _p2, double _r, short _beamType, string material_name)
{
    p1 = _p1;
    p2 = _p2;
    k = 100000.0;
    r = _r;
    beamType = _beamType;
    yield_strength = 0.02;
    assign_mat_properties(material_name);
}

// Returns true if a beam has failed.
bool Beam::fail(double distance) {
	stress = 1 - (abs(distance) - r) / 0.02;
	return abs(distance) > (r + yield_strength);
}

// Returns the stress on a beam.
double Beam::getStress() {
	return stress;
}

// Assigns the bridge material properties based on input string.
void Beam::assign_mat_properties(string material_name){
    struct material {
        double weight;
        double yield_strength;
        double k;
        double cost_per_meter;
    };
    double cross_sectional_area = 0.0125;//cross sectional area of I-Beam
    double cost_factor = 50.50;//accounts for beam size and estimate of manufacturing costs
    
    material A992;
        A992.weight = 7850*cross_sectional_area;
        A992.yield_strength = 345.0;
        A992.k = 200.0;
        A992.cost_per_meter = 1.51*cost_factor;

    material Low_Carbon_Steel;
        Low_Carbon_Steel.weight = 7860*cross_sectional_area;
        Low_Carbon_Steel.yield_strength = 350.0;
        Low_Carbon_Steel.k = 200.0;
        Low_Carbon_Steel.cost_per_meter = 1.0*cost_factor;
    
    material Cold_Rolled_Steel;
        Cold_Rolled_Steel.weight = 7920*cross_sectional_area;
        Cold_Rolled_Steel.yield_strength = 500.0;
        Cold_Rolled_Steel.k = 190.0;
        Cold_Rolled_Steel.cost_per_meter = 1.51*cost_factor;

    material Cast_Iron;
        Cast_Iron.weight = 7300*cross_sectional_area;
        Cast_Iron.yield_strength = 230.0;
        Cast_Iron.k = 190.0;
        Cast_Iron.cost_per_meter = 1.51*cost_factor;

    material Aluminum;
        Aluminum.weight = 2710*cross_sectional_area;
        Aluminum.yield_strength = 255.0;
        Aluminum.k = 69.0;
        Aluminum.cost_per_meter = 4.01*cost_factor;


    map<string, material> material_properties;
    // Inserting data in std::map
    //based on HEB 260B I-beam, cross sectional area is 0.0125 m^2
    //weight per m^2 = density * volume per meter
    //{Density,Yield Strength,Young's Modulus,Dollars per Meter}

    //material costs are found from a table at http://www.roymech.co.uk/Useful_Tables/Matter/Costs.html
    //for convenience, the relative costs of the materials will be multiplied by a 'cost factor'
    material_properties["ASTM A992 Steel"] = A992;
    material_properties["Low Carbon Steel"] = Low_Carbon_Steel;
    material_properties["Cold Rolled Steel"] = Cold_Rolled_Steel;
    material_properties["Cast Iron"] = Cast_Iron;
    material_properties["Aluminum 6061-T6"] = Aluminum;

    /*
    need to implement these materials as above
    material_properties["Yellow Brass Cold-Rolled"] = {8470*area, 435.0, 105.0,10.2*cost_factor};
    material_properties["Yellow Brass Annealed"] = {8470*area, 105.0, 105.0,10.2*cost_factor};
    material_properties["Phosphor Bronze Cold-Rolled"] = {8860*area, 520.0, 110.0,12*cost_factor};
    material_properties["Magnesium Alloy"] = {1800*area, 275.0, 45.0,7.3*cost_factor};
    material_properties["Titanium Alloy"] = {4460*area, 825.0, 114.0,30.9*cost_factor};
    */

    material search_result = material_properties[material_name];
    weight = search_result.weight;
    yield_strength = search_result.yield_strength;
    k = search_result.k;
    cost_per_meter = search_result.cost_per_meter;
}