#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <iostream> 
using namespace std;

int main()
{
    map<string, vector<double> > material_properties;
    // Inserting data in std::map
    //based on HEB 260B I-beam, cross sectional area is 0.0125 m^2
    //weight per m^2 = density * volume per meter
    //{Density,Yield Strength,Young's Modulus,Dollars per Meter}

    //material costs are found from a table at http://www.roymech.co.uk/Useful_Tables/Matter/Costs.html
    //for convenience, the relative costs of the materials will be multiplied by a 'cost factor'
    double area = 0.0125;//cross sectional area of I-Beam
    double cost_factor = 50.50;//accounts for beam size and estimate of manufacturing costs
    material_properties["ASTM A992 Steel"] = {7850*area, 345.0, 200.0,1.51*cost_factor};
    material_properties["Low Carbon Steel"] = {7860*area, 350.0, 200.0, 1*cost_factor};
    material_properties["Cold-Rolled Steel"] = {7920*area, 500.0, 190.0,1.51*cost_factor};
    material_properties["Cast Iron"] = {7300*area, 230.0, 190.0,1.51*cost_factor};
    material_properties["Aluminum 6061-T6"] = {2710*area, 255.0, 69.0,4.01*cost_factor};
    material_properties["Yellow Brass Cold-Rolled"] = {8470*area, 435.0, 105.0,10.2*cost_factor};
    material_properties["Yellow Brass Annealed"] = {8470*area, 105.0, 105.0,10.2*cost_factor};
    material_properties["Phosphor Bronze Cold-Rolled"] = {8860*area, 520.0, 110.0,12*cost_factor};
    material_properties["Magnesium Alloy"] = {1800*area, 275.0, 45.0,7.3*cost_factor};
    material_properties["Titanium Alloy"] = {4460*area, 825.0, 114.0,30.9*cost_factor};
}

/*
g++ -std=c++11 material_properties.cpp


Structural Steel:
Density=7860//kg/m^3
Yield Strength=260//MPa
Young's Modulus=200//GPa

High Strength Low Carbon Steel:
Density=7860//kg/m^3
Yield Strength=350//MPa
Young's Modulus=200//GPa

Cold-Rolled Steel:
Density=7920//kg/m^3
Yield Strength=500//MPa
Young's Modulus=190//GPa

Cast Iron:
Density=7300//kg/m^3
Yield Strength=230//MPa
Young's Modulus=190//GPa

Aluminum 6061-T6:
Density=2710//kg/m^3
Yield Strength=255//MPa
Young's Modulus=69//GPa

Yellow Brass Cold-Rolled:
Density=8470//kg/m^3
Yield Strength=435//MPa
Young's Modulus=105//GPa

Yellow Brass Annealed:
Density=8470//kg/m^3
Yield Strength=105//MPa
Young's Modulus=105//GPa

Phosphor Bronze Cold-Rolled:
Density=8860//kg/m^3
Yield Strength=520//MPa
Young's Modulus=110//GPa

Magnesium Alloy:
Density=1800//kg/m^3
Yield Strength=275//MPa
Young's Modulus=45//GPa

Titanium Alloy:
Density=4460//kg/m^3
Yield Strength=825//MPa
Young's Modulus=114//GPa


*/