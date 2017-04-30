#include <set>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <string.h>
using namespace std;


struct material {
        double weight;
        double yield_strength;
        double k;
        double cost_per_meter;
    };


int main(){

    
    material steel;
    steel.weight = 1.1;
    steel.yield_strength = 2.2;
    steel.k = 3.3;
    steel.cost_per_meter = 4.4;
	map<string, material> material_properties;
    // Inserting data in std::map
    //based on HEB 260B I-beam, cross sectional area is 0.0125 m^2
    //weight per m^2 = density * volume per meter
    //{Density,Yield Strength,Young's Modulus,Dollars per Meter}

    //material costs are found from a table at http://www.roymech.co.uk/Useful_Tables/Matter/Costs.html
    //for convenience, the relative costs of the materials will be multiplied by a 'cost factor'
    double cross_sectional_area = 0.0125;//cross sectional area of I-Beam
    double cost_factor = 50.50;//accounts for beam size and estimate of manufacturing costs
    material_properties["ASTM A992 Steel"] = steel;
  //  material_properties.insert("Low Carbon Steel", {7860*area, 350.0, 200.0, 1*cost_factor});
  //  material_properties.insert("Cold-Rolled Steel",{7920*area, 500.0, 190.0,1.51*cost_factor});
    
/*
    material_properties["Cast Iron"] = {7300*area, 230.0, 190.0,1.51*cost_factor};
    material_properties["Aluminum 6061-T6"] = {2710*area, 255.0, 69.0,4.01*cost_factor};
    material_properties["Yellow Brass Cold-Rolled"] = {8470*area, 435.0, 105.0,10.2*cost_factor};
    material_properties["Yellow Brass Annealed"] = {8470*area, 105.0, 105.0,10.2*cost_factor};
    material_properties["Phosphor Bronze Cold-Rolled"] = {8860*area, 520.0, 110.0,12*cost_factor};
    material_properties["Magnesium Alloy"] = {1800*area, 275.0, 45.0,7.3*cost_factor};
    material_properties["Titanium Alloy"] = {4460*area, 825.0, 114.0,30.9*cost_factor};
*/
    material search_result = material_properties["ASTM A992 Steel"];
    double weight = search_result.weight;
    double yield_strength = search_result.yield_strength;
    double k = search_result.k;
    double cost_per_meter = search_result.cost_per_meter;
    cout << weight << "\n";
    cout << k << "\n";
    cout << yield_strength << "\n";
    cout << cost_per_meter << "\n";
    return 1;
}