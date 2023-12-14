set terminal svg enhanced font "arial,12" size 800,600
set grid
set datafile separator ";"

set output 'output_temps.svg'

set xlabel "Temps (en sec)"
set ylabel "Nombre de fléchette (en million)"
plot 'BUILD/values.dat' every 4::1 using 3:4 with linespoints title 'SEQUENTIAL Pi', \
     '' every 4::2 using 3:4 with linespoints title 'OMP Pi', \
     '' every 4::3 using 3:4 with linespoints title 'Target'


set output 'output.svg'

set xlabel "Nombre de fléchette (en million)"
set ylabel "Valeur de Pi"
set yrange[3.1418: 3.1415]

# Ajout de l'axe horizontal avec le titre
set arrow 1 from graph 0, first 3.141593 to graph 1, first 3.141593 nohead lt 2 lw 2 lc "red"
set label "Valeur de PI" at 45, first 3.141593-0.00002 center tc "red"  


plot 'BUILD/values.dat' every 4::1 using 4:2 with linespoints title 'SEQUENTIAL Pi', \
     '' every 4::2 using 4:2 with linespoints title 'OMP Pi', \
     '' every 4::3 using 4:2 with linespoints title 'Target', \
     #'' every 4::3 using 0:($1+0.02):1 with labels offset char 1,1 notitle
	
