#!/usr/bin/wish

proc xconvert { p } {
    expr 15 * $p + 5
}

proc yconvert { p canvas } {
    expr [ lindex [ $canvas configure -height ] 4 ] - 15 * $p - 5
}

proc make_dot { x y canvas } {
    set ulx [ expr [ xconvert $x ] - 1 ]
    set uly [ expr [ yconvert $y $canvas ] + 1 ]
    set lrx [ expr $ulx + 2 ]
    set lry [ expr $uly - 2 ]
	      
    $canvas create oval $ulx $uly $lrx $lry -fill black
}

proc circle { x y canvas } { 
    set ulx [ expr [ xconvert $x ] - 2 ]
    set uly [ expr [ yconvert $y $canvas ] + 2 ]
    set lrx [ expr $ulx + 4 ]
    set lry [ expr $uly - 4 ]
	      
    $canvas create oval $ulx $uly $lrx $lry -outline red
}

proc draw_line { x1 y1 x2 y2 canvas } {
    set x1pos [ xconvert $x1 ]
    set y1pos [ yconvert $y1 $canvas ]
    set x2pos [ xconvert $x2 ]
    set y2pos [ yconvert $y2 $canvas ]

    $canvas create line $x1pos $y1pos $x2pos $y2pos
}

proc draw_grid { canvas } {

    set dim { 0 1 2 3 4 5 6 7 8 9 10 }
    foreach x $dim {
	foreach y $dim {
	    make_dot $x $y $canvas
	}
    }
}

wm title . "Rules Graph Visualizer"

canvas .c -bg white -height 165 -width 165
pack .c

button .b -command { exit } -text Quit -bg red
pack .b

draw_grid .c 




