#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <iostream> 
using namespace std;

int main()
{
    map<string, vector<int> > material_properties;
    // Inserting data in std::map
    material_properties["Structural Steel"] = {7860, 260, 200};
    material_properties["Low Carbon Steel"] = {7860, 350, 200};
    material_properties["Cold-Rolled Steel"] = {7920, 500, 190};
    material_properties["Cast Iron"] = {7300, 230, 190};
    material_properties["Aluminum 6061-T6"] = {2710, 255, 69};
    material_properties["Yellow Brass Cold-Rolled"] = {8470, 435, 105};
    material_properties["Yellow Brass Annealed"] = {8470, 105, 105};
    material_properties["Phosphor Bronze Cold-Rolled"] = {8860, 520, 110};
    material_properties["Magnesium Alloy"] = {1800, 275, 45};
    material_properties["Titanium Alloy"] = {4460, 825, 114};
    return 0;


    vector<int> mat_prop(3) mat_prop;
    mat_prop=material_properties.find("Cast Iron");

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