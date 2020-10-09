//
// Created by Gustavo Batistela on 09/10/2020.
//

#ifndef OCDOTS_H
#define OCDOTS_H

class OCDots {
private: 
    double m_viscosity = -1.0;
    
public:
    
    explicit OCDots(double viscosity);
    ~OCDots() = default;
    
    [[nodiscard]] double Viscosity() const;
    void SetViscosity(double viscosity);
};


#endif//OCPPDOTS_OCDOTS_H
