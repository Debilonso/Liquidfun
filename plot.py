import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
X = np.arange(1, 99, 1)
Y = np.arange(1, 99, 1)
X, Y = np.meshgrid(X, Y)
z = np.genfromtxt("onda.dat")

surf = ax.plot_surface(X, Y, z[0:98], cmap=cm.coolwarm,linewidth=0, antialiased=False)
plt.title("Diferencias finitas ondas Tiempo 0")
plt.savefig("Ondas1.pdf")
plt.show()
#datos tiempo= 0.


fig2, ax2 = plt.subplots(subplot_kw={"projection": "3d"})
surf = ax2.plot_surface(X, Y, z[979:1077], cmap=cm.coolwarm,linewidth=0, antialiased=False)
plt.title("Diferencias finitas Tiempo 10")
plt.savefig("Ondas2.pdf")
plt.show()
#datos tiempo= 10.

fig3, ax3 = plt.subplots(subplot_kw={"projection": "3d"})
surf = ax3.plot_surface(X, Y, z[1959:2057], cmap=cm.coolwarm,linewidth=0, antialiased=False)
plt.title("Diferencias finitas tiempo= 20")
plt.savefig("Ondas3.pdf")
plt.show()
#datos tiempo= 20.

fig4, ax4 = plt.subplots(subplot_kw={"projection": "3d"})
surf = ax4.plot_surface(X, Y, z[4899:4997], cmap=cm.coolwarm,linewidth=0, antialiased=False)
plt.title("Diferencias finitas ondas tiempo= 50")
plt.savefig("Ondas4.pdf")
plt.show()
#datos tiempo= 50.

fig5, ax5 = plt.subplots(subplot_kw={"projection": "3d"})
surf = ax5.plot_surface(X, Y, z[9799:9897], cmap=cm.coolwarm,linewidth=0, antialiased=False)
plt.title("Diferencias finitas ondas tiempo= 100")
plt.savefig("Ondas5.pdf")
plt.show()
#datos tiempo= 100.

fig6, ax6 = plt.subplots(subplot_kw={"projection": "3d"})
surf = ax6.plot_surface(X, Y, z[48999:49097], cmap=cm.coolwarm,linewidth=0, antialiased=False)
plt.title("Diferencias finitas ondas tiempo= 500")
plt.savefig("Ondas6.pdf")
plt.show()
#datos tiempo= 500.

fig7, ax7 = plt.subplots(subplot_kw={"projection": "3d"})
surf = ax7.plot_surface(X, Y, z[97901:97999], cmap=cm.coolwarm,linewidth=0, antialiased=False)
plt.title("Diferencias finitas ondas tiempo= 999")
plt.savefig("Ondas6.pdf")
plt.show()
#datos tiempo= 999.