import ROOT
from matplotlib import pyplot as plt
import crflux.models as mods
import numpy as np
import math

def integrate(func, x0, x1, target_error):
    y0, y1 = func(x0), func(x1)
    abs_error = abs(y0-y1)
    integral = y0+y1
    trial_error = abs_error/integral     # percentage error of a single step

    step_no = 0
    x_range = x1 - x0

    while (trial_error>target_error):
        step_no += math.ceil(trial_error/target_error + 1*step_no)
        if (step_no<100): step_no = 100
        step_size = x_range/step_no

        x = x0
        y0 = y1 = func(x)
        integral = abs_error = 0
        for i in range(step_no-1):
            x += step_size
            y0 = y1
            y1 = func(x)
            integral += y0+y1
            abs_error += abs(y0-y1)
        integral = step_size*integral
        abs_error = step_size*abs_error

        # last step is seperated since step_size is changed by accumulated cutoff errors 
        step_size = x1-x
        y0 = y1
        y1 = func(x1)
        integral += step_size*(y0+y1)
        abs_error += step_size*abs(y0-y1)

        trial_error = abs_error/integral
    
    return 0.5*integral

CR_model = mods.HillasGaisser2012("H4a")
def pFlux(E):
    return CR_model.nucleus_flux(14, E)
def HeFlux(E):
    return CR_model.nucleus_flux(402, E)

def GetNuFlux(CRFlux, FileName):
    bin_no = 200
    Emax = (1e5)*1000
    Emin = (1e0)*1000
    bin_edge = np.logspace(0, 5, bin_no+1)
    E = (bin_edge[:-1] + bin_edge[1:])/2
    bin = [[0 for j in range(i+1)] for i in range(bin_no)]
    p_counter = np.zeros(bin_no)
    nuFlux = np.zeros(bin_no)

    file = ROOT.TFile.Open(FileName)
    nu_tree = file.Get("nu_mu")
    p_tree = file.Get("proton")

    E_p = 0
    for entry in nu_tree:
        if (entry.KE_MeV<Emin or entry.KE_MeV>Emax): continue
        if (entry.Primary_KE_MeV != E_p):
            E_p = entry.Primary_KE_MeV
            if (E_p<Emin or E_p>Emax): continue
            p_index = np.digitize(E_p/1000, bin_edge) - 1
        nu_index = np.digitize(entry.KE_MeV/1000, bin_edge) - 1
        bin[p_index][nu_index] += 1

    for entry in p_tree:
        p_index = np.digitize(entry.KE_MeV/1000, bin_edge) - 1
        p_counter[p_index] += 1

    print(f"Number of CR injected = {np.sum(p_counter)}")
    file.Close()

    for i in range(bin_no):
        if (p_counter[i] == 0): continue
        bin[i] = (bin[i]/p_counter[i])*integrate(CRFlux, bin_edge[i], bin_edge[i+1], 0.0001)

    for j in range(bin_no):
        delta_E = bin_edge[j+1]-bin_edge[j]
        for i in range(j, bin_no):
            nuFlux[j] += bin[i][j]/delta_E
    
    return E, nuFlux

plt.figure(figsize=(7.5, 5))
plt.title(r'$\nu_{\mu}$ flux')
plt.loglog()
plt.xlabel(r"$E_{\nu}$ [GeV]")
plt.ylabel(r"dN/dE (E/GeV)$^{3}$ (cm$^{2}$ s GeV)$^{-1}$")

E, nuFlux = GetNuFlux(pFlux, "/home/jimmyma/Software/SANuSim/result/Cut/p5M_1GeV-100TeV.root")
scalingFactor = (0.00042464212)/10000   # pi*(2.5*R_sun/1AU)^2 = 0.00042464212
nuFlux = nuFlux*scalingFactor
TotalFlux = nuFlux

E, nuFlux = GetNuFlux(pFlux, "/home/jimmyma/Software/SANuSim/result/Cut/He5M_1GeV-100TeV.root")
nuFlux = nuFlux*scalingFactor
TotalFlux += nuFlux
plt.plot(E, TotalFlux*(E**3), color="black", ls="-", lw=1.5, label='p+He')

def ReadData(filename):
    a, b = [], []
    with open(filename + '.txt', 'r') as file:
        for line in file:
            data = list(map(float, line.split(',')))
            a.append(data[0])
            b.append(data[1])
    return a, b

x, y = ReadData('C.A. Arguelles_muFlux_Sun')
plt.plot(x, y, color="b", ls="-", lw=1.5, label="Arguelles")

plt.legend(loc=0, frameon=False, numpoints=1, ncol=2)
plt.tight_layout()
plt.savefig("NuFlux.pdf")